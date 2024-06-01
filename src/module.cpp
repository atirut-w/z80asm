#include <module.hpp>
#include <map>

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

elfio Module::generate_elf()
{
    elfio elf;
    elf.create(ELFCLASS32, ELFDATA2LSB);
    elf.set_type(ET_REL);
    elf.set_machine(EM_Z80);
    elf.set_os_abi(ELFOSABI_NONE);

    int auto_offset = 0;
    for (auto &section : sections)
    {
        if (section.org == (uint16_t)-1)
        {
            section.org = auto_offset;
        }
        
        auto elf_section = elf.sections.add(section.name);
        elf_section->set_type(SHT_PROGBITS);
        if (SHFLAGS.find(section.name) != SHFLAGS.end())
        {
            elf_section->set_flags(SHFLAGS.at(section.name));
        }
        elf_section->set_data(reinterpret_cast<const char *>(section.data.data()), section.data.size());
        elf_section->set_addr_align(1);

        auto segment = elf.segments.add();
        segment->set_type(PT_LOAD);
        segment->set_virtual_address(section.org);
        segment->set_physical_address(section.org);
        if (PFLAGS.find(section.name) != PFLAGS.end())
        {
            segment->set_flags(PFLAGS.at(section.name));
        }
        segment->set_align(1);
        segment->add_section_index(elf_section->get_index(), elf_section->get_addr_align());

        section.index = elf_section->get_index();
        auto_offset += section.data.size();
    }

    if (symbols.size() > 0)
    {
        auto strtab = elf.sections.add(".strtab");
        strtab->set_type(SHT_STRTAB);
        strtab->set_entry_size(elf.get_default_entry_size(SHT_STRTAB));

        auto symtab = elf.sections.add(".symtab");
        symtab->set_type(SHT_SYMTAB);
        symtab->set_info(symbols.size() + 1); // Wtf?
        symtab->set_link(strtab->get_index());
        symtab->set_entry_size(elf.get_default_entry_size(SHT_SYMTAB));
    
        auto string_accessor = string_section_accessor(strtab);
        auto symtab_accessor = symbol_section_accessor(elf, symtab);
        for (auto &symbol : symbols)
        {
            symtab_accessor.add_symbol(
                string_accessor,
                symbol.name.c_str(),
                sections[symbol.section].org + symbol.offset,
                0,
                symbol.type,
                STV_DEFAULT,
                sections[symbol.section].index
            );
        }
    }

    return elf;
}
