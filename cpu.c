#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

#define SET_SZP(s, value) \
{ \
  s->sf = (value & 0x80) != 0; \
  s->zf = (value == 0); \
  s->pf = parity(value); \
}

#define PAIR(HIGH, LOW) ((((HIGH) << 8) | ((LOW) & 0xFF)) & 0xFFFF)

struct instruction instructions[256] =
{
  {4, "NOP"}, // 0x00
  {10, "LXI B, $"}, // 0x01
  {7, "STAX B"}, // 0x02
  {5, "INX B"}, // 0x03
  {5, "INR B"}, // 0x04
  {5, "DCR B"}, // 0x05
  {7, "MVI B, #"}, // 0x06
  {4, "RLC"}, // 0x07
  {4, "NOP"}, // 0x08
  {10, "DAD B"}, // 0x09
  {7, "LDAX B"}, // 0x0a
  {5, "DCX B"}, // 0x0b
  {5, "INR C"}, // 0x0c
  {5, "DCR C"}, // 0x0d
  {7, "MVI C, #"}, // 0x0e
  {4, "RRC",}, // 0x0f
  {4, "NOP"}, // 0x10
  {10, "LXI D, $"}, // 0x11
  {7, "STAX D"}, // 0x12
  {5, "INX D"}, // 0x13
  {5, "INR D"}, // 0x14
  {5, "DCR D"}, // 0x15
  {7, "MVI D, #"}, // 0x16
  {4, "RAL"}, // 0x17
  {4, "NOP"}, // 0x18
  {10, "DAD D"}, // 0x19
  {7, "LDAX D"}, // 0x1a
  {5, "DCX D"}, // 0x1b
  {5, "INR E"}, // 0x1c
  {5, "DCR E"}, // 0x1d
  {7, "MVI E, #"}, // 0x1e
  {4, "RAR"}, // 0x1f
  {4, "NOP"}, // 0x20
  {10, "LXI H, $"}, // 0x21
  {16, "SHLD, $"}, // 0x22
  {5, "INX H"}, // 0x23
  {5, "INR H"}, // 0x24
  {5, "DCR H"}, // 0x25
  {7, "MVI H, #"}, // 0x26
  {4, "DAA"}, // 0x27
  {4, "NOP"}, // 0x28
  {10, "DAD H"}, // 0x29
  {16, "LHLD, $"}, // 0x2a
  {5, "DCX H"}, // 0x2b
  {5, "INR L"}, // 0x2c
  {5, "DCR L"}, // 0x2d
  {7, "MVI L, #"}, // 0x2e
  {4, "CMA"}, // 0x2f
  {4 ,"NOP"}, // 0x30
  {10, "LXI SP, $"}, // 0x31
  {13, "STA, $"}, // 0x32
  {5, "INX SP"}, // 0x33
  {10, "INR M"}, // 0x34
  {10, "DCR M"}, // 0x35
  {10, "MVI M, #"}, /// 0x36
  {4, "STC"}, // 0x37
  {4, "NOP"}, // 0x38
  {10, "DAD SP"}, // 0x39
  {13, "LDA, $"}, // 0x3a
  {5, "DCX SP"}, // 0x3b
  {5, "INR A"}, // 0x3c
  {5, "DCR A"}, // 0x3d
  {7, "MVI A, #"}, // 0x3e
  {4, "CMC"}, // 0x3f
  {5, "MOV B, B"}, // 0x40
  {5, "MOV B, C"}, // 0x41
  {5, "MOV B, D"}, // 0x42
  {5, "MOV B, E"}, // 0x43
  {5, "MOV B, H"}, // 0x44
  {5, "MOV B, L"}, // 0x45
  {7, "MOV B, M"}, // 0x46
  {5, "MOV B, A"}, // 0x47
  {5, "MOV C, B"}, // 0x48
  {5, "MOV C, C"}, // 0x49
  {5, "MOV C, D"}, // 0x4a
  {5, "MOV C, E"}, // 0x4b
  {5, "MOV C, H"}, // 0x4c
  {5, "MOV C, L"}, // 0x4d
  {7, "MOV C, M"}, // 0x4e
  {5, "MOV C, A"}, // 0x4f
  {5, "MOV D, B"}, // 0x50
  {5, "MOV D, C"}, // 0x51
  {5, "MOV D, D"}, // 0x52
  {5, "MOV D, E"}, // 0x53
  {5, "MOV D, H"}, // 0x54
  {5, "MOV D, L"}, // 0x55
  {7, "MOV D, M"}, // 0x56
  {5, "MOV D, A"}, // 0x57
  {5, "MOV E, B"}, // 0x58
  {5, "MOV E, C"}, // 0x59
  {5, "MOV E, D"}, // 0x5a
  {5, "MOV E, E"}, // 0x5b
  {5, "MOV E, H"}, // 0x5c
  {5, "MOV E, L"}, // 0x5d
  {7, "MOV E, M"}, // 0x5e
  {5, "MOV E, A"}, // 0x5f
  {5, "MOV H, B"}, // 0x60
  {5, "MOV H, C"}, // 0x61
  {5, "MOV H, D"}, // 0x62
  {5, "MOV H, E"}, // 0x63
  {5, "MOV H, H"}, // 0x64
  {5, "MOV H, L"}, // 0x65
  {7, "MOV H, M"}, // 0x66
  {5, "MOV H, A"}, // 0x67
  {5, "MOV L, B"}, // 0x68
  {5, "MOV L, C"}, // 0x69
  {5, "MOV L, D"}, // 0x6a
  {5, "MOV L, E"}, // 0x6b
  {5, "MOV L, H"}, // 0x6c
  {5, "MOV L, L"}, // 0x6d
  {7, "MOV L, M"}, // 0x6e
  {5, "MOV L, A"}, // 0x6f
  {7, "MOV M, B"}, // 0x70
  {7, "MOV M, C"}, // 0x71
  {7, "MOV M, D"}, // 0x72
  {7, "MOV M, E"}, // 0x73 
  {7, "MOV M, H"}, // 0x74
  {7, "MOV M, L"}, // 0x75
  {7, "HALT"}, // 0x76
  {7, "MOV M, A"}, // 0x77
  {5, "MOV A, B"}, // 0x78
  {5, "MOV A, C"}, // 0x79
  {5, "MOV A, D"}, // 0x7a
  {5, "MOV A, E"}, // 0x7b
  {5, "MOV A, H"}, // 0x7c
  {5, "MOV A, L"}, // 0x7d
  {7, "MOV A, M"}, // 0x7e
  {5, "MOV A, A"}, // 0x7f
  {4, "ADD B"}, // 0x80
  {4, "ADD C"}, // 0x81
  {4, "ADD D"}, // 0x82
  {4, "ADD E"}, // 0x83
  {4, "ADD H"}, // 0x84
  {4, "ADD L"}, // 0x85
  {7, "ADD M"}, // 0x86
  {4, "ADD A"}, // 0x87
  {4, "ADC B"}, // 0x88
  {4, "ADC C"}, // 0x89
  {4, "ADC D"}, // 0x8a
  {4, "ADC E"}, // 0x8b
  {4, "ADC H"}, // 0x8c
  {4, "ADC L"}, // 0x8d
  {7, "ADC M"}, // 0x8e
  {4, "ADC A"}, // 0x8f
  {4, "SUB B"}, // 0x90
  {4, "SUB C"}, // 0x91
  {4, "SUB D"}, // 0x92
  {4, "SUB E"}, // 0x93
  {4, "SUB H"}, // 0x94
  {4, "SUB L"}, // 0x95
  {7, "SUB M"}, // 0x96
  {4, "SUB A"}, // 0x97
  {4, "SBB B"}, // 0x98
  {4, "SBB C"}, // 0x99
  {4, "SBB D"}, // 0x9a
  {4, "SBB E"}, // 0x9b 
  {4, "SBB H"}, // 0x9c
  {4, "SBB L"}, // 0x9d
  {7, "SBB M"}, // 0x9e
  {4, "SBB A"}, // 0x9f
  {4, "ANA B"}, // 0xa0
  {4, "ANA C"}, // 0xa1
  {4, "ANA D"}, // 0xa2
  {4, "ANA E"}, // 0xa3
  {4, "ANA H"}, // 0xa4
  {4, "ANA L"}, // 0xa5
  {7, "ANA M"}, // 0xa6
  {4, "ANA A"}, // 0xa7
  {4, "XRA B"}, // 0xa8
  {4, "XRA C"}, // 0xa9
  {4, "XRA D"}, // 0xaa
  {4, "XRA E"}, // 0xab
  {4, "XRA H"}, // 0xac
  {4, "XRA L"}, // 0xad
  {7, "XRA M"}, // 0xae
  {4, "XRA A"}, // 0xaf
  {4, "ORA B"}, // 0xb0
  {4, "ORA C"}, // 0xb1
  {4, "ORA D"}, // 0xb2
  {4, "ORA E"}, // 0xb3
  {4, "ORA H"}, // 0xb4
  {4, "ORA L"}, // 0xb5
  {7, "ORA M"}, // 0xb6
  {4, "ORA A"}, // 0xb7
  {4, "CMP B"}, // 0xb8
  {4, "CMP C"}, // 0xb9
  {4, "CMP D"}, // 0xba
  {4, "CMP E"}, // 0xbb
  {4, "CMP H"}, // 0xbc
  {4, "CMP L"}, // 0xbd
  {4, "CMP M"}, // 0xbe
  {4, "CMP A"}, // 0xbf
  {5, "RNZ"}, // 0xc0
  {10, "POP B"}, // 0xc1
  {10, "JNZ, $"}, // 0xc2
  {10, "JMP, $"}, // 0xc3
  {11, "CNZ, $"}, // 0xc4
  {11, "PUSH B"}, // 0xc5
  {7, "ADI #"}, // 0xc6
  {11, "RST 0"}, // 0xc7
  {5, "RZ"}, // 0xc8
  {10, "RET"}, // 0xc9
  {10, "JZ, $"}, // 0xca
  {10, "JMP, $"}, // 0xcb
  {11, "CZ, $"}, // 0xcc
  {17, "CALL $"}, // 0xcd
  {7, "ACI #"}, // 0xce
  {11, "RST 1"}, // 0xcf
  {5, "RNC"}, // 0xd0
  {10, "POP D"}, // 0xd1
  {10, "JNC, $"}, // 0xd2
  {10, "OUT, #"}, // 0xd3
  {11, "CNC, $"}, // 0xd4
  {11, "PUSH D"}, // 0xd5
  {7, "SUI, #"}, // 0xd6
  {11, "RST 2"}, // 0xd7
  {5, "RC"}, // 0xd8
  {10, "RET"}, // 0xd9
  {10, "JC, $"}, // 0xda
  {10, "IN, #"}, // 0xdb
  {11, "CC, $"}, // 0xdc
  {17, "CALL, $"}, // 0xdd
  {7, "SBI, #"}, // 0xde
  {11, "RST 3"}, // 0xdf
  {5 ,"RPO"}, // 0xe0
  {10, "POP H"}, // 0xe1
  {10, "JPO $"}, // 0xe2
  {18, "XTHL"}, // 0xe3
  {11, "CPO, $"}, // 0xe4
  {11, "PUSH H"}, // 0xe5
  {7, "ANI, #"}, // 0xe6
  {11, "RST 4"}, // 0xe7
  {11, "RPE"}, // 0xe8
  {5, "PCHL"}, // 0xe9
  {10, "JPE, $"}, // 0xea
  {4, "XCHG"}, // 0xeb
  {11, "CPE, $"}, // 0xec
  {17, "CALL, $"}, // 0xed
  {7, "XRI, #"}, // 0xee
  {11, "RST 5"}, // 0xef
  {5, "RP"}, // 0xf0
  {10, "POP PSW"}, // 0xf1
  {10, "JP, $"}, // 0xf2
  {4, "DI"}, // 0xf3
  {11, "CP $"}, // 0xf4
  {11,"PUSH PSW"}, // 0xf5
  {7, "ORI, #"}, // 0xf6
  {11, "RST 6"}, // 0xf7
  {5, "RM"}, // 0xf8
  {5, "SPHL "}, // 0xf9
  {10, "JM, $"}, // 0xfa 
  {4, "EI"}, // 0xfb
  {11 ,"CM, $"}, // 0xfc
  {17, "CALL, $"}, // 0xfd
  {7, "CPI, #"}, // 0xfe
  {11, "RST 7"} // 0xff
};

