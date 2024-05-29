#include <assembler.hpp>
#include <iostream>
#include <stdexcept>

using namespace std;

void Assembler::error(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    throw runtime_error(to_string(ctx->getStart()->getLine()) + ":" + to_string(ctx->getStart()->getCharPositionInLine()) + ": error: " + message);
}

antlrcpp::Any Assembler::visitInstruction(Z80AsmParser::InstructionContext *ctx)
{
    auto mnemonic = ctx->mnemonic()->getText();
    vector<Operand> operands;
    if (ctx->operandList())
    {
        operands = any_cast<vector<Operand>>(visit(ctx->operandList()));
    }
    
    cout << "Instruction: " << mnemonic << endl;
    cout << "Operands: " << endl;
    for (auto operand : operands)
    {
        cout << "  " << (operand.indirect ? "Indirect" : "Direct") << ": " << operand.operand->getText() << endl;
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
