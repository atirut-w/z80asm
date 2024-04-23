#pragma once
#include <input_reader.hpp>
#include <vector>

struct Token
{
};

class Tokenizer
{
private:
    InputReader reader;

public:
    std::vector<Token> tokens;

    Tokenizer(std::shared_ptr<std::istream> stream);
};
