#include <tokenizer.hpp>
#include <stdexcept>
#include <cctype>

using namespace std;

Tokenizer::Tokenizer(std::shared_ptr<std::istream> stream) : reader(stream)
{
    // TODO: Consider inlining this
}

void Tokenizer::flush_token()
{
    if (current_token.value.length() > 0)
    {
        tokens.push_back(current_token);
    }
    current_token = Token();
}

void Tokenizer::tokenize()
{
    while (!reader.eof())
    {
        switch (current_token.type)
        {
        case Token::TYPE_UNKNOWN:
        {
            char ch = reader.peek();
            current_token.line = reader.get_line();
            current_token.column = reader.get_column();

            if (isblank(ch))
            {
                reader.consume();
                continue;
            }
            else if (isalpha(ch)) // Identifier
                current_token.type = Token::TYPE_IDENT;
            else if (isdigit(ch)) // Number
                current_token.type = Token::TYPE_NUMBER;
            else if (ch == '(' || ch == ')')
            {
                current_token.type = Token::TYPE_PAREN;
                current_token.value = reader.consume();
                flush_token();
            }
            else if (ch == '\n')
            {
                current_token.type = Token::TYPE_NEWLINE;
                current_token.value = reader.consume();
                flush_token();
            }
            else if (ch == ':')
            {
                current_token.type = Token::TYPE_COLON;
                current_token.value = reader.consume();
                flush_token();
            }
            else if (ch == ',')
            {
                current_token.type = Token::TYPE_COMMA;
                current_token.value = reader.consume();
                flush_token();
            }
            else if (ch == ';')
                current_token.type = Token::TYPE_COMMENT;
            else
                throw runtime_error("could not determine token type");

            break;
        }
        case Token::TYPE_IDENT:
        {
            char ch = reader.peek();

            if (!isalnum(ch) && ch != '_')
                flush_token();
            else
                current_token.value += reader.consume();
            
            break;
        }
        case Token::TYPE_NUMBER:
        {
            char ch = reader.peek();

            if (!isxdigit(ch)) // TODO: Consider supporting floating point numbers
                flush_token();
            else
                current_token.value += reader.consume();
            
            break;
        }
        case Token::TYPE_COMMENT:
        {
            char ch = reader.peek();

            if (ch == '\n')
            {
                flush_token();
            }
            else
                reader.consume();
            
            break;
        }
        default:
            throw runtime_error("unhandled token type " + to_string(current_token.type));
        }
    }
}
