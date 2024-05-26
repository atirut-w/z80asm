#include <parser.hpp>

using namespace std;

vector<shared_ptr<Statement>> Parser::parse(istream &input)
{
    vector<shared_ptr<Statement>> statements;

    string current;
    for(; getline(input, current); line++)
    {
        // TODO: Parse line
    }
    return statements;
}
