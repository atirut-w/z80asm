#pragma once
#include <cstdint>
#include <vector>
// #include <map>
#include <string>

class Assembler
{
private:
    uint16_t pc = 0;

    static std::string trim(std::string str);
    static std::vector<std::string> split(const std::string &str, const char &delim, bool trim = true);

public:
    std::vector<uint8_t> program;
    // std::map<std::string, uint16_t> labels;

    void assemble_line(std::string line);
};
