#include <parser.hpp>

using namespace std;

void Parser::error(const string &message)
{
    errors.push_back(to_string(nlines) + ": error: " + message);
}

void Parser::parse(istream &stream)
{
    for (string line; getline(stream, line); nlines++)
    {
        // TODO: Implement
        error("TODO: Implement");
    }
}
