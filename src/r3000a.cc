#include <r3000a.hh>
#include <stdio.h>

void R3000A::reset()
{
    PC = 0xBFC00000;
    isPaused = false;

    reg[0] = 0;
}

void R3000A::cycle()
{
    if (isPaused) return;

    //Fetch
    instruction = mem->read32(PC);
    PC+=4;
    //Decode
    opcode = (instruction & 0xFC000000) >> 26;
    subOpcode = (instruction & 0x2F);

    rt = (instruction & 0x1F0000) >> 16;
    rs = (instruction & 0x3E00000) >> 21;
    rd = (instruction & 0xF800) >> 11;
    imm = (instruction & 0xFFFF);

    base = rs;
    offset = imm;
    //Execute
    switch(opcode)
    {
    case 0x0: // SPECIAL
        switch (subOpcode)
        {
        case 0x0: //NOP???? or SLL
            break;
        case 0x25:
            OR();
            break;
        case 0x2B:
            SLTU();
            break;
        default:
            fprintf(stderr, "sub opcode not implemented: 0x%x\n", subOpcode);
            printf("instruction: 0x%x, PC: 0x%x\n", instruction, PC);
            isPaused = true;
            break;
        }
        break;
    case 0x2:
        J();
        break;
    case 0x5:
        BNE();
        break;
    case 0x8:
        ADDI();
        break;
    case 0x9:
        ADDIU();
        break;
    case 0x10:
        MTC0();
        break;
    case 0xF: // LUI
        LUI();
        break;
    case 0xD:
        ORI();
        break;
    case 0x23:
        LW();
        break;
    case 0x2B:
        SW();
        break;
    default:
        fprintf(stderr, "opcode not implemented: 0x%x\n", opcode);
        printf("instruction: 0x%x, PC: 0x%x\n", instruction, PC);
        isPaused = true;
        break;
    }

    if (isDelay)
    {
        PC = jumpAddr;
        isDelay = false;
    }

    if (isBranched)
    {
        isBranched = false;
        isDelay = true;
    }
}
