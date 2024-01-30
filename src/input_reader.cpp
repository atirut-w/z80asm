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
    return input[pos];
}

char InputReader::consume()
{
    char ch = input[pos++];
    if (ch == '\n')
    {
        line++;
        column = 1;
    }
    else if (ch == '\r' && peek() == '\n') // I hate CRLF I hate CRLF I hate CRLF.....
    {
        pos++;
        line++;
        column = 1;
    }
    else
    {
        column++;
    }
    return ch;
}

bool InputReader::eof()
{
    return pos >= input.size();
}
