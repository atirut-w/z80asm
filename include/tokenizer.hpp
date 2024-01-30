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
        TK_IDENT,
    } type;
    std::any value;
};

class Tokenizer
{
private:
    InputReader reader;
    std::string buffer;

    static bool is_id_start(char);
    static bool is_id(char);
    static bool is_punc(char);
    static bool is_whitespace(char);

    Token read_number();
    Token read_id();
    void skip_comment();

public:
    Tokenizer(InputReader reader) : reader(reader) {}

    Token read_next();
    std::string read_while(std::function<bool(char)> predicate);
};
