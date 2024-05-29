#pragma once
#include <Z80AsmBaseVisitor.h>

struct Operand
{
    bool indirect = false;
    Z80AsmParser::OperandContext *operand = nullptr;
};

class Assembler : public Z80AsmBaseVisitor
{
private:
    virtual antlrcpp::Any visitInstruction(Z80AsmParser::InstructionContext *ctx) override;
    virtual antlrcpp::Any visitOperandList(Z80AsmParser::OperandListContext *ctx) override;
    

public:
    void assemble(antlr4::tree::ParseTree *tree);
};
