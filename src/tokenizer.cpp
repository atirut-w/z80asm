#include <tokenizer.hpp>
#include <stdexcept>
#include <cctype>

using namespace std;

Tokenizer::Tokenizer(std::shared_ptr<std::istream> stream) : reader(stream)
{
    // TODO: Consider inlining this
}

void Tokenizer::tokenize()
{
    while (!reader.eof())
    {
        char next = reader.peek();
        Token current;
        current.line = reader.get_line();
        current.column = reader.get_column();

        if (isblank(next)) // Horizontal whitespace
        {
            while (isblank(reader.peek()))
                reader.consume();
        }
        else if (next == ';') // Comment
        {
            while (reader.peek() != '\n')
                reader.consume();
        }
        else if (isalpha(next) || next == '_') // Identifier
        {
            current.type = Token::TYPE_IDENT;
            while (isalnum(reader.peek()) || reader.peek() == '_')
            {
                get<string>(current.value) += reader.consume();
            }
            tokens.push_back(current);
        }
        else if (next == '\n') // Newline
        {
            current.type = Token::TYPE_NEWLINE;
            tokens.push_back(current);
            reader.consume();
        }
        else if (next == ':') // Colon
        {
            current.type = Token::TYPE_COLON;
            tokens.push_back(current);
            reader.consume();
        }
        else if (next == ',') // Comma
        {
            current.type = Token::TYPE_COMMA;
            tokens.push_back(current);
            reader.consume();
        }
        else if (isdigit(next)) // Number
        {
            // TODO: More strict validation
            current.type = Token::TYPE_NUMBER;
            string literal;
            while (isxdigit(reader.peek()) || tolower(reader.peek()) == 'x')
            {
                literal += reader.consume();
            }

            try
            {
                current.value = stoi(literal, nullptr, 0);
            }
            catch (const invalid_argument &err)
            {
                die("malformed integer literal `" + literal + "`");
            }
            catch (const out_of_range &err)
            {
                die("integer literal `" + literal + "` is out of range");
            }
            tokens.push_back(current);
        }
        else if (next == '(' || next == ')') // Parenthesis
        {
            current.type = Token::TYPE_PAREN;
            get<string>(current.value) += reader.consume();
        }
        else // Something went very wrong
            die("could not determine token type");
    }
    Token eof;
    eof.type = Token::TYPE_EOF;
    eof.line = reader.get_line();
    eof.column = reader.get_column();
    tokens.push_back(eof);
}

void Tokenizer::die(const string &message)
{
    throw runtime_error(to_string(reader.get_line()) + ":" + to_string(reader.get_column()) + ": error: " + message);
}
