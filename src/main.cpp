#include <argparse/argparse.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <tokenizer.hpp>

using namespace argparse;
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentParser program("z80asm");

    program.add_argument("input")
        .help("input file");
    
    program.add_argument("-o", "--output")
        .help("output file")
        .default_value("a.out");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const runtime_error &err)
    {
        cout << err.what() << endl;
        cout << program;
        exit(1);
    }

    ifstream input(program.get<string>("input"));
    if (!input)
    {
        cout << "Error: could not open input file" << endl;
        exit(1);
    }
    input.seekg(0, ios::end);
    size_t size = input.tellg();
    input.seekg(0, ios::beg);
    string buffer(size, ' ');
    input.read(&buffer[0], size);

    Tokenizer tokenizer;

    return 0;
}
