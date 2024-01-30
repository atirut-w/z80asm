#pragma once
#include <string>
#include <istream>

class InputReader
{
private:
    std::string input;
    int pos = 0;

public:
    InputReader(std::istream &stream);

    int line = 1;
    int column = 1;

    char peek();
    char consume();
    bool eof();
    void die(const std::string &message);
};
