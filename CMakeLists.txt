cmake_minimum_required(VERSION 3.22)
project("z80asm")

# Third-party libraries
add_subdirectory("3rd/argparse")
add_subdirectory("3rd/antlr4-cpp-runtime")
add_subdirectory("3rd/elfio")

# ANTLR stuff
add_custom_command(
    COMMENT "Generating parser"
    MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/Z80Asm.g4"
    OUTPUT
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmBaseListener.h"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmBaseListener.cpp"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmBaseVisitor.h"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmBaseVisitor.cpp"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmLexer.h"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmLexer.cpp"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmListener.h"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmListener.cpp"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmParser.h"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmParser.cpp"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmVisitor.h"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmVisitor.cpp"
    BYPRODUCTS
        "${CMAKE_SOURCE_DIR}/parser/Z80Asm.interp"
        "${CMAKE_SOURCE_DIR}/parser/Z80Asm.tokens"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmLexer.interp"
        "${CMAKE_SOURCE_DIR}/parser/Z80AsmLexer.tokens"
    COMMAND antlr4 -visitor -o "${CMAKE_SOURCE_DIR}/parser" "${CMAKE_SOURCE_DIR}/Z80Asm.g4"
)

add_executable("z80asm"
    "src/main.cpp"
    "src/assembler.cpp"
    "src/module.cpp"

    # Generated parser
    "parser/Z80AsmBaseListener.cpp"
    "parser/Z80AsmBaseVisitor.cpp"
    "parser/Z80AsmLexer.cpp"
    "parser/Z80AsmListener.cpp"
    "parser/Z80AsmParser.cpp"
    "parser/Z80AsmVisitor.cpp"
)
target_compile_features("z80asm" PRIVATE cxx_std_17)
target_include_directories("z80asm" PRIVATE "include" "parser" "3rd/antlr4-cpp-runtime/runtime/src") # Why does ANTLR do this to me
target_link_libraries("z80asm" PRIVATE "argparse" "antlr4_static" "elfio")
