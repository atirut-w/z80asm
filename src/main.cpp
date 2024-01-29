#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>

auto parse_arguments(int argc, char **argv)
{
    auto parser = std::make_shared<argparse::ArgumentParser>("z80asm");

    parser->add_argument("input")
        .help("input file");

    try
    {
        parser->parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;
        std::cout << *parser << std::endl;
        exit(0);
    }

    return parser;
}

int main(int argc, char **argv)
{
    auto args = parse_arguments(argc, argv);

    return 0;
}
