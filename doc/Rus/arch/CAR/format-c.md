# Format-c - Call

| Mode  | Format | OP     | Immediate |
|-------|--------|--------|-----------|
| 1 bit | 3 bit  | 4 bit  | 24 bit    |

### Opcodes

| Category           | Mnemonic | Opcode | OPERAND1 | OPERAND2 | Description                                                    |
|--------------------|----------|--------|----------|----------|----------------------------------------------------------------|
| Flow               | CALL     | 0x50   |          | IMM24    | IP += IMM24 (Signed)                                           |
|                    | CEQ      | 0x51   |          | IMM24    | If flag  EQ then CALL                                          |
|                    | CNE      | 0x52   |          | IMM24    | If flag !EQ then CALL                                          |
| Flow (Signed)      | CLT      | 0x53   |          | IMM24    | If flag  LT then CALL                                          |
|                    | CGT      | 0x54   |          | IMM24    | If flag !LT and !EQ then CALL                                  |
|                    | CLE      | 0x55   |          | IMM24    | If flag  LT and  EQ then CALL                                  |
|                    | CGE      | 0x56   |          | IMM24    | If flag  LT then CALL                                          |
| Flow (Unsigned)    | CLS      | 0x57   |          | IMM24    | If flag  LO and  EQ then CALL                                  |
|                    | CHS      | 0x58   |          | IMM24    | If flag !LO then CALL                                          |
|                    | CLO      | 0x59   |          | IMM24    | If flag  LO then CALL                                          |
|                    | CHI      | 0x5A   |          | IMM24    | If flag !LO and !EQ then CALL                                  |
|                    | RET      | 0x60   |          | IMM24    | IP = POP(Reg)                                                  |
