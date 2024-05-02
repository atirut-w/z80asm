#pragma once
#include <string>
#include <vector>
#include <istream>

struct Instruction
{

};

class Parser
{
private:
    int nlines = 1;

    void error(const std::string &message);

public:
    std::vector<Instruction> instructions;
    std::vector<std::string> errors;

    void parse(std::istream &stream);
};
