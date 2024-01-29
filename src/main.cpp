#include <argparse/argparse.hpp>
#include <memory>
#include <iostream>
#include <filesystem>

std::shared_ptr<const argparse::ArgumentParser> parse_arguments(int argc, char **argv)
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
    const auto input = std::filesystem::path(args->get<std::string>("input"));

    if (!std::filesystem::exists(input) || std::filesystem::is_directory(input))
    {
        std::cout << "error: input file does not exist" << std::endl;
        return 1;
    }

    return 0;
}