static inline bool parity(uint8_t value)
{
	uint8_t result = 0;

	for(uint8_t i = 0; i < 8; i++)
	{
		result += ((value >> i) & 1);
	}

	return ((result & 1) == 0);
}


/* HOW TO IMPLEMENT CARRT FLAG WITH XOR:
*  https://stackoverflow.som/questions/39728980/how-does-xoring-the-a-register-clear-the-carry-bit-on-the-f-register-in-the-z80 
*/

static inline bool set_carry(uint8_t value1, uint8_t value2, uint8_t shift_no, bool cy)
{
  uint16_t result = value1 + value2 + cy;
  uint16_t carry = result ^ value1 ^ value2;
  return (carry >> shift_no) & 1;
}

static inline void set_pair(i8080* const s, uint8_t pair, uint16_t value)
{
  uint8_t high = (value >> 8) & 0xFF;
  uint8_t low = value & 0xFF;
  switch(pair)
  {
    case 0:
      s->b = high;
      s->c = low;
      break;
    case 1:
      s->d = high;
      s->e = low;
      break;
    case 2:
      s->h = high;
      s->l = low;
      break;
    case 3:
      s->sp = (high << 8) | (low & 0xFF);
      break;
    default:
      printf("\nCouldn't set pair.\n");
      break;
  }
}

