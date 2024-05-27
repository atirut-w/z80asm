#pragma once
#include <istream>
#include <ipositional.hpp>
#include <memory>
#include <vector>

struct Statement : public IPositional
{
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
public:
    std::vector<std::shared_ptr<Statement>> parse(std::istream &input);
};
