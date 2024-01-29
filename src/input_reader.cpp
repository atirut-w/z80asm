#include <input_reader.hpp>
#include <sstream>

InputReader::InputReader(std::istream &stream)
{
    std::stringstream buffer;
    buffer << stream.rdbuf();
    input = buffer.str();
}
