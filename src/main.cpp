#include <argparse/argparse.hpp>
#include <iostream>

using namespace argparse;
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentParser program = ArgumentParser("z80asm");

    program.add_argument("input")
        .help("input file");
    
    program.add_argument("-o", "--output")
        .help("output file")
        .default_value("a.out");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(1);
    }

    return 0;
}
