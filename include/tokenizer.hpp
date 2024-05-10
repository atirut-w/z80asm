#pragma once
#include <input_reader.hpp>
#include <vector>
#include <variant>
#include <string>

struct Token
{
    // TODO: Consider combining colon and comma into one "punctuation" type
    enum Type
    {
        TYPE_UNKNOWN,
        TYPE_EOF,
        TYPE_IDENT,
        TYPE_NEWLINE,
        TYPE_COLON,
        TYPE_COMMA,
        TYPE_NUMBER,
        TYPE_PAREN,
    } type = TYPE_UNKNOWN;
    std::variant<std::string, int> value;
    int line = 1;
    int column = 1;
};

class Tokenizer
{
private:
    InputReader reader;

    void die(const std::string &message);

public:
    std::vector<Token> tokens;

    Tokenizer(std::shared_ptr<std::istream> stream);
    void tokenize();
};
