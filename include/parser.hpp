#pragma once
#include <string>
#include <vector>
#include <istream>
#include <memory>

struct Statement
{
    virtual ~Statement() = default; // Force polymorphism for casting to derived types
};

struct Label : Statement
{
    std::string name;

    Label(std::string name) : name(name) {}
};

class Parser
{
private:
    int nlines = 1;

    void error(const std::string &message);

public:
    std::vector<std::shared_ptr<Statement>> statements;
    std::vector<std::string> errors;

    void parse(std::istream &stream);
};
