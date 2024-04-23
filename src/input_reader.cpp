#include <input_reader.hpp>
#include <sstream>

using namespace std;

InputReader::InputReader(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

char InputReader::peek()
{
    if (eof())
        return '\0';
    return stream->peek();
}

char InputReader::consume()
{
    if (eof())
        return '\0';
    
    char ch;
    stream->get(ch);
    if (ch == '\n')
    {
        line++;
        column = 1;
    }
    else if (ch == '\r' && peek() == '\n') // I hate CRLF I hate CRLF I hate CRLF.....
    {
        line++;
        column = 1;
        ch = '\n'; // No CRLF for you
    }
    else
    {
        column++;
    }
    return ch;
}

bool InputReader::eof()
{
    return stream->peek() == EOF;
}
