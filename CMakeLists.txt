cmake_minimum_required(VERSION 3.22)
project("z80asm")

# Third-party libraries
add_subdirectory("3rd/argparse")
find_package(Boost REQUIRED)

add_executable("z80asm"
    "src/main.cpp"
    "src/parser.cpp"
)
target_compile_features("z80asm" PRIVATE cxx_std_17)
target_include_directories("z80asm" PRIVATE "include")
target_link_libraries("z80asm" PRIVATE "argparse")
