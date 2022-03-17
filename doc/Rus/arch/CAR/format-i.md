# Format-i - Immediate

**Format-i это формат в котором отведено `7 бит` под команду `5 бит` под регистр и `16 битов` под непосредственное значение.**

## Opcode structure

| Mode  | Format | OP     | RegDst | Immediate |
|-------|--------|--------|--------|-----------|
| 1 bit | 3 bit  | 7 bit  | 5 bit  | 16 bit    |

### Opcodes

| Category  | Mnemonic  | OP     | Operand1 | Operand2  | Operand3  | Operand4  | Description                                       |
|-----------|-----------|--------|----------|-----------|-----------|-----------|---------------------------------------------------|
| Basic     | MOV       | `0x00` | RegDst   | Immediate | None      | None      | RegDst = Imm16                                    |
|           | PUSH      | `0x01` | RegDst   | None      | None      | None      | RegDst = Imm16                                    |