static inline uint16_t get_pair(i8080* const s, uint8_t pair)
{
  switch(pair)
  {
    case 0:
      return PAIR(s->b, s->c);
      break;
    case 1:
      return PAIR(s->d, s->e);
      break;
    case 2:
      return PAIR(s->h, s->l);
      break;
    case 3: 
      return s->sp;
      break;
    default:
      printf("\nCouldn't get pair.\n");
      break;
  }

  return 0;
} 

static inline int8_t get_reg(i8080* const s, uint8_t reg)
{
  switch (reg)
  {
    case 0:
      return s->b;
      break;
    case 1: 
      return s->c;
      break;
    case 2:
      return s->d;
      break;
    case 3: 
      return s->e;
      break;
    case 4:
      return s->h;
      break;
    case 5:
      return s->l;
      break;
    case 6:
      return readByte(s, PAIR(s->h, s->l));
      break;
    case 7:
      return s->a;
      break;
    default:
      printf("\nCouldn't get register\n");
      break;
  }

  return 0;
}

static inline void set_reg(i8080* const s, uint8_t reg, uint8_t value)
{
  switch(reg)
  {
    case 0:
      s->b = value;
      break;
    case 1: 
      s->c = value;
      break;
    case 2:
      s->d = value;
      break;
    case 3:
      s->e = value;
      break;
    case 4:
      s->h = value;
      break;
    case 5:
      s->l = value;
      break;
    case 6:
      writeByte(s, PAIR(s->h, s->l), value);
      break;
    case 7:
      s->a = value;
      break;
    default:
      printf("\nCouldn't set register.\n");
      break;
  }
}

