# Format-j - Jump

| Mode  | Format | OP     | Immediate |
|-------|--------|--------|-----------|
| 1 bit | 3 bit  | 4 bit  | 24 bit    |

### Opcodes

| Category          | Mnemonic | Opcode | OPERAND1 | OPERAND2 | Description                                                     |
|-------------------|----------|--------|----------|----------|-----------------------------------------------------------------|
| Flow              | JMP      | 0x40   |          | IMM24    | IP += IMM24 (Signed)                                            |
|                   | JEQ      | 0x41   |          | IMM24    | If flag  EQ then JMP                                            |
|                   | JNE      | 0x42   |          | IMM24    | If flag !EQ then JMP                                            |
| Flow (Signed)     | JLT      | 0x43   |          | IMM24    | If flag  LT then JMP                                            |
|                   | JGT      | 0x44   |          | IMM24    | If flag !LT and !EQ then JMP                                    |
|                   | JLE      | 0x45   |          | IMM24    | If flag  LT and  EQ then JMP                                    |
|                   | JGE      | 0x46   |          | IMM24    | If flag  LT then JMP                                            |
| Flow (Unsigned)   | JLS      | 0x47   |          | IMM24    | If flag  LO and  EQ then JMP                                    |
|                   | JHS      | 0x48   |          | IMM24    | If flag !LO then JMP                                            |
|                   | JLO      | 0x49   |          | IMM24    | If flag  LO then JMP                                            |
|                   | JHI      | 0x4A   |          | IMM24    | If flag !LO and !EQ then JMP                                    |
