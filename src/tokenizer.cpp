#include <tokenizer.hpp>
#include <cstring>
#include <sstream>

bool Tokenizer::is_id_start(char ch)
{
    return isalpha(ch) > 0 || ch == '_';
}

bool Tokenizer::is_id(char ch)
{
    return is_id_start(ch) || isdigit(ch) > 0;
}

bool Tokenizer::is_punc(char ch)
{
    return strchr(",", ch) != NULL;
}

bool Tokenizer::is_whitespace(char ch)
{
    return isspace(ch) > 0;
}

Token Tokenizer::read_number()
{
    if (reader.peek() == '0')
        reader.die("non-decimal numbers");
    
    std::string num_str = read_while(isdigit);
    
    return {Token::TK_NUM, std::stoi(num_str)};
}

Token Tokenizer::read_id()
{
    std::string id = read_while(is_id);
    return {Token::TK_IDENT, id};
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

    if (isdigit(ch)) return read_number();
    if (is_id_start(ch)) return read_id();
    if (is_punc(ch)) return {Token::TK_PUNC, reader.consume()};

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