static inline void sub(i8080* const s, uint8_t* const reg_a, uint8_t value, bool cy)
{
  uint8_t result = *reg_a + ~(value) + !(cy);
  s->cf = set_carry(*reg_a, ~value, 8, !cy);
  s->hf = set_carry(*reg_a, ~value, 4, !cy);
  SET_SZP(s, result);
  *reg_a = result;
  s->cf = !s->cf;
}

static inline void add(i8080* const s, uint8_t* const reg_a, uint8_t value, bool cy)
{
  uint8_t result = *reg_a + value + cy;
  s->cf = set_carry(*reg_a, value, 8, cy);
  s->hf = set_carry(*reg_a, value, 4, cy);
  SET_SZP(s, result);
  *reg_a = result;
}

/* HOW TO IMPLEMENT HALF-CARRY:
 https://retrocomputing.stackexchange.com/questions/14977/auxiliary-carry-and-the-intel-8080s-logical-instructions */

static inline void ana(i8080* const s, uint8_t* const reg_a, uint8_t value)
{
  uint8_t result = *reg_a & value;
  s->cf = 0;
  s->hf = ((*reg_a | value) & 0x08) != 0;
  SET_SZP(s, result);
  *reg_a = result;
}

static inline void xra(i8080* const s, uint8_t* const reg_a, uint8_t value)
{
  uint8_t result = *reg_a ^ value;
  s->cf = 0;
  s->hf = 0;
  SET_SZP(s, result);
  *reg_a = result;
}

static inline void ora(i8080* const s, uint8_t* const reg_a, uint8_t value)
{
  uint8_t result = *reg_a | value;
  s->cf = 0;
  s->hf = 0;
  SET_SZP(s, result);
  *reg_a = result;
}

static inline void cmp(i8080* const s, uint8_t* const reg_a, uint8_t value)
{
  uint16_t result = *reg_a - value;
  s->cf = (result >> 8) & 1;
  s->hf = ~(result ^ *reg_a ^ value) & 0x10;
  SET_SZP(s, result);
}

static inline void inx(i8080* const s, uint8_t opcode)
{
  uint8_t reg = (opcode & 0x30) >> 4;
  set_pair(s, reg, get_pair(s, reg) + 1);
}

static inline void dcx(i8080* const s, uint8_t opcode)
{
  uint8_t reg = (opcode & 0x30) >> 4;
  set_pair(s, reg, get_pair(s, reg) - 1);
}

