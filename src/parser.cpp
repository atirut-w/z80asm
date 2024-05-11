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

        if (peek(1).type == Token::TYPE_COLON)
        {
            statements.push_back(make_shared<Label>(get<string>(consume().value)));
            consume();
        }
        else if (peek(1).type == Token::TYPE_IDENT || peek(1).type == Token::TYPE_NUMBER || peek(1).type == Token::TYPE_PAREN || peek(1).type == Token::TYPE_NEWLINE)
        {
            error("TODO: parse instruction");
        }
        else
        {
            consume(); // Correct position
            error("expected colon or identifier");
        }
    }
}
