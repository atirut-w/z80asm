#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <elfio/elfio.hpp>

struct Section
{
    std::string name;
    std::vector<uint8_t> data;
    uint16_t org = -1;

    // For ELF output phase
    int index;
};

struct Symbol
{
    std::string name;
    int section;
    uint16_t offset;
    int type = ELFIO::STT_NOTYPE;
};

struct Module
{
    std::vector<Section> sections;
    std::vector<Symbol> symbols;

    ELFIO::elfio generate_elf();
};
