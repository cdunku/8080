#ifndef I8080_MEMORY_
#define I8080_MEMORY_

#include "cpu.h"

uint8_t readByte(i8080* const s, uint16_t addr);
uint16_t readWord(i8080* const s, uint16_t addr);

void writeByte(i8080* const s, uint16_t addr, uint8_t byte);
void writeWord(i8080* const s, uint16_t addr, uint16_t word);

uint8_t nextByte(i8080* const s);
uint16_t nextWord(i8080* const s);

void emu_out(i8080* const s, uint8_t port);
uint8_t emu_in(i8080* const s, uint8_t port);

#endif // I8080_MEMORY_
