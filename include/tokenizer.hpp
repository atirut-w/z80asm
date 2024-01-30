#pragma once
#include <any>
#include <input_reader.hpp>
#include <string>
#include <functional>

class Token
{
public:
    enum Type
    {
        TK_EOF,
        TK_PUNC,
        TK_NUM,
        TK_INST,
    } type;
    std::any value;
};

class Tokenizer
{
private:
    InputReader reader;
    std::string buffer;

    static bool is_whitespace(char);

    void skip_comment();

public:
    Tokenizer(InputReader reader) : reader(reader) {}

    Token read_next();
    std::string read_while(std::function<bool(char)> predicate);
};
