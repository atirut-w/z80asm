#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

void Parser::error(const Token &ctx, const std::string &message)
{
    errors.push_back(to_string(ctx.line) + ":" + to_string(ctx.column) + ": error: " + message);
}

void Parser::parse(const std::vector<Token> tokens)
{
    for (int cur = 0; cur < tokens.size(); cur++)
    {
        error(tokens[cur], "TODO: implement parsing");
    }
}
