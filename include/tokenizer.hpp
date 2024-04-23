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
        TYPE_PAREN,
    } type = TYPE_UNKNOWN;
    std::string value;
    int line = 1;
    int column = 1;
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
