#include <assembler.hpp>

using namespace std;

void Assembler::error(const string &message, int line)
{
    throw runtime_error(to_string(line) + ": " + message);
}

void Assembler::assemble(vector<shared_ptr<Statement>> &statements)
{
    for (auto &statement : statements)
    {
        // TODO: Labels
        if (auto instruction = dynamic_pointer_cast<Instruction>(statement))
        {
            auto mnemonic = instruction->mnemonic;
            auto operands = instruction->operands;
            if (mnemonic == "ld")
            {
                if (operands.size() < 2)
                {
                    error("ld requires at least two operands", instruction->line);
                    continue;
                }

                if (operands[0].type == Operand::Type::Reg8 && !operands[0].indirect) // LD r, *
                {
                    // TODO: Implement
                }
            }
        }
    }

    // TODO: Solve labels
}
