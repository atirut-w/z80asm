#include <assembler.hpp>
#include <string>

std::string Assembler::trim(std::string str)
{
    str.erase(0, str.find_first_not_of(" \t"));
    str.erase(str.find_last_not_of(" \t") + 1);
    return str;
}

void Assembler::assemble_line(std::string line)
{
    line = line.substr(0, line.find_first_of(";"));
    line = trim(line);
    if (line.empty())
        return;
}
