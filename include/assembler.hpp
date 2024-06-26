#pragma once
#include <Z80AsmBaseVisitor.h>
#include <vector>
#include <cstdint>
#include <elfio/elfio.hpp>
#include <module.hpp>

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
    void set_section(const std::string &name);
    void symbol_type(int stt);

    virtual antlrcpp::Any visitLabel(Z80AsmParser::LabelContext *ctx) override;
    virtual antlrcpp::Any visitInstruction(Z80AsmParser::InstructionContext *ctx) override;
    virtual antlrcpp::Any visitOperandList(Z80AsmParser::OperandListContext *ctx) override;
    virtual antlrcpp::Any visitOperand(Z80AsmParser::OperandContext *ctx) override;
    virtual antlrcpp::Any visitNumber(Z80AsmParser::NumberContext *ctx) override;

public:
    Assembler();

    Module module;
    int current_section;

    void assemble(antlr4::tree::ParseTree *tree);
};
