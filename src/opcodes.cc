#include <r3000a.hh>
#include <stdio.h>

std::string R3000A::cop0RegToName(uint8_t reg)
{
    switch (reg)
    {
    case 3:	    return "BPC	Breakpoint Program Counter";
    case 5:	    return "BDA	Breakpoint Data Address";
    case 6:	    return "TAR	Target Address";
    case 7:	    return "DCIC	Debug and Cache Invalidate Control";
    case 8:	    return "BadA	Bad Address";
    case 9:	    return "BDAM	Breakpoint Data Address Mask";
    case 11:	return "BPCM	Breakpoint Program Counter Mask";
    case 12:	return "SR	Status Register";
    case 13:	return "CAUSE	Cause of the last exception";
    case 14:	return "EPC	Exception Program Counter";
    case 15:	return "PRID	Processor Revision Identifier";
    default:
        return "unimplemnted";
        break;
    }
}


void R3000A::J()
{
    jumpAddr = ((instruction & 0x3FFFFFF) << 2) | (PC & 0xF0000000);
    isBranched = true;
}

void R3000A::ADDI()
{
    reg[rt] = reg[rs] + static_cast<int16_t>(imm); 
}

void R3000A::ADDIU()
{
    //Not complete
    reg[rt] = reg[rs] + imm; 
}

void R3000A::MTC0()
{
    cop0Reg[rd] = reg[rt];

    printf("cop0 reg %s set to 0x%x\n", cop0RegToName(rd).c_str(), reg[rt]);
}

void R3000A::OR()
{
    reg[rd] = reg[rs] | reg[rt];
}

void R3000A::LUI()
{
    reg[rt] = (imm << 16 | 0x0000);
    // fprintf(stderr, "rt: 0x%x, reg[rt]: 0x%x\n", rt, reg[rt]);
}

void R3000A::LW()
{
    uint32_t vaddr = reg[base] + static_cast<int16_t>(offset);
    reg[rt] = mem->read32(vaddr);
}

void R3000A::SLTU()
{
    int16_t cmp = reg[rs] - static_cast<int16_t>(imm);
    if (reg[rs] < cmp)
    {
        reg[rt] = 1;
    }
    else 
    {
        reg[rt] = 0;
    }
}

void R3000A::BNE()
{
    if (reg[rt] != reg[rs]) 
    {
    // fprintf(stderr, "reg[rs]: 0x%x, reg[rt]: 0x%x\n", reg[rs], reg[rt]);
        
        jumpAddr = static_cast<int16_t>(offset << 2) + PC;
    // fprintf(stderr, "PC: 0x%x, jumpAddr: 0x%x, offset: 0x%x\n", PC, jumpAddr, static_cast<int16_t>(offset << 2) );
        
        // exit(0);
        isBranched = true;
    }
}

void R3000A::ORI()
{
    // fprintf(stderr, "instruction: 0x%x\n", instruction);
    // fprintf(stderr, "rs: 0x%x, reg[rs]: 0x%x\n", rs, reg[rs]);
    reg[rt] = imm | reg[rs]; 
    // fprintf(stderr, "rt: 0x%x, reg[rt]: 0x%x\n", rt, reg[rt]);
}

void R3000A::SW()
{
    uint32_t vaddr = reg[base] + offset;
    if (vaddr == 0xfffe0130) {
        // fprintf(stderr, "vaddr: 0x%x, base: 0x%x, offset:0x%x, reg[base]: 0x%x\n", vaddr, base, offset, reg[base]);
        // fprintf(stderr, "PC: 0x%x, instrution: 0x%x\n", PC, instruction);
    }
    mem->write32(vaddr, reg[rt]);
}
