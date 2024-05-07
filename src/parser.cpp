#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

int recover(int cur, const std::vector<Token> &tokens)
{
    while (cur < tokens.size() && tokens[cur].type != Token::TYPE_NEWLINE)
        cur++;
    return cur;
}

void Parser::error(const Token &ctx, const std::string &message)
{
    errors.push_back(to_string(ctx.line) + ":" + to_string(ctx.column) + ": error: " + message);
}

void Parser::parse(const std::vector<Token> tokens)
{
    for (int cur = 0; cur < tokens.size() - 1; cur++)
    {
        if (tokens[cur].type == Token::TYPE_NEWLINE) // Blank line, this is
            continue;
        
        if (tokens[cur].type != Token::TYPE_IDENT) // A line always begin with a name for label or instruction... for now.
        {
            error(tokens[cur], "expected label or instruction");
            cur = recover(cur, tokens);
            continue;
        }
        
        error(tokens[cur], "TODO: implement parsing");
    }
}
