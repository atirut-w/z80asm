#include <assembler.hpp>

using namespace std;

void Assembler::error(const string &message, int line)
{
    throw runtime_error(to_string(line) + ": " + message);
}

void Assembler::assemble(vector<shared_ptr<Statement>> &statements)
{
    // TODO: Implement
}
