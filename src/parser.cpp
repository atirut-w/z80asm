#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>

using namespace std;

const vector<string> REG8 = {
    "a",
    "f",
    "b",
    "c",
    "d",
    "e",
    "h",
    "l",

    "i",
    "r"
};

const vector<string> REG16 = {
    "af",
    "bc",
    "de",
    "hl",
    "sp",
    "ix",
    "iy"
};

void Parser::error(const string &msg)
{
    errors.push_back(to_string(nlines) + ": " + msg);
}

vector<string> Parser::split(const string &str, const char delim)
{
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delim))
        result.push_back(item);
    return result;
}

vector<shared_ptr<Statement>> Parser::parse(istream &input)
{
    vector<shared_ptr<Statement>> statements;

    string line;
    for(nlines = 1; getline(input, line); nlines++)
    {
        if (line.find(';') != string::npos)
            line.erase(line.find(';'));
        boost::trim(line);
        
        // TODO: For future references, preproc should be done here. Skip everything after if condition is false.

        if (line.find(':') != string::npos)
        {
            auto label = make_shared<Label>();
            label->line = nlines;
            label->name = boost::trim_copy(line.substr(0, line.find(':')));
            statements.push_back(label);
            line.erase(0, line.find(':') + 1);
        }
        boost::trim(line);
        if (line.empty())
            continue;
        
        auto instruction = make_shared<Instruction>();
        instruction->line = nlines;
        instruction->mnemonic = boost::to_lower_copy(line.substr(0, line.find(' ')));
        line.erase(0, line.find(' ') + 1);

        for (auto &operand_str : split(line, ','))
        {
            boost::trim(operand_str);
            Operand operand;
            operand.text = operand_str;
            
            if (operand_str[0] == '(')
            {
                if (operand_str[operand_str.size() - 1] != ')')
                {
                    error("expected ')' after indirect operand");
                    break;
                }
                operand_str = operand_str.substr(1, operand_str.size() - 2);
                operand.indirect = true;
            }

            // Detect operand type
            if (isdigit(operand_str[0])) // Integer
            {
                operand.type = Operand::Type::Number;
                if (operand_str[0] == '0' && operand_str.length() > 1)
                {
                    if (tolower(operand_str[1]) == 'x')
                    {
                        for (size_t i = 2; i < operand_str.length(); i++)
                        {
                            if (!isxdigit(operand_str[i]))
                            {
                                error("invalid hexadecimal number `" + operand_str + "`");
                                break;
                            }
                        }
                    }
                    else
                    {
                        error("invalid non-decimal number `" + operand_str + "`");
                        break;
                    }
                }
                else
                {
                    for (size_t i = 1; i < operand_str.length(); i++)
                    {
                        if (!isdigit(operand_str[i]))
                        {
                            error("invalid number `" + operand_str + "`");
                            break;
                        }
                    }
                }
            }
            else if (find(REG8.begin(), REG8.end(), boost::to_lower_copy(operand_str)) != REG8.end()) // 8-Bit registers
            {
                operand.type = Operand::Type::Reg8;
            }
            else if (find(REG16.begin(), REG16.end(), boost::to_lower_copy(operand_str)) != REG16.end()) // 16-Bit registers
            {
                operand.type = Operand::Type::Reg16;
            }
            else if (isalpha(operand_str[0])) // Name
            {
                operand.type = Operand::Type::Name;
                for (size_t i = 1; i < operand_str.length(); i++)
                {
                    if (!isalnum(operand_str[i]) && operand_str[i] != '_')
                    {
                        error("invalid name `" + operand_str + "`");
                        break;
                    }
                }
            }
            else // TODO: String literal support for pseudo-instructions
            {
                error("could not determine operand type for `" + operand_str + "`");
            }

            instruction->operands.push_back(operand);
        }

        statements.push_back(instruction);
    }
    return statements;
}
