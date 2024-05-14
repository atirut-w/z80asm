#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <map>

using namespace std;

const map<string, Mnemonic> mnemonic_map = {
    {"ld", Mnemonic::LD},
    {"push", Mnemonic::PUSH},
    {"pop", Mnemonic::POP},

    {"ex", Mnemonic::EX},
    {"exx", Mnemonic::EXX},
    {"ldi", Mnemonic::LDI},
    {"ldir", Mnemonic::LDIR},
    {"ldd", Mnemonic::LDD},
    {"lddr", Mnemonic::LDDR},
    {"cpi", Mnemonic::CPI},
    {"cpir", Mnemonic::CPIR},
    {"cpd", Mnemonic::CPD},
    {"cpdr", Mnemonic::CPDR},

    {"add", Mnemonic::ADD},
    {"adc", Mnemonic::ADC},
    {"sub", Mnemonic::SUB},
    {"sbc", Mnemonic::SBC},
    {"and", Mnemonic::AND},
    {"or", Mnemonic::OR},
    {"xor", Mnemonic::XOR},
    {"cp", Mnemonic::CP},
    {"inc", Mnemonic::INC},
    {"dec", Mnemonic::DEC},

    {"jp", Mnemonic::JP},
    {"jr", Mnemonic::JR},
    {"djnz", Mnemonic::DJNZ},

    {"in", Mnemonic::IN},
    {"ini", Mnemonic::INI},
    {"inir", Mnemonic::INIR},
    {"ind", Mnemonic::IND},
    {"indr", Mnemonic::INDR},
    {"out", Mnemonic::OUT},
    {"outi", Mnemonic::OUTI},
    {"otir", Mnemonic::OTIR},
    {"outd", Mnemonic::OUTD},
    {"outdr", Mnemonic::OUTDR},
};

void Parser::error(const std::string &message)
{
    errors.push_back(to_string(tokens[cur].line) + ":" + to_string(tokens[cur].column) + ": error: " + message);

    // Recover from error
    while (cur < tokens.size() - 1 && tokens[cur].type != Token::TYPE_NEWLINE)
        cur++;
}

const Token& Parser::consume()
{
    return tokens[cur++];
}

const Token& Parser::peek()
{
    return tokens[cur];
}

const Token& Parser::peek(int offset)
{
    return tokens[cur + offset];
}

void Parser::parse()
{
    while (peek().type != Token::TYPE_EOF)
    {
        if (peek().type == Token::TYPE_NEWLINE) // Blank line, this is
        {
            consume();
            continue;
        }
        if (peek().type != Token::TYPE_IDENT) // A line always begin with a name for label or instruction... for now.
        {
            error("expected identifier");
            continue;
        }

        auto ident_tk = peek();
        if (peek(1).type == Token::TYPE_COLON)
        {
            statements.push_back(make_shared<Label>(get<string>(consume().value)));
            consume();
        }
        else if (peek(1).type == Token::TYPE_IDENT || peek(1).type == Token::TYPE_NUMBER || peek(1).type == Token::TYPE_PAREN || peek(1).type == Token::TYPE_NEWLINE)
        {
            auto instruction = make_shared<Instruction>();

            auto mnemonic_iter = mnemonic_map.find(boost::to_lower_copy(get<string>(ident_tk.value)));
            if (mnemonic_iter == mnemonic_map.end())
            {
                error("unrecognized instruction `" + get<string>(ident_tk.value) + "`");
                continue;
            }
            instruction->mnemonic = mnemonic_iter->second;

            while (peek().type != Token::TYPE_NEWLINE && peek().type != Token::TYPE_EOF)
            {
                Operand operand;
                
                if (peek().type == Token::TYPE_PAREN)
                {
                    if (get<string>(peek().value) == ")")
                    {
                        error("unexpected closing parenthesis");
                        break;
                    }
                    operand.indirect = true;
                    consume();
                }

                if (peek().type != Token::TYPE_IDENT && peek().type != Token::TYPE_NUMBER)
                {
                    error("expected identifier or number");
                    break;
                }
                operand.value = consume().value;

                if (operand.indirect)
                {
                    if (peek().type != Token::TYPE_PAREN)
                    {
                        error("expected closing parenthesis");
                        break;
                    }
                    else if (get<string>(peek().value) == "(")
                    {
                        error("unexpected opening parenthesis");
                        break;
                    }
                    consume();
                }

                if (peek().type == Token::TYPE_COMMA)
                    consume();

                instruction->operands.push_back(operand);
            }

            statements.push_back(instruction);
        }
        else
        {
            consume(); // Correct position
            error("expected colon or identifier");
        }
    }
}
