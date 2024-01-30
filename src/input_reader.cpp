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
    if (eof())
        return '\0';
    return input[pos];
}

char InputReader::consume()
{
    if (eof())
        return '\0';
    
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

void InputReader::die(const std::string &message)
{
    std::stringstream ss;
    ss << "error: " << message << " at " << line << ":" << column;
    throw std::runtime_error(ss.str());
}
