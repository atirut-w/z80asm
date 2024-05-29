#include <assembler.hpp>
#include <iostream>

using namespace std;

antlrcpp::Any Assembler::visitInstruction(Z80AsmParser::InstructionContext *ctx)
{
    cout << "instruction: " << ctx->mnemonic()->getText() << endl;

    return visitChildren(ctx);
}

void Assembler::assemble(antlr4::tree::ParseTree *tree)
{
    visit(tree);
    // TODO: Solve symbols
}
