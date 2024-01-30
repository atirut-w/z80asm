#pragma once
#include <string>
#include <istream>

class InputReader
{
private:
    std::string input;
    int line = 1;
    int column = 1;
public:
    InputReader(std::istream &stream);
    
    char peek();
    char peek(int offset);
    char consume();
    char consume(int offset);
    bool eof();
};
