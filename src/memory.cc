#include <memory.hh>

#include <stdio.h>
#include <fstream>
#include <cstring>
#include <vector>

void Memory::loadRom()
{
    std::ifstream file("SCPH1001.BIN", std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        fprintf(stderr, "failed to open bios\n");
        return;
    }

    // Get file size
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate vector
    std::vector<uint8_t> buffer(static_cast<size_t>(size));

    // Read entire file
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    rom = new uint8_t[buffer.size()];
    std::memcpy(rom, buffer.data(), buffer.size());
}

void Memory::write8(uint32_t addr, uint8_t data)
{
    fprintf(stderr, "write8 unimplemented\n");
}

void Memory::write16(uint32_t addr, uint16_t data)
{
    fprintf(stderr, "write16 unimplemented\n");
}

void Memory::write32(uint32_t addr, uint32_t data)
{
    if (addr < 0x200000) 
    {
        //Ram
        ram[addr] = data;
        return;
    }
    if (addr >= 0xA0000000 && addr < 0xA0200000) 
    {
        //Ram
        ram[addr] = data;
        return;
    }

    if (addr >= 0x1F801000 && addr < 0x1F802000){
        //IO
        return;
    }

    fprintf(stderr, "write32 unimplemented. addr: 0x%x, data: 0x%x\n", addr, data);
}

uint8_t Memory::read8(uint32_t addr)
{
    fprintf(stderr, "read8 unimplemented\n");

    return 0;
}

uint16_t Memory::read16(uint32_t addr)
{
    fprintf(stderr, "read16 unimplemented\n");

    return 0;
}

uint32_t Memory::read32(uint32_t addr)
{
    // fprintf(stderr, "[read32] addr: 0x%x\n", addr);

    if (addr <= 0xA0000000 && addr < 0xA0200000)
    {
        return *reinterpret_cast<uint32_t*>(&ram[addr & 0x002FFFFF]);
    }

    if (addr >= 0xBFC00000)
    {
        return *reinterpret_cast<uint32_t*>(&rom[addr - 0xBFC00000]);
    }

    fprintf(stderr, "read32 unimplemented. addr: 0x%x\n", addr);
    exit(0);

    return 0;
}
