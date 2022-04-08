
`z` - Zero flag

`o` - Overflow flag

`c` - Carry flag

| Opcode | Funct3 | RegDst | Immediate |
|--------|--------|--------|-----------|
| 8bit   | 3bit   | 5bit   | 16bit     |

| Mnemonic | Opcode | Op1    | Op2          | Description              |
|----------|--------|--------|--------------|--------------------------|
| MOV      | `0x00` | RegDst | IMM16/RegSrc | Op1 = Op2                |
| PUSH     | `0x01` | Reg    | None         | SP -= 8, STACK[SP] = Op1 |
| POP      | `0x02` | RegDst | None         | Op1 = STACK[SP], SP += 8 |
| SWP      | `0x03` | RegDst | None         | Byte Swap                |