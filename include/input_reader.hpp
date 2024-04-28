#pragma once
#include <string>
#include <istream>
#include <memory>

/**
 * @brief Utility class to facilitate text parsing. It provides position tracking by line and column, peek/consume, and EOF detection.
 */
class InputReader
{
private:
    std::shared_ptr<std::istream> stream;
    int line = 1;
    int column = 1;

public:
    InputReader(std::shared_ptr<std::istream> stream);

    int get_line() { return line; }
    int get_column() { return column; }

    char peek();
    char consume();
    bool eof();
};
