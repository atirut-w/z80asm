#include <parser.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

vector<shared_ptr<Statement>> Parser::parse(istream &input)
{
    vector<shared_ptr<Statement>> statements;

    string line;
    for(int nlines = 1; getline(input, line); nlines++)
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
        instruction->mnemonic = line.substr(0, line.find(' '));
        line.erase(0, line.find(' ') + 1);
    }
    return statements;
}
