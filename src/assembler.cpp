#include <assembler.hpp>
#include <string>
#include <sstream>

std::string Assembler::trim(std::string str)
{
    str.erase(0, str.find_first_not_of(" \t"));
    str.erase(str.find_last_not_of(" \t") + 1);
    return str;
}

std::vector<std::string> Assembler::split(const std::string &str, const char &delim, bool trim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(str);
    while (std::getline(token_stream, token, delim))
    {
        if (trim)
            token = Assembler::trim(token);
        tokens.push_back(token);
    }
    return tokens;
}

void Assembler::assemble_line(std::string line)
{
    line = line.substr(0, line.find_first_of(";"));
    line = trim(line);
    if (line.empty())
        return;

    auto raw_instruction = line.substr(0, line.find_first_of(" \t"));

    // TODO: Handle non-instruction lines

    auto raw_operands = split(line.substr(line.find_first_of(" \t")), ',');
}
