#include <tokenizer.hpp>
#include <cstring>
#include <sstream>

bool Tokenizer::is_whitespace(char ch)
{
    return isspace(ch) > 0;
}

Token Tokenizer::read_next()
{
    read_while(is_whitespace);
    if (reader.eof())
        return {Token::TK_EOF, NULL};

    switch (reader.peek())
    {
        default:
            std::stringstream msg;
            msg << "can't handle character '" << reader.peek() << "'";
            reader.die(msg.str());
            return {Token::TK_EOF, NULL}; // Shut the compiler up
    }
}

std::string Tokenizer::read_while(std::function<bool(char)> predicate)
{
    std::string str;
    while (!reader.eof() && predicate(reader.peek()))
        str += reader.consume();
    return str;
}