static inline uint8_t inr(i8080* const s, uint8_t opcode)
{
  uint8_t reg_got = get_reg(s, (opcode & 0x38) >> 3) + 1;
  s->hf = (reg_got & 0xF) == 0x0;
  set_reg(s, opcode >> 3, reg_got);
  SET_SZP(s, reg_got);
  return reg_got;
}

static inline uint8_t dcr(i8080* const s, uint8_t opcode)
{
  uint8_t reg_got = get_reg(s, (opcode & 0x38) >> 3) - 1;
  s->hf = !((reg_got & 0xF) == 0xF);
  set_reg(s, opcode >> 3, reg_got);
  SET_SZP(s, reg_got);
  return reg_got;
}

/* ROTATES REGISTER A LEFT */

static inline void rlc(i8080* const s)
{
  s->cf = s->a >> 7;
  s->a = (s->a << 1) | s->cf;
}

/* ROTATES REGISTER A TO THE LEFT WITH A CARRY */

static inline void ral(i8080* const s)
{
  bool cy = s->cf;
  s->cf = s->a >> 7;
  s->a = (s->a << 1) | cy;
}

/* ROTATES REGISTER A RIGHT */

static inline void rrc(i8080* const s)
{
  s->cf = s->a & 1; 
  s->a = (s->cf << 7) | (s->a >> 1);
}

/* ROTATES REGISTER A TO THE LEFT WITH A CARRY */

static inline void rar(i8080* const s) 
{
  bool cy = s->cf;
  s->cf = s->a & 1; 
  s->a = (s->a >> 1) | (cy << 7);
}

static inline void lxi(i8080* const s, uint8_t opcode)
{
  set_pair(s, (opcode & 0x30) >> 4, nextWord(s));
}

static inline void mov_reg(i8080* const s, uint8_t opcode)
{
  uint8_t left = (opcode & 0x38) >> 3;
  uint8_t right = opcode & 0x7;
  set_reg(s, left, get_reg(s, right));
}

static inline void mvi_reg(i8080* const s, uint8_t opcode)
{
  set_reg(s, (opcode & 0x38) >> 3, nextByte(s));
}

static inline void stax(i8080* const s, uint8_t opcode)
{
  writeByte(s, get_pair(s, (opcode & 0x30) >> 4), s->a);
}

static inline void ldax(i8080* const s, uint8_t opcode)
{
  s->a = readByte(s, get_pair(s, (opcode & 0x30) >> 4));
}

static inline void dad(i8080* const s, uint8_t opcode)
{
  uint16_t pair_got = get_pair(s, (opcode & 0x30) >> 4);
  s->cf = ((PAIR(s->h, s->l) + pair_got) >> 16) & 1;
  uint16_t value = (PAIR(s->h, s->l) + pair_got);

  s->h = (value >> 8) & 0xFF;
  s->l = value & 0xFF;
}

static inline void daa(i8080* const s)
{
  bool cy = s->cf;
  uint8_t perform_add = 0;
  uint8_t higher_bits = s->a >> 4;
  uint8_t lower_bits = s->a & 0x0F;

  if(lower_bits > 9 || s->hf)
  {
    perform_add += 0x6;
  }
  if(higher_bits > 9 || ((higher_bits >= 9 && lower_bits > 9)) || s->cf)
  {
    perform_add += 0x60; /* 0x60 = 6 * 2^4 */
    cy = 1;
  }

  add(s, &s->a, perform_add, 0);
  s->cf = cy;
}

static inline void cma(i8080* const s)
{
  s->a = ~s->a;
}

static inline void cmc(i8080* const s)
{
  s->cf = !s->cf;
}

static inline void stc(i8080* const s)
{
  s->cf = 1;
}

static inline void sta(i8080* const s)
{
  writeByte(s, nextWord(s), s->a);
}

static inline void shld(i8080* const s)
{
  writeWord(s, nextWord(s), PAIR(s->h, s->l));
}

static inline void lda(i8080* const s)
{
  s->a = readByte(s, nextWord(s));
}

static inline void lhld(i8080* const s, uint8_t opcode, uint16_t addr)
{
  set_pair(s, opcode & 0x7, readWord(s, addr));
}

static inline void push_stack(i8080* const s, uint16_t value)
{
  s->sp -= 2;
  writeWord(s, s->sp, value);
}

static inline uint16_t pop_stack(i8080* const s)
{
  uint16_t value_popped = readWord(s, s->sp);
  s->sp += 2;
  return value_popped;
}

static inline void jump(i8080* const s, uint16_t addr)
{
  s->pc = addr;
}

