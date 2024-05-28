#pragma once
#include <parser.hpp>
#include <cstdint>

class Assembler
{
private:
    int pc = 0;
    std::vector<uint8_t> program;

    void error(const std::string &message, int line);

public:
    void assemble(std::vector<std::shared_ptr<Statement>> &statements);
};
