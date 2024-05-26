#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
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
    ifstream input(abs_path);
    if (!input)
    {
        cout << "error: could not open `" << abs_path << "` for reading" << endl;
        return 1;
    }

    Parser parser;
    auto statements = parser.parse(input);

    return 0;
}
