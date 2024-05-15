#pragma once
#include <string>
#include <vector>
#include <istream>
#include <memory>
#include <tokenizer.hpp>
#include <variant>

struct Statement
{
    virtual ~Statement() = default; // Force polymorphism for casting to derived types
};

struct Label : Statement
{
    std::string name;

    Label(std::string name) : name(name) {}
};

struct Operand
{
    std::variant<std::string, int> value;
    bool indirect = false;
};

struct Instruction : Statement
{
    std::string mnemonic;
    std::vector<Operand> operands;
};

class Parser
{
private:
    std::vector<Token> tokens;
    int cur = 0;

    void error(const std::string &message);
    const Token& consume();
    const Token& peek();
    const Token& peek(int offset);

public:
    std::vector<std::shared_ptr<Statement>> statements;
    std::vector<std::string> errors;

    Parser(const std::vector<Token> tokens) : tokens(tokens) {}
    void parse();
};
