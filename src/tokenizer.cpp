#include <tokenizer.hpp>

Token Tokenizer::read_next()
{
    return {Token::TK_EOF, NULL};
}

std::string Tokenizer::read_while(std::function<bool(char)> predicate)
{
    std::string str;
    while (!reader.eof() && predicate(reader.peek()))
        str += reader.consume();
    return str;
}
