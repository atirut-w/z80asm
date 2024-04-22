#include <input_reader.hpp>
#include <sstream>
#include <fstream>

using namespace std;

InputReader::InputReader(filesystem::path path)
{
    this->path = filesystem::absolute(path);
    ifstream stream(path);
    if (!stream)
    {
        throw runtime_error("could not open `" + path.string() + "` for reading");
    }

    stringstream buffer;
    buffer << stream.rdbuf();
    content = buffer.str();
}

char InputReader::peek()
{
    if (eof())
        return '\0';
    return content[pos];
}

char InputReader::consume()
{
    if (eof())
        return '\0';
    
    char ch = content[pos++];
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
    return pos >= content.size();
}

void InputReader::die(const string &message)
{
    throw runtime_error(path.string() + ":" + to_string(line) + ":" + to_string(column) + ": " + message);
}
