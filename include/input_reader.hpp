#pragma once
#include <string>
#include <istream>

class InputReader
{
private:
    std::string input;
    int pos = 0;
    int line = 1;
    int column = 1;

public:
    InputReader(std::istream &stream);

    char peek();
    char consume();
    bool eof();
};
