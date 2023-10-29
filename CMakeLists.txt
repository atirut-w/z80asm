cmake_minimum_required(VERSION 3.22)
project(Z80ASM)

add_executable(z80asm
    "src/main.cpp"
)
target_include_directories(z80asm PRIVATE "include")

add_subdirectory("3rd/argparse")
target_link_libraries(z80asm PRIVATE argparse)