static inline void call(i8080* const s, uint16_t addr)
{
  s->sp -= 2;
  writeWord(s, s->sp, s->pc); /* PUSH PC TO STACK */
  jump(s, addr);
}

static inline void ret(i8080* const s)
{
  s->pc = pop_stack(s);
}

static inline void cond_jump(i8080* const s, bool condition)
{
  uint16_t addr = nextWord(s);
  if(condition)
  {
    jump(s, addr);
  }
}

static inline void cond_call(i8080* const s, bool condition)
{

  uint16_t addr = nextWord(s);
  if(condition)
  {
    call(s, addr);
  }
}

static inline void cond_ret(i8080* const s, bool condition)
{
  if(condition)
  {
    ret(s);
  }
}

static inline void xthl(i8080* const s, uint8_t opcode)
{
  uint16_t sp_value = readWord(s, s->sp);
  writeWord(s, s->sp, get_pair(s, (opcode & 0x30) >> 4));
  set_pair(s, (opcode & 0x30) >> 4, sp_value);
}

static inline void xchg(i8080* const s)
{
  uint16_t hl, de;
  de = PAIR(s->d, s->e);
  hl = PAIR(s->h, s->l);

  set_pair(s, 0x1, hl);
  set_pair(s, 0x2, de);
}

static inline void pop_psw(i8080* const s)
{
  uint16_t psw = pop_stack(s);
  s->a = psw >> 8;
  uint8_t f = psw & 0xFF;
  s->sf = (f >> 7) & 1;
  s->zf = (f >> 6) & 1;
  s->hf = (f >> 4) & 1;
  s->pf = (f >> 2) & 1;
  s->cf = (f >> 0) & 1;
}

static inline void push_psw(i8080* const s)
{
  uint8_t f = 0;
  f |= s->sf << 7;
  f |= s->zf << 6;
  f |= s->hf << 4;
  f |= s->pf << 2;
  f |= 1 << 1;
  f |= s->cf << 0;

  push_stack(s, s->a << 8 | f);
}

static inline void interrupt_rst(i8080* const s, uint8_t rst_number)
{
  s->sp -= 2;
  writeWord(s, s->sp, s->pc); /* PUSH PC TO STACK */


  s->pc = rst_number * 0x0008;

  /* WITHOUT inte_pending = 0 HERE THE INTERRUPTS WILL BE CALLED ON TOP OF EACH OTHER,
  MACHINE CODE CHECKS INTERRUPT STATE BEFORE GENERATION,
  WE CANNOT GET ANOTHER EI BEFORE THE INSTRUCTION EI IS CALLED

  "The interrupt enable bit, INTE, is reset = 0 (Intel 8080 Assembly Programming Manual - 59. page)"
  */

  s->inte_pending = 0;
}


uint8_t emu_in(i8080* const s, uint8_t port)
{
  uint16_t value = 0;
  uint8_t reg_a = 0;
  switch(port)
  {
    case 3:
      value = (s->shift_1 << 8) | s->shift_0;
      reg_a = ((value >> (8 - s->offset_shift)) & 0xFF);
      break;
  }
  return reg_a;
}

void emu_out(i8080* const s, uint8_t port)
{
  switch(port)
  {
    case 2:
      s->offset_shift = s->a & 0x7;
      break;

    case 4:
      s->shift_0 = s->shift_1;
      s->shift_1 = s->a;
      break;
  }
}


void init_state(i8080* const s)
{
  s->cyc = 0;

  s->a = 0x00;
  s->b = 0x00;
  s->c = 0x00;
  s->d = 0x00;
  s->e = 0x00;
  s->h = 0x00;
  s->l = 0x00;

  s->sf = 0x00;
  s->zf = 0x00;
  s->pf = 0x00;
  s->cf = 0x00;
  s->hf = 0x00;

  s->pc = 0x0000;
  s->sp = 0x0000;

  s->halt = 0;
  s->inte_happened = 0;
  s->inte_pending = 0;
  s->inte_vector = 0;
}

