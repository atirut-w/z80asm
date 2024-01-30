#include <tokenizer.hpp>

Token Tokenizer::read_next()
{
    return {Token::TK_EOF, NULL};
}
