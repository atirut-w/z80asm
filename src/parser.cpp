#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>

using namespace std;

void Parser::error(const string &msg)
{
    cerr << nlines << ": " << msg << endl;
    has_error = true;
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
            operand.value = operand_str;
            
            if (operand_str[0] == '(')
            {
                if (operand_str[operand_str.size() - 1] != ')')
                {
                    error("expected ')' after indirect operand");
                    break;
                }
                operand_str = operand_str.substr(1, operand_str.size() - 2);
                operand.indirect = true;
                cout << "Indirect " << operand_str << endl;
            }

            // TODO: Detect if operand is a register, number or name

            instruction->operands.push_back(operand);
        }

        statements.push_back(instruction);
    }
    return statements;
}