static inline void opcode_execution(i8080* const s, uint8_t opcode)
{
  s->cyc += instructions[opcode].cycle;
  switch(opcode)
  {
    case 0x00:
    case 0x08:
    case 0x10:
    case 0x18:
    case 0x20:
    case 0x28:
    case 0x30:
    case 0x38:
      break;

    case 0x01:
    case 0x11:
    case 0x21:
    case 0x31:
      lxi(s, opcode);
      break;

    case 0x02:
    case 0x12:
      stax(s, opcode);
      break;

    case 0x22:
      shld(s);
      break;
    case 0x32:
      sta(s);
      break;

    case 0x0A:
    case 0x1A:
      ldax(s, opcode);
      break;

    case 0x2A:
      lhld(s, opcode, nextWord(s));
      break;

    case 0x3A:
      lda(s);
      break;

    case 0x03:
    case 0x13:
    case 0x23:
    case 0x33:
      inx(s, opcode);
      break;

    case 0x0B:
    case 0x1B:
    case 0x2B:
    case 0x3B:
      dcx(s, opcode);
      break;

    case 0x04:
    case 0x14:
    case 0x24:
    case 0x34:
    case 0x0C:
    case 0x1C:
    case 0x2C:
    case 0x3C:
      inr(s, opcode);
      break;

    case 0x05:
    case 0x15:
    case 0x25:
    case 0x35:
    case 0x0D:
    case 0x1D:
    case 0x2D:
    case 0x3D:
      dcr(s, opcode);
      break;

    case 0x06:
    case 0x16:
    case 0x26:
    case 0x36:
    case 0x0E:
    case 0x1E:
    case 0x2E:
    case 0x3E:
      mvi_reg(s, opcode);
      break;

    case 0x07: rlc(s); break;
    case 0x17: ral(s); break;
    case 0x0F: rrc(s); break;
    case 0x1F: rar(s); break;

    case 0x27: daa(s); break;
    case 0x37: stc(s); break;
    case 0x2F: cma(s); break;
    case 0x3F: cmc(s); break;

    case 0x09:
    case 0x19:
    case 0x29:
    case 0x39:
      dad(s, opcode);
      break;

    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7B:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
      mov_reg(s, opcode);
      break;

    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
      add(s, &s->a, get_reg(s, opcode & 0x7), 0);
      break;

    case 0x88:
    case 0x89:
    case 0x8A:
    case 0x8B:
    case 0x8C:
    case 0x8D:
    case 0x8E:
    case 0x8F:
      add(s, &s->a, get_reg(s, opcode & 0x7), s->cf);
      break;

    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
      sub(s, &s->a, get_reg(s, opcode & 0x7), 0);
      break;

    case 0x98:
    case 0x99:
    case 0x9A:
    case 0x9B:
    case 0x9C:
    case 0x9D:
    case 0x9E:
    case 0x9F:
      sub(s, &s->a, get_reg(s, opcode & 0x7), s->cf);
      break;

    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
    case 0xA4:
    case 0xA5:
    case 0xA6:
    case 0xA7:
      ana(s, &s->a, get_reg(s, opcode & 0x7));
      break;

    case 0xA8:
    case 0xA9:
    case 0xAA:
    case 0xAB:
    case 0xAC:
    case 0xAD:
    case 0xAE:
    case 0xAF:
      xra(s, &s->a, get_reg(s, opcode & 0x7));
      break;

    case 0xB0:
    case 0xB1:
    case 0xB2:
    case 0xB3:
    case 0xB4:
    case 0xB5:
    case 0xB6:
    case 0xB7:
      ora(s, &s->a, get_reg(s, opcode & 0x7));
      break;

    case 0xB8:
    case 0xB9:
    case 0xBA:
    case 0xBB:
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xBF:
      cmp(s, &s->a, get_reg(s, opcode & 0x7));
      break;

    case 0xC0: cond_ret(s, s->zf == 0); break;
    case 0xD0: cond_ret(s, s->cf == 0); break;
    case 0xE0: cond_ret(s, s->pf == 0); break;
    case 0xF0: cond_ret(s, s->sf == 0); break;
    
    case 0xC1:
    case 0xD1:
    case 0xE1:
      set_pair(s, (opcode & 0x30) >> 4, pop_stack(s));
      break;
    
    case 0xC2: cond_jump(s, s->zf == 0); break;
    case 0xD2: cond_jump(s, s->cf == 0); break;
    case 0xE2: cond_jump(s, s->pf == 0); break;
    case 0xF2: cond_jump(s, s->sf == 0); break;

    case 0xC3:
    case 0xCB:
      jump(s, nextWord(s)); 
      break;

    case 0xD3: emu_out(s, nextByte(s)); break;
    case 0xDB: emu_in(s, nextByte(s)); break;

    case 0xC4: cond_call(s, s->zf == 0); break;
    case 0xD4: cond_call(s, s->cf == 0); break;
    case 0xE4: cond_call(s, s->pf == 0); break;
    case 0xF4: cond_call(s, s->sf == 0); break;

    case 0xC5:
    case 0xD5:
    case 0xE5:
      push_stack(s, get_pair(s, (opcode & 0x30) >> 4));
      break;

    case 0xF1: pop_psw(s); break;
    case 0xF5: push_psw(s); break;

    case 0xE3: xthl(s, opcode); break;
    case 0xEB: xchg(s); break;

    case 0xC6: add(s, &s->a, nextByte(s), 0); break;
    case 0xD6: sub(s, &s->a, nextByte(s), 0); break;
    case 0xE6: ana(s, &s->a, nextByte(s)); break;
    case 0xF6: ora(s, &s->a, nextByte(s)); break;

    case 0xCE: add(s, &s->a, nextByte(s), s->cf); break;
    case 0xDE: sub(s, &s->a, nextByte(s), s->cf); break;
    case 0xEE: xra(s, &s->a, nextByte(s)); break;
    case 0xFE: cmp(s, &s->a, nextByte(s)); break;

    case 0xC8: cond_ret(s, s->zf == 1); break;
    case 0xD8: cond_ret(s, s->cf == 1); break;
    case 0xE8: cond_ret(s, s->pf == 1); break;
    case 0xF8: cond_ret(s, s->sf == 1); break;

    case 0xC9:
    case 0xD9: 
      ret(s); 
      break;

    case 0xE9: s->pc = PAIR(s->h, s->l); break;
    case 0xF9: set_pair(s, (opcode & 0x30) >> 4, PAIR(s->h, s->l)); break;

    case 0xCA: cond_jump(s, s->zf == 1); break;
    case 0xDA: cond_jump(s, s->cf == 1); break;
    case 0xEA: cond_jump(s, s->pf == 1); break;
    case 0xFA: cond_jump(s, s->sf == 1); break;

    case 0xCC: cond_call(s, s->zf == 1); break;
    case 0xDC: cond_call(s, s->cf == 1); break;
    case 0xEC: cond_call(s, s->pf == 1); break;
    case 0xFC: cond_call(s, s->sf == 1); break;

    case 0xCD:
    case 0xDD:
    case 0xED:
    case 0xFD:
      call(s, nextWord(s));
      break;

    case 0x76: s->halt = 1; break;
    case 0xFB: s->inte_pending = 1; break;
    case 0xF3: s->inte_pending = 0; break;

    case 0xC7: interrupt_rst(s, 0x0000); break;
    case 0xCF: interrupt_rst(s, 0x0008); break;
    case 0xD7: interrupt_rst(s, 0x0010); break;
    case 0xDF: interrupt_rst(s, 0x0018); break;
    case 0xE7: interrupt_rst(s, 0x0020); break;
    case 0xEF: interrupt_rst(s, 0x0028); break;
    case 0xF7: interrupt_rst(s, 0x0030); break;
    case 0xFF: interrupt_rst(s, 0x0038); break;

    default:
      fprintf(stderr, "UNIMPLEMENTED INSTRUCTION AT: 0x%04x\n", s->pc);
      exit(1);
      break;
  }
}

