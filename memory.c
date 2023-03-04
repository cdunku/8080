#include <stdint.h>
#include "cpu.h"

uint8_t readByte(i8080* const s, uint16_t addr)
{
    return s->memory[addr & 0xFFFF];
}

uint16_t readWord(i8080* const s, uint16_t addr)
{
    return (readByte(s, addr + 1) << 8 | readByte(s, addr)); 
}

void writeByte(i8080* const s, uint16_t addr, uint8_t byte)
{
    s->memory[addr & 0xFFFF] = byte;   
}

void writeWord(i8080* const s, uint16_t addr, uint16_t word)
{
    writeByte(s, addr, word & 0xFF);
    writeByte(s, addr + 1, (word >> 8) & 0xFF);
}

uint8_t nextByte(i8080* const s)
{
    return readByte(s, s->pc++);
}

uint16_t nextWord(i8080* const s)
{
    uint16_t word = readWord(s, s->pc);
    s->pc += 2;
    return word;
}
