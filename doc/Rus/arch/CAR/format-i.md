# Format-i - Immediate

**Format-i это формат в котором отведено `7 бит` под команду `5 бит` под регистр и `16 битов` под непосредственное значение.**

## Opcode structure

| Mode  | Format | Opcode | RegDst | Immediate |
|-------|--------|--------|--------|-----------|
| 1 bit | 3 bit  | 7 bit  | 5 bit  | 16 bit    |

### Opcodes

##### Basic

| Mnemonic | Opcode | Op1    | Op2   | Description                 |
|----------|--------|--------|-------|-----------------------------|
| MOV      | `0x00` | RegDst | IMM16 | RegDst = IMM16              |
| PUSH     | `0x01` | Reg    | None  | SP -= 8, STACK[SP] = Reg    |
| POP      | `0x02` | RegDst | None  | RegDst = STACK[SP], SP += 8 |
| SWP      | `0x03` | RegDst | None  | Byte Swap                   |