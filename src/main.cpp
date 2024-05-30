#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <Z80AsmLexer.h>
#include <Z80AsmParser.h>
#include <assembler.hpp>

using namespace std;
using namespace argparse;
using namespace antlr4;

shared_ptr<const ArgumentParser> parse_arguments(int argc, char **argv)
{
    auto parser = make_shared<ArgumentParser>("z80asm");

    parser->add_argument("input")
        .help("input file");

    try
    {
        parser->parse_args(argc, argv);
    }
    catch (const runtime_error &err)
    {
        cout << err.what() << endl;
        cout << *parser << endl;
        exit(0);
    }

    return parser;
}

int main(int argc, char **argv)
{
    auto args = parse_arguments(argc, argv);

    auto abs_path = filesystem::absolute(args->get<string>("input"));
    auto input = make_shared<ifstream>(abs_path);
    if (!*input)
    {
        cout << "error: could not open " << abs_path << " for reading" << endl;
        return 1;
    }

    ANTLRInputStream stream(*input);
    Z80AsmLexer lexer(&stream);
    CommonTokenStream tokens(&lexer);
    Z80AsmParser parser(&tokens);

    tree::ParseTree *tree = parser.program();
    if (lexer.getNumberOfSyntaxErrors() > 0 || parser.getNumberOfSyntaxErrors() > 0)
    {
        return 1;
    }

    Assembler assembler;
    assembler.assemble(tree);

    assembler.elf.save(abs_path.replace_extension(".o").string());

    return 0;
}
