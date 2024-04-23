#include <tokenizer.hpp>

using namespace std;

Tokenizer::Tokenizer(std::shared_ptr<std::istream> stream) : reader(stream)
{
}
