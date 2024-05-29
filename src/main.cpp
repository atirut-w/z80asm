#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <parser.hpp>
#include <assembler.hpp>

using namespace std;
using namespace argparse;

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
    ifstream input(abs_path);
    if (!input)
    {
        cout << "error: could not open " << abs_path << " for reading" << endl;
        return 1;
    }

    Parser parser;
    auto statements = parser.parse(input);
    if (parser.errors.size() > 0)
    {
        for (auto &error : parser.errors)
            cerr << abs_path.string() << ":" << error << endl;
    }

    Assembler assembler;
    try
    {
        assembler.assemble(statements);
    }
    catch (const runtime_error &err)
    {
        cerr << abs_path.string() << ": error: " << err.what() << endl;
        return 1;
    }

    ofstream output(abs_path.replace_extension(".bin"), ios::binary);
    output.write(reinterpret_cast<const char *>(assembler.program.data()), assembler.program.size());

    return 0;
}
