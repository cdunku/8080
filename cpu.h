#ifndef I8080_CPU_
#define I8080_CPU_
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    /* REGISTERS AND FLAGS  */
    uint8_t memory[0x10000];

    uint8_t a, b, c, d, e, h, l;
    bool sf, zf, cf, hf, pf;

    uint16_t pc, sp;

    unsigned long cyc;

    /* INTERRUPTS AND HALT */
    bool halt, inte_pending, inte_happened;
    uint8_t inte_vector;

    /* I/O PORTS */

    uint8_t offset_shift, shift_0, shift_1;

} i8080;

struct instruction
{
    unsigned long cycle;
    char *disassemble;
};

void init_state(i8080* const s);
void cpu_step(i8080* const s);
void interrupt_handle(i8080* const s, uint8_t opcode);
void debug_output(i8080* const s, bool print);

#endif // I8080_CPU_
