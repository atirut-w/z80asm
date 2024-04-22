#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>
#include <input_reader.hpp>
#include <fstream>

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

    InputReader reader(args->get<string>("input"));
    while (!reader.eof())
    {
        cout << reader.peek();
        reader.die("unexpected character");
        reader.consume();
    }

    return 0;
}
