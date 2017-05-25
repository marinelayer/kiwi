#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <bits/mach-o.h>

#define VM_PROT_WRITE 0x02

void __rebase_macho(const struct mach_header* mh, intptr_t slide)
{
	const uint32_t cmd_count = mh->ncmds;
	const struct load_command* const cmds = (struct load_command*)(((char*)mh)+sizeof(struct mach_header));
	const struct load_command* cmd = cmds;
	const struct segment_command_64* linkEditSeg = 0;
	const struct segment_command_64* firstWritableSeg = 0;
	const struct dysymtab_command* dynamicSymbolTable = 0;
	for (uint32_t i = 0; i < cmd_count; ++i) {
		switch (cmd->cmd) {
			case LC_SEGMENT_64: {
					const struct segment_command_64* seg = (struct segment_command_64*)cmd;
					if (strcmp(seg->segname, SEG_LINKEDIT) == 0) linkEditSeg = seg;
					const struct section_64* const sectionsStart =
						(struct section_64*)((char*)seg + sizeof(struct segment_command_64));
					const struct section_64* const sectionsEnd = &sectionsStart[seg->nsects];
					for (const struct section_64* sect=sectionsStart; sect < sectionsEnd; ++sect) {
						const uint8_t type = sect->flags & SECTION_TYPE;
						if (type == S_NON_LAZY_SYMBOL_POINTERS) {
							const uint32_t pointerCount = (uint32_t)(sect->size / sizeof(uintptr_t));
							uintptr_t* const symbolPointers = (uintptr_t*)(sect->addr + slide);
							for (uint32_t j=0; j < pointerCount; ++j) {
								symbolPointers[j] += slide;
							}
						}
					}
					if ((firstWritableSeg == 0) && (seg->initprot & VM_PROT_WRITE)) {
						firstWritableSeg = seg;
					}
				}
				break;
			case LC_DYSYMTAB: {
				dynamicSymbolTable = (struct dysymtab_command *)cmd;
				break;
			}
		}
		cmd = (const struct load_command*)(((char*)cmd)+cmd->cmdsize);
	}
	if (!(linkEditSeg && firstWritableSeg && dynamicSymbolTable)) return;
	const uintptr_t relocBase = firstWritableSeg->vmaddr + slide;
	const struct relocation_info* const relocsStart = (struct relocation_info*)(linkEditSeg->vmaddr + slide + dynamicSymbolTable->locreloff - linkEditSeg->fileoff);
	const struct relocation_info* const relocsEnd = &relocsStart[dynamicSymbolTable->nlocrel];
	for (const struct relocation_info* reloc=relocsStart; reloc < relocsEnd; ++reloc) {
		if (reloc->r_length != 3) abort();
		if (reloc->r_type != X86_64_RELOC_UNSIGNED) abort();
		*((uintptr_t*)(reloc->r_address + relocBase)) += slide;
	}
}

