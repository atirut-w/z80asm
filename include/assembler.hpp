#pragma once
#include <Z80AsmBaseVisitor.h>

class Assembler : public Z80AsmBaseVisitor
{
public:
    virtual antlrcpp::Any visitInstruction(Z80AsmParser::InstructionContext *ctx) override;
};
