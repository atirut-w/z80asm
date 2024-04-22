#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>

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
    const auto input = filesystem::path(args->get<string>("input"));

    if (!filesystem::exists(input) || filesystem::is_directory(input))
    {
        cout << "error: input file does not exist" << endl;
        return 1;
    }

    return 0;
}
