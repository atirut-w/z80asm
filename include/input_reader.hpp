#pragma once
#include <string>
#include <istream>

/**
 * @brief Utility class to facilitate text parsing. It provides position tracking by line and column, peek/consume, and EOF detection.
 * 
 * @warning This class loads the entire input stream at once, so be mindful of memory usage.
 */
class InputReader
{
private:
    std::string input;
    int pos = 0;
    int line = 1;
    int column = 1;

public:
    InputReader(std::istream &stream);

    int get_line() { return line; }
    int get_column() { return column; }

    char peek();
    char consume();
    bool eof();
};