void interrupt_handle(i8080* const s, uint8_t opcode)
{
  if(s->inte_pending == 1)
  {
    s->inte_happened = 1;
    s->inte_vector = opcode;
  }
}

void cpu_step(i8080* const s)
{
  if(s->inte_happened && s->inte_pending == 0)
  {
    s->halt = 0;
    s->inte_happened = 0;
    s->inte_pending = 0;
    opcode_execution(s, s->inte_vector);
  }
  if(!s->halt)
  {
    opcode_execution(s, nextByte(s));
  }
}

void debug_output(i8080* const s, bool print)
{
  uint8_t f = 0;

  f |= s->sf << 7;
  f |= s->zf << 6;
  f |= s->hf << 4;
  f |= s->pf << 2;
  f |= 1 << 1;
  f |= s->cf << 0;
  printf("\nAF = %04X BC = %04X DE = %04X HL = %04X PC = %04X SP = %04X CYC = %lu ", 
         s->a << 8 | f, PAIR(s->b, s->c), PAIR(s->d, s->e), PAIR(s->h, s->l), s->pc, s->sp, s->cyc);
  
  printf(" (%02X %02X %02X %02X)", 
	 readByte(s, s->pc), readByte(s, s->pc + 1), readByte(s, s->pc + 2), readByte(s, s->pc + 3));

  printf("\nF = %d SF = %d ZF = %d HF = %d PF = %d CF = %d", 
         f, s->sf, s->zf, s->hf, s->pf, s->cf);

  if(print == true)
  {
    printf("\n - %s", instructions[readByte(s, s->pc)].disassemble);
  }
  printf("\n");
}
