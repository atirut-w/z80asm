#include <tokenizer.hpp>
#include <cstring>
#include <sstream>

bool Tokenizer::is_whitespace(char ch)
{
    return isspace(ch) > 0;
}

void Tokenizer::skip_comment()
{
    read_while([](char ch) { return ch != '\n'; });
    reader.consume();
}

Token Tokenizer::read_next()
{
    read_while(is_whitespace);
    if (reader.eof())
        return {Token::TK_EOF, NULL};
    
    char ch = reader.peek();

    // TODO: strings, once `.db` is implemented
    switch (ch)
    {
        case ';':
            skip_comment();
            return read_next();
    }

    std::stringstream msg;
    msg << "can't handle character '" << ch << "'";
    reader.die(msg.str());
    return {Token::TK_EOF, NULL}; // Shut the compiler up
}

std::string Tokenizer::read_while(std::function<bool(char)> predicate)
{
    std::string str;
    while (!reader.eof() && predicate(reader.peek()))
        str += reader.consume();
    return str;
}
