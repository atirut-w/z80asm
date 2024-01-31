#pragma once
#include <cstdint>
#include <vector>
// #include <map>
#include <string>

class Assembler
{
private:
    uint16_t pc = 0;

public:
    std::vector<uint8_t> program;
    // std::map<std::string, uint16_t> labels;

    void assemble_line(std::string line);
};
