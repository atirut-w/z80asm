#pragma once
#include <map>
#include <string>

enum Opcode
{
    // 8-Bit Load Group
    LD_R_R = 0b01000000,
    LD_R_N = 0b00000110,

    // General-Purpose Arithmetic and CPU Control Group
    HALT = 0b01110110,
};

// Note: while `(HL)` is technically an 8-bit "register", it is not included here
const std::map<std::string, int> REG8 = {
    {"b", 0},
    {"c", 1},
    {"d", 2},
    {"e", 3},
    {"h", 4},
    {"l", 5},
    {"a", 7}
};
