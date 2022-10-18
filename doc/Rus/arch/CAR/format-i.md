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
| Special            | ENTER    | 0x0C   |          | IMM16    | Создание кадра стека и резервирование места на нем!            |
|                    | LEAVE    | 0x0D   |          | IMM16    | Выходит из кадра стека!                                        |
|                    | INV      | 0x0F   |          | IMM16    | Вызывает аппаратную процедуру!                                 |
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
|                    | ROL      | 0x24   | RegDst   | IMM16    | RegDst >>>>= IMM16                                             |
|                    | ROR      | 0x25   | RegDst   | IMM16    | RegDst <<<<= IMM16                                             |
| Logic              | AND      | 0x30   | RegDst   | IMM16    | RegDst &= IMM16                                                |
|                    | NAND     | 0x31   | RegDst   | IMM16    | RegDst &= !IMM16                                               |
|                    | OR       | 0x32   | RegDst   | IMM16    | RegDst &#124;= IMM16                                           |                                                       |= IMM16                                               |
|                    | NOR      | 0x33   | RegDst   | IMM16    | RegDst &#124;= !IMM16                                          |    
|                    | XOR      | 0x34   | RegDst   | IMM16    | RegDst ^= IMM16                                                |    
|                    | NOT      | 0x35   | RegDst   | IMM16    | RegDst = !IMM16                                                |    
|                    | NEG      | 0x36   | RegDst   | IMM16    | RegDst = -IMM16                                                |    

##### Basic

