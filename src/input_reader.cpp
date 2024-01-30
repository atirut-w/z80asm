#include <input_reader.hpp>
#include <sstream>

InputReader::InputReader(std::istream &stream)
{
    std::stringstream buffer;
    buffer << stream.rdbuf();
    input = buffer.str();
}

char InputReader::peek()
{
    return input[0];
}

char InputReader::peek(int offset)
{
    return input[offset];
}

char InputReader::consume()
{
    char c = input[0];
    input.erase(0, 1);
    return c;
}

char InputReader::consume(int offset)
{
    char c = input[offset];
    input.erase(offset, 1);
    return c;
}

bool InputReader::eof()
{
    return input.empty();
}
