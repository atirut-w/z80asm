#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <tokenizer.hpp>

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

    auto input = make_shared<ifstream>(args->get<string>("input"));
    if (!*input)
    {
        cout << "error: could not open `" << args->get<string>("input") << "` for reading" << endl;
        return 1;
    }

    Tokenizer tokenizer(input);
    try
    {
        tokenizer.tokenize();
    }
    catch (const runtime_error &err)
    {
        auto reader = tokenizer.get_reader();
        cout << filesystem::absolute(args->get<string>("input")).string() << ":" << reader.get_line() << ":" << reader.get_column() << ": error: " << err.what() << endl;
    }

    return 0;
}
