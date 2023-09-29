# Format-i - Immediate

**Format-i это формат в котором отведено `7 бит` под команду `5 бит` под регистр и `16 битов` под непосредственное значение.**

## Opcode structure

| Mode  | Format | Opcode | RegDst | Immediate |
|-------|--------|--------|--------|-----------|
| 1 bit | 3 bit  | 7 bit  | 5 bit  | 16 bit    |

### Opcodes

| Category           | Mnemonic | Opcode | OPERAND1 | OPERAND2 | Description                                                    |
|--------------------|----------|--------|----------|----------|----------------------------------------------------------------|
| Basic              | MOV      | 0x00   | RegDst   | IMM16    | RegDst = IMM16                                                 |
|                    | PUSH     | 0x01   | Reg      |          | STACK[SP] = Reg                                                |
|                    | POP      | 0x02   | Reg      |          | Reg = STACK[SP]                                                |
|                    | SWP      | 0x03   | Reg      |          | !                                                              |
|                    | LD       | 0x04   | Reg      | IMM16    | RegDst = [IMM16]!                                              |
|                    | ST       | 0x05   | Reg      | IMM16    | RegDst = [IMM16]!                                              |
|                    | BK       | 0x09   |          |          | Вызывает прерывание точки останова                             |
| Interrupts         | HWI      | 0x0A   |          | IMM8     | Аппаратное прерывание. Передает аппаратное прерывание в DVM    |
|                    | SWI      | 0x0B   |          | IMM8     | Программное прерывание. Передает программное прерывание из DVM |
| Special            | ENTER    | 0x0C   |          | IMM16    | Создание кадра стека и резервирование места на нем             |
|                    | LEAVE    | 0x0D   |          | IMM16    | Выходит из кадра стека                                         |
|                    | INV      | 0x0F   |          | IMM16    | Вызывает аппаратную процедуру                                  |
| Integer arithmetic | ADD      | 0x10   | RegDst   | IMM16    | RegDst += IMM16                                                |
|                    | SUB      | 0x11   | RegDst   | IMM16    | RegDst -= IMM16                                                |
|                    | INC      | 0x14   | RegDst   |          | RegDst++                                                       |
|                    | DEC      | 0x15   | RegDst   |          | RegDst--                                                       |
|                    | MUL      | 0x16   | RegDst   | IMM16    | RegDst *= IMM16                                                |
|                    | DIV      | 0x17   | RegDst   | IMM16    | RegDst /= IMM16                                                |
|                    | IMUL     | 0x18   | RegDst   | IMM16    | RegDst *= IMM16 (Signed)                                       |
|                    | IDIV     | 0x19   | RegDst   | IMM16    | RegDst /= IMM16 (Signed)                                       |
|                    | MOD      | 0x18   | RegDst   | IMM16    | RegDst %= IMM16                                                |
|                    | SHL      | 0x20   | RegDst   | IMM16    | RegDst <<= IMM16                                               |
|                    | SHR      | 0x21   | RegDst   | IMM16    | RegDst >>= IMM16                                               |
|                    | ASHL     | 0x22   | RegDst   | IMM16    | RegDst <<<= IMM16                                              |
|                    | ASHR     | 0x23   | RegDst   | IMM16    | RegDst >>>= IMM16                                              |
|                    | ROL      | 0x24   | RegDst   | IMM16    | RegDst >>>>= IMM16                                             |
|                    | ROR      | 0x25   | RegDst   | IMM16    | RegDst <<<<= IMM16                                             |
| Logic              | AND      | 0x30   | RegDst   | IMM16    | RegDst &= IMM16                                                |
|                    | NAND     | 0x31   | RegDst   | IMM16    | RegDst &= !IMM16                                               |
|                    | OR       | 0x32   | RegDst   | IMM16    | RegDst &#124;= IMM16                                           |
|                    | NOR      | 0x33   | RegDst   | IMM16    | RegDst &#124;= !IMM16                                          |
|                    | XOR      | 0x34   | RegDst   | IMM16    | RegDst ^= IMM16                                                |
|                    | NOT      | 0x35   | RegDst   | IMM16    | RegDst = !IMM16                                                |
|                    | NEG      | 0x36   | RegDst   | IMM16    | RegDst = -IMM16                                                |
| Compare            | CMP      | 0x3A   | RegDst   | IMM16    | FR &#124;= (RegDst < IMM16) &#124 (RegDst == IMM16)            |
|                    | ICMP     | 0x3B   | RegDst   | IMM16    | FR &#124;= (RegDst < IMM16) &#124 (RegDst == IMM16) (Signed)   |
| Flow               | JMP      | 0x40   |          | IMM16    | IP += IMM16 (Signed)                                           |
|                    | JEQ      | 0x41   |          | IMM16    | If flag  EQ then JMP                                           |
|                    | JNE      | 0x42   |          | IMM16    | If flag !EQ then JMP                                           |
| Flow (Signed)      | JLT      | 0x43   |          | IMM16    | If flag  LT then JMP                                           |
|                    | JGT      | 0x44   |          | IMM16    | If flag !LT and !EQ then JMP                                   |
|                    | JLE      | 0x45   |          | IMM16    | If flag  LT and  EQ then JMP                                   |
|                    | JGE      | 0x46   |          | IMM16    | If flag  LT then JMP                                           |
| Flow (Unsigned)    | JLS      | 0x47   |          | IMM16    | If flag  LO and  EQ then JMP                                   |
|                    | JHS      | 0x48   |          | IMM16    | If flag !LO then JMP                                           |
|                    | JLO      | 0x49   |          | IMM16    | If flag  LO then JMP                                           |
|                    | JHI      | 0x4A   |          | IMM16    | If flag !LO and !EQ then JMP                                   |
| Flow               | CALL     | 0x50   |          | IMM16    | IP += IMM16 (Signed)                                           |
|                    | CEQ      | 0x51   |          | IMM16    | If flag  EQ then CALL                                          |
|                    | CNE      | 0x52   |          | IMM16    | If flag !EQ then CALL                                          |
| Flow (Signed)      | CLT      | 0x53   |          | IMM16    | If flag  LT then CALL                                          |
|                    | CGT      | 0x54   |          | IMM16    | If flag !LT and !EQ then CALL                                  |
|                    | CLE      | 0x55   |          | IMM16    | If flag  LT and  EQ then CALL                                  |
|                    | CGE      | 0x56   |          | IMM16    | If flag  LT then CALL                                          |
| Flow (Unsigned)    | CLS      | 0x57   |          | IMM16    | If flag  LO and  EQ then CALL                                  |
|                    | CHS      | 0x58   |          | IMM16    | If flag !LO then CALL                                          |
|                    | CLO      | 0x59   |          | IMM16    | If flag  LO then CALL                                          |
|                    | CHI      | 0x5A   |          | IMM16    | If flag !LO and !EQ then CALL                                  |
|                    | RET      | 0x60   |          | IMM16    | IP = POP(Reg)                                                  |
