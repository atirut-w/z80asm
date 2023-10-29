#include <string>
#include <vector>

class Token
{
public:
    std::string string;
    int line;
    int column;
};

class Tokenizer
{
private:
    Token current_token;
    int line;
    int column;
public:
    std::vector<Token> tokens;

    void tokenize(std::string buffer);
};
