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

struct Instruction : public Statement
{
    std::string mnemonic;
};

class Parser
{
private:
    int nlines = 1;

    void error(const std::string &msg);

public:
    bool has_error = false;

    std::vector<std::shared_ptr<Statement>> parse(std::istream &input);
};
