#ifndef MEMORY_HH
#define MEMORY_HH

#include <stdint.h>

class Memory
{
public:
    void loadRom();

    // template <typename T>
    // void write(uint32_t addr, T data);

    // template <typename T>
    // T read(uint32_t addr);

    void write8(uint32_t addr, uint8_t data);
    void write16(uint32_t addr, uint16_t data);
    void write32(uint32_t addr, uint32_t data);

    uint8_t read8(uint32_t addr);
    uint16_t read16(uint32_t addr);
    uint32_t read32(uint32_t addr);
private:
    uint8_t ram[200000];
    uint8_t* rom;
};

#endif
