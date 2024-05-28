#pragma once
#include <istream>
#include <memory>
#include <vector>

struct Statement
{
    int line = 1;
    virtual ~Statement() = default; // Force polymorphism
};

struct Label : public Statement
{
    std::string name;
};

struct Operand
{
    enum class Type
    {
        Register,
        Number,
        Name
    } type;
    std::string text;
    bool indirect = false;
};

struct Instruction : public Statement
{
    std::string mnemonic;
    std::vector<Operand> operands;
};

class Parser
{
private:
    int nlines = 1;

    void error(const std::string &msg);
    std::vector<std::string> split(const std::string &str, char delim);

public:
    std::vector<std::string> errors;

    std::vector<std::shared_ptr<Statement>> parse(std::istream &input);
};
