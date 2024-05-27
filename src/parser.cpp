#include <parser.hpp>

using namespace std;

vector<shared_ptr<Statement>> Parser::parse(istream &input)
{
    vector<shared_ptr<Statement>> statements;

    string current;
    for(int nlines = 1; getline(input, current); nlines++)
    {
        // TODO: Parse line
    }
    return statements;
}
