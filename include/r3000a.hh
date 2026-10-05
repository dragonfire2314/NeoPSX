#ifndef R3000A_HH
#define R3000A_HH

#include <stdint.h>
#include <memory.hh>
#include <string>

class R3000A 
{
public:
    R3000A(Memory* _mem) 
    {
        mem = _mem;
    }
    void reset();
    void cycle();
private:
    uint32_t reg[32];

    uint32_t PC;

    bool isPaused = true;
    
    Memory* mem;

    uint8_t opcode;
    uint8_t subOpcode;
    uint32_t instruction;

    uint8_t rt;
    uint8_t rs;
    uint8_t rd;
    uint8_t base;
    uint16_t imm;
    uint16_t offset;

    // std::function<int(int, int)> delaySlot;
    bool isBranched = false;
    bool isDelay = false;
    uint32_t jumpAddr;
private:
    uint32_t cop0Reg[16];

    std::string cop0RegToName(uint8_t reg);
private:
    void LUI();
    void LW();
    void SLTU();
    void ADDI();
    void ADDIU();
    void BNE();
    void OR();
    void ORI();
    void SW();
    void J();
    void MTC0();
};

#endif
