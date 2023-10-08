# Format-j - Jump

| Mode  | Format | OP     | Immediate |
|-------|--------|--------|-----------|
| 1 bit | 3 bit  | 4 bit  | 24 bit    |

### Opcodes

| Category          | Mnemonic | Opcode | OPERAND1 | OPERAND2 | Description                                                     |
|-------------------|----------|--------|----------|----------|-----------------------------------------------------------------|
| Flow              | JMP      | 0x00   |          | IMM24    | IP += IMM24 (Signed)                                            |
|                   | JEQ      | 0x01   |          | IMM24    | If flag  EQ then JMP                                            |
|                   | JNE      | 0x02   |          | IMM24    | If flag !EQ then JMP                                            |
| Flow (Signed)     | JLT      | 0x03   |          | IMM24    | If flag  LT then JMP                                            |
|                   | JGT      | 0x04   |          | IMM24    | If flag !LT and !EQ then JMP                                    |
|                   | JLE      | 0x05   |          | IMM24    | If flag  LT and  EQ then JMP                                    |
|                   | JGE      | 0x06   |          | IMM24    | If flag  LT then JMP                                            |
| Flow (Unsigned)   | JLS      | 0x07   |          | IMM24    | If flag  LO and  EQ then JMP                                    |
|                   | JHS      | 0x08   |          | IMM24    | If flag !LO then JMP                                            |
|                   | JLO      | 0x09   |          | IMM24    | If flag  LO then JMP                                            |
|                   | JHI      | 0x0A   |          | IMM24    | If flag !LO and !EQ then JMP                                    |
