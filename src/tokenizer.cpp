#include <tokenizer.hpp>
#include <stdexcept>

using namespace std;

Tokenizer::Tokenizer(std::shared_ptr<std::istream> stream) : reader(stream)
{
}

void Tokenizer::flush_token()
{
    if (current_token.value.length() > 0)
    {
        tokens.push_back(current_token);
        current_token.type = Token::TYPE_UNKNOWN;
        current_token.value = "";
    }
}

void Tokenizer::tokenize()
{
    while (!reader.eof())
    {
        switch (current_token.type)
        {
        case Token::TYPE_UNKNOWN:
        {
            reader.consume(); // TODO: Determine token type
            break;
        }
        default:
            throw runtime_error("unhandled token type " + to_string(current_token.type));
        }
    }
}
