#include <assembler.hpp>
#include <iostream>
#include <stdexcept>
#include <codegen.hpp>

using namespace std;

void Assembler::error(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    throw runtime_error(to_string(ctx->getStart()->getLine()) + ":" + to_string(ctx->getStart()->getCharPositionInLine()) + ": error: " + message);
}

void Assembler::warning(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    cout << to_string(ctx->getStart()->getLine()) << ":" << to_string(ctx->getStart()->getCharPositionInLine()) << ": warning: " << message << endl;
}

void Assembler::emit(uint8_t byte)
{
    code.push_back(byte);
}

antlrcpp::Any Assembler::visitInstruction(Z80AsmParser::InstructionContext *ctx)
{
    auto mnemonic = ctx->mnemonic()->getText();
    vector<Operand> operands;
    if (ctx->operandList())
    {
        operands = any_cast<vector<Operand>>(visit(ctx->operandList()));
    }
    
    if (mnemonic == "ld")
    {
        if (operands.size() < 2)
        {
            error(ctx, "ld instruction requires at least two operands");
        }
        
        if (!operands[0].indirect) // LD rn, *
        {
            if (operands[0].operand->reg8()) // LD r, *
            {
                if (!operands[1].indirect)
                {
                    if (auto reg8 = operands[1].operand->reg8()) // LD r, r'
                    {
                        emit(LD_R_R | (REG8.at(operands[0].operand->getText()) << 3) | REG8.at(reg8->getText()));
                    }
                    else if (auto number = operands[1].operand->number()) // LD r, n
                    {
                        emit(LD_R_N | (REG8.at(operands[0].operand->getText()) << 3));
                        emit(any_cast<int>(visit(number)));
                    }
                }
            }
        }
    }
    else if (mnemonic == "halt")
    {
        emit(HALT);
    }

    return visitChildren(ctx);
}

antlrcpp::Any Assembler::visitOperandList(Z80AsmParser::OperandListContext *ctx)
{
    vector<Operand> operands;

    for (auto operand : ctx->operand())
    {
        operands.push_back(any_cast<Operand>(visit(operand)));
    }

    return operands;
}

antlrcpp::Any Assembler::visitOperand(Z80AsmParser::OperandContext *ctx)
{
    Operand operand;
    if (ctx->LPAREN())
    {
        operand.indirect = true;
        operand.operand = ctx->operand();
    }
    else
    {
        operand.indirect = false;
        operand.operand = ctx;
    }

    return operand;
}

antlrcpp::Any Assembler::visitNumber(Z80AsmParser::NumberContext *ctx)
{
    return stoi(ctx->getText(), nullptr, 0);
}

void Assembler::assemble(antlr4::tree::ParseTree *tree)
{
    visit(tree);
    // TODO: Solve symbols
}
