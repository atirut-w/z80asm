#pragma once
#include <string>
#include <vector>
#include <istream>
#include <memory>
#include <tokenizer.hpp>
#include <variant>

struct Statement
{
    virtual ~Statement() = default; // Force polymorphism for casting to derived types
};

struct Label : Statement
{
    std::string name;

    Label(std::string name) : name(name) {}
};

enum class Mnemonic
{
    // Load group
    LD,
    PUSH,
    POP,

    // Exchange, block transfer, and search
    EX,
    EXX,
    LDI,
    LDIR,
    LDD,
    LDDR,
    CPI,
    CPIR,
    CPD,
    CPDR,

    // 8-bit arithmetic
    ADD,
    ADC,
    SUB,
    SBC,
    AND,
    OR,
    XOR,
    CP,
    INC,
    DEC,

    // Jump group
    JP,
    JR,
    DJNZ,

    // I/O group
    IN,
    INI,
    INIR,
    IND,
    INDR,
    OUT,
    OUTI,
    OTIR,
    OUTD,
    OUTDR,
};

struct Operand
{
    std::variant<std::string, int> value;
    bool indirect = false;
};

struct Instruction : Statement
{
    Mnemonic mnemonic;
    std::vector<Operand> operands;
};

class Parser
{
private:
    std::vector<Token> tokens;
    int cur = 0;

    void error(const std::string &message);
    const Token& consume();
    const Token& peek();
    const Token& peek(int offset);

public:
    std::vector<std::shared_ptr<Statement>> statements;
    std::vector<std::string> errors;

    Parser(const std::vector<Token> tokens) : tokens(tokens) {}
    void parse();
};
