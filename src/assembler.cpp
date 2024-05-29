#include <assembler.hpp>
#include <iostream>
#include <stdexcept>

using namespace std;

void Assembler::error(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    throw runtime_error(to_string(ctx->getStart()->getLine()) + ":" + to_string(ctx->getStart()->getCharPositionInLine()) + ": error: " + message);
}

void Assembler::warning(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    cout << to_string(ctx->getStart()->getLine()) << ":" << to_string(ctx->getStart()->getCharPositionInLine()) << ": warning: " << message << endl;
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
        
        if (!operands[0].indirect && operands[0].operand->reg8()) // LD r, *
        {
            if (auto number = operands[1].operand->number()) // LD r, n
            {
                error(ctx, "TODO: Implement LD r, n"); // TODO: Implement LD r, n
            }
        }
    }

    return visitChildren(ctx);
}

antlrcpp::Any Assembler::visitOperandList(Z80AsmParser::OperandListContext *ctx)
{
    vector<Operand> operands;

    for (auto operand : ctx->operand())
    {
        Operand op;
        
        if (operand->LPAREN())
        {
            op.indirect = true;
            op.operand = operand->operand();
        }
        else
        {
            op.indirect = false;
            op.operand = operand;
        }

        operands.push_back(op);
    }

    return operands;
}

void Assembler::assemble(antlr4::tree::ParseTree *tree)
{
    visit(tree);
    // TODO: Solve symbols
}
