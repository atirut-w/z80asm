#pragma once
#include <input_reader.hpp>
#include <vector>
#include <string>

struct Token
{
    enum Type
    {
        TYPE_UNKNOWN,
        TYPE_IDENT,
        TYPE_NEWLINE,
        TYPE_COLON,
        TYPE_COMMA,
        TYPE_NUMBER,
        TYPE_COMMENT,
    } type = TYPE_UNKNOWN;
    std::string value;
};

class Tokenizer
{
private:
    InputReader reader;
    Token current_token;

    void flush_token();

public:
    std::vector<Token> tokens;

    Tokenizer(std::shared_ptr<std::istream> stream);
    const InputReader &get_reader() { return reader; }
    void tokenize();
};
