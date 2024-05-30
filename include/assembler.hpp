#pragma once
#include <Z80AsmBaseVisitor.h>
#include <vector>
#include <cstdint>

struct Operand
{
    bool indirect = false;
    Z80AsmParser::OperandContext *operand = nullptr;
};

class Assembler : public Z80AsmBaseVisitor
{
private:
    void error(antlr4::ParserRuleContext *ctx, const std::string &message);
    void warning(antlr4::ParserRuleContext *ctx, const std::string &message);
    void emit(uint8_t byte);

    virtual antlrcpp::Any visitInstruction(Z80AsmParser::InstructionContext *ctx) override;
    virtual antlrcpp::Any visitOperandList(Z80AsmParser::OperandListContext *ctx) override;
    virtual antlrcpp::Any visitOperand(Z80AsmParser::OperandContext *ctx) override;

public:
    std::vector<uint8_t> code;

    void assemble(antlr4::tree::ParseTree *tree);
};
