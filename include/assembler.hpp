#pragma once
#include <parser.hpp>
#include <cstdint>

class Assembler
{
private:
    int pc = 0;

    void error(const std::string &message, int line);

public:
    std::vector<uint8_t> program;
    
    void assemble(std::vector<std::shared_ptr<Statement>> &statements);
};
