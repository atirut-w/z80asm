#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

void Parser::error(const std::string &message)
{
    errors.push_back(to_string(tokens[cur].line) + ":" + to_string(tokens[cur].column) + ": error: " + message);

    // Recover from error
    while (cur < tokens.size() - 1 && tokens[cur].type != Token::TYPE_NEWLINE)
        cur++;
}

void Parser::parse()
{
    for (cur = 0; cur < tokens.size() - 1; cur++)
    {
        if (tokens[cur].type == Token::TYPE_NEWLINE) // Blank line, this is
            continue;
        
        if (tokens[cur].type != Token::TYPE_IDENT) // A line always begin with a name for label or instruction... for now.
        {
            error("expected label or instruction");
            continue;
        }
        
        error("TODO: implement parsing");
    }
}
