#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <map>

using namespace std;

const map<string, Mnemonic> mnemonic_map = {
    {"ld", Mnemonic::LD},
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

        auto ident_tk = consume();
        if (peek().type == Token::TYPE_COLON)
        {
            statements.push_back(make_shared<Label>(get<string>(ident_tk.value)));
            consume();
        }
        else if (peek().type == Token::TYPE_IDENT || peek().type == Token::TYPE_NUMBER || peek().type == Token::TYPE_PAREN || peek().type == Token::TYPE_NEWLINE)
        {
            Instruction instruction;

            auto mnemonic_iter = mnemonic_map.find(boost::to_lower_copy(get<string>(ident_tk.value)));
            if (mnemonic_iter == mnemonic_map.end())
            {
                error("unrecognized instruction `" + get<string>(ident_tk.value) + "`");
                continue;
            }
            instruction.mnemonic = mnemonic_iter->second;

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
            }
        }
        else
        {
            consume(); // Correct position
            error("expected colon or identifier");
        }
    }
}
