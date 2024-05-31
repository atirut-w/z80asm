#include <assembler.hpp>
#include <iostream>
#include <stdexcept>
#include <codegen.hpp>

using namespace std;
using namespace ELFIO;

const map<string, int> SHFLAGS = {
    {".text", SHF_ALLOC | SHF_EXECINSTR},
    {".data", SHF_ALLOC | SHF_WRITE},
    {".bss", SHF_ALLOC | SHF_WRITE},
};

const map<string, int> PFLAGS = {
    {".text", PF_R | PF_X},
    {".data", PF_R | PF_W},
    {".bss", PF_R | PF_W},
};

Assembler::Assembler()
{
    elf.create(ELFCLASS32, ELFDATA2LSB);
    elf.set_type(ET_REL);
    elf.set_machine(EM_Z80);

    set_section(".text");
}

void Assembler::error(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    throw runtime_error(to_string(ctx->getStart()->getLine()) + ":" + to_string(ctx->getStart()->getCharPositionInLine()) + ": error: " + message);
}

void Assembler::warning(antlr4::ParserRuleContext *ctx, const std::string &message)
{
    cout << to_string(ctx->getStart()->getLine()) << ":" << to_string(ctx->getStart()->getCharPositionInLine()) << ": warning: " << message << endl;
}

void Assembler::emit(uint8_t byte)
{
    current_section->data.push_back(byte);
}

void Assembler::set_section(const std::string &name)
{
    if (sections.find(name) == sections.end())
    {
        sections[name] = Section();
    }
    current_section = &sections[name];
}

antlrcpp::Any Assembler::visitLabel(Z80AsmParser::LabelContext *ctx)
{
    auto name = ctx->NAME()->getText();
    if (symbols.find(name) != symbols.end())
    {
        error(ctx, "symbol '" + name + "' already defined");
    }
    symbols[name] = {current_section, (uint16_t)current_section->data.size()};

    return visitChildren(ctx);
}

antlrcpp::Any Assembler::visitInstruction(Z80AsmParser::InstructionContext *ctx)
{
    auto mnemonic = ctx->mnemonic()->getText();
    vector<Operand> operands;
    if (ctx->operandList())
    {
        operands = any_cast<vector<Operand>>(visit(ctx->operandList()));
    }
    
    if (mnemonic == "ld")
    {
        if (operands.size() < 2)
        {
            error(ctx, "ld instruction requires at least two operands");
        }
        
        if (!operands[0].indirect) // LD rn, *
        {
            if (operands[0].operand->reg8()) // LD r, *
            {
                if (!operands[1].indirect)
                {
                    if (auto reg8 = operands[1].operand->reg8()) // LD r, r'
                    {
                        emit(LD_R_R | (REG8.at(operands[0].operand->getText()) << 3) | REG8.at(reg8->getText()));
                    }
                    else if (auto number = operands[1].operand->number()) // LD r, n
                    {
                        emit(LD_R_N | (REG8.at(operands[0].operand->getText()) << 3));
                        emit(any_cast<int>(visit(number)));
                    }
                }
            }
        }
    }
    else if (mnemonic == "halt")
    {
        emit(HALT);
    }

    return visitChildren(ctx);
}

antlrcpp::Any Assembler::visitOperandList(Z80AsmParser::OperandListContext *ctx)
{
    vector<Operand> operands;

    for (auto operand : ctx->operand())
    {
        operands.push_back(any_cast<Operand>(visit(operand)));
    }

    return operands;
}

antlrcpp::Any Assembler::visitOperand(Z80AsmParser::OperandContext *ctx)
{
    Operand operand;
    if (ctx->LPAREN())
    {
        operand.indirect = true;
        operand.operand = ctx->operand();
    }
    else
    {
        operand.indirect = false;
        operand.operand = ctx;
    }

    return operand;
}

antlrcpp::Any Assembler::visitNumber(Z80AsmParser::NumberContext *ctx)
{
    return stoi(ctx->getText(), nullptr, 0);
}

void Assembler::assemble(antlr4::tree::ParseTree *tree)
{
    visit(tree);
    
    int auto_offset = 0;
    for (auto &pair : sections)
    {
        auto &name = pair.first;
        auto &section = pair.second;
        if (section.org == (uint16_t)-1)
        {
            sections[name].org = auto_offset; // For symbol resolution
            section.org = auto_offset;
        }
        
        auto elf_section = elf.sections.add(name);
        elf_section->set_type(SHT_PROGBITS);
        if (SHFLAGS.find(name) != SHFLAGS.end())
        {
            elf_section->set_flags(SHFLAGS.at(name));
        }
        elf_section->set_data(reinterpret_cast<const char *>(section.data.data()), section.data.size());
        elf_section->set_addr_align(1);

        auto segment = elf.segments.add();
        segment->set_type(PT_LOAD);
        segment->set_virtual_address(section.org);
        segment->set_physical_address(section.org);
        if (PFLAGS.find(name) != PFLAGS.end())
        {
            segment->set_flags(PFLAGS.at(name));
        }
        segment->set_align(1);
        segment->add_section_index(elf_section->get_index(), elf_section->get_addr_align());

        auto_offset += section.data.size();
    }
}
