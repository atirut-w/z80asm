#include <assembler.hpp>
#include <iostream>

using namespace std;

antlrcpp::Any Assembler::visitInstruction(Z80AsmParser::InstructionContext *ctx)
{
    cout << "instruction: " << ctx->mnemonic()->getText() << endl;

    return visitChildren(ctx);
}
