#pragma once
#include <istream>
#include <ipositional.hpp>
#include <memory>
#include <vector>

struct Statement : public IPositional
{
    virtual ~Statement() = default; // Force polymorphism
};

class Parser : private IPositional
{
public:
    std::vector<std::shared_ptr<Statement>> parse(std::istream &input);
};
