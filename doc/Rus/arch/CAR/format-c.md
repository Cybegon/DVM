# Format-c - Call

| Mode  | Format | OP    | Immediate |
|-------|--------|-------|-----------|
| 2 bit | 6 bit  | 8 bit | 48 bit    |

### Opcodes

| Category           | Mnemonic | Opcode | OPERAND1 | OPERAND2 | Description                                                    |
|--------------------|----------|--------|----------|----------|----------------------------------------------------------------|
| Flow               | CALL     | 0x00   |          | IMM24    | IP += IMM24 (Signed)                                           |
|                    | CEQ      | 0x01   |          | IMM24    | If flag  EQ then CALL                                          |
|                    | CNE      | 0x02   |          | IMM24    | If flag !EQ then CALL                                          |
| Flow (Signed)      | CLT      | 0x03   |          | IMM24    | If flag  LT then CALL                                          |
|                    | CGT      | 0x04   |          | IMM24    | If flag !LT and !EQ then CALL                                  |
|                    | CLE      | 0x05   |          | IMM24    | If flag  LT and  EQ then CALL                                  |
|                    | CGE      | 0x06   |          | IMM24    | If flag  LT then CALL                                          |
| Flow (Unsigned)    | CLS      | 0x07   |          | IMM24    | If flag  LO and  EQ then CALL                                  |
|                    | CHS      | 0x08   |          | IMM24    | If flag !LO then CALL                                          |
|                    | CLO      | 0x09   |          | IMM24    | If flag  LO then CALL                                          |
|                    | CHI      | 0x0A   |          | IMM24    | If flag !LO and !EQ then CALL                                  |
|                    | RET      | 0x0B   |          | IMM24    | IP = POP(Reg)                                                  |
