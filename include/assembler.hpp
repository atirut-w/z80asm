#pragma once
#include <Z80AsmBaseVisitor.h>

class Assembler : public Z80AsmBaseVisitor
{
private:
    virtual antlrcpp::Any visitInstruction(Z80AsmParser::InstructionContext *ctx) override;

public:
    void assemble(antlr4::tree::ParseTree *tree);
};
