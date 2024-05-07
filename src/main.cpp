#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <tokenizer.hpp>
#include <parser.hpp>

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

    string abs_path = filesystem::absolute(args->get<string>("input")).string();
    auto input = make_shared<ifstream>(abs_path);
    if (!*input)
    {
        cout << "error: could not open `" << abs_path << "` for reading" << endl;
        return 1;
    }

    Tokenizer tokenizer(input);
    tokenizer.tokenize();

    Parser parser;
    parser.parse(tokenizer.tokens);

    if (!parser.errors.empty())
    {
        for (const auto &error : parser.errors)
        {
            cout << abs_path << ":" << error << endl;
        }
        return 1;
    }

    return 0;
}
