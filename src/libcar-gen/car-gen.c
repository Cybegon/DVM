#include "car-gen.h"

#include "dvmdef.h"

#include "formats.h"

#define BIT_GET( var, pos ) \
        ( ((var) >> (pos))  & 0x01u )

#define BIT_SET( var, pos ) \
        ( (var) |= (1u << (pos) ) )

#define BIT_CLEAR( var, pos ) \
        ( (var) &= ~(1u << (pos) ) )

duint64 car_op32Pack64(duint32 opFirst, duint32 opSecond)
{
    return ( (duint64)opFirst << 32u ) | ( (duint64)opSecond );
}

duint64 bitCount(duint64 list)
{
    duint count = 0;

    for (int i = 0; i < sizeof(duint64) * 8; ++i)
        if ( BIT_GET(list, i) )
            ++count;
    return count;
}

duint getNextEnabledBit(duint64 list)
{
    for (int i = sizeof(duint64) * 8; i > 0; --i)
        if ( BIT_GET(list, i) )
            return i;
    return NO_REG;
}

void writeFormat32(duint64* byteCode, duint8 format)
{
    *byteCode |= ( ((duint32)format) << 28 );
}

void writeOperation32(duint64* byteCode, duint8 op)
{
    *byteCode |= ( ((duint32)op) << 21 );
}

void writeReg32(duint64* byteCode, duint8 reg, duint8 offset)
{
    *byteCode |= ( nR(reg) << offset );
}

void writeImm32(duint64* byteCode, duint32 imm)
{
    *byteCode |= imm;
}

duint64 car_emitOp32(duint8 format, duint8 opcode,
                      duint8 regDst, duint8 regSrc1,
                      duint8 regSrc2, duint8 regSrc3,
                      duint32 imm)
{
    duint64 byteCode = 0;
    writeFormat32(&byteCode, format);

    switch (format) {
        case CAR_FORMAT_I: {
            writeOperation32(&byteCode, opcode & 0x7F);
            writeReg32(&byteCode, regDst, 16);
            writeImm32(&byteCode, imm);
            break;
        }
        case CAR_FORMAT_R: {
            writeOperation32(&byteCode, opcode & 0x7F);
            writeReg32(&byteCode, regDst, 16);
            writeReg32(&byteCode, regSrc1, 11);
            writeReg32(&byteCode, regSrc2, 6);
            if (regSrc3 != NO_REG) {
                writeReg32(&byteCode, regSrc3, 1);
                byteCode |= 1;
            }
            break;
        }
        case CAR_FORMAT_J:
        case CAR_FORMAT_C: {
            writeOperation32(&byteCode, opcode & 0x0F);
            writeImm32(&byteCode, imm & 0x00FFFFFF);
            break;
        }
        default: {
            break;
        }
    }

    return ( (byteCode) << 32 );
}

void writeFormat64(duint64* byteCode, duint8 format)
{
    *byteCode |= ( ((duint64)format) << 56 );
}

void writeOperation64(duint64* byteCode, duint8 op)
{
    *byteCode |= ( ((duint64)op) << 48 );
}

void writeReg64(duint64* byteCode, duint8 reg, duint8 offset)
{
    *byteCode |= ( ((duint64)nR(reg)) << offset );
}

void writeImm64(duint64* byteCode, duint64 imm)
{
    *byteCode |= imm;
}

duint64 car_emitOp64(duint8 format, duint8 opcode, duint8 regDst, duint64 imm)
{
    duint64 byteCode = 0;
    _BIT_SET(byteCode, ( ( sizeof(duint64) * 8 ) - 1ull ) );
    writeFormat64(&byteCode, format);

    switch (format) {
        case CAR_FORMAT_L:
        case CAR_FORMAT_I: {
            writeOperation64(&byteCode, opcode);
            writeReg64(&byteCode, regDst, 43);
            writeImm64(&byteCode, imm & 0x00000000FFFFFFFFull);
            break;
        }
        case CAR_FORMAT_J:
        case CAR_FORMAT_C: {
            writeOperation64(&byteCode, opcode);
            writeImm64(&byteCode, imm & 0x0000FFFFFFFFFFFFull);
            break;
        }
        default: {
            break;
        }
    }

    return byteCode;
}

duint64 car_EmitOp(car_opcodeStruct opcodeStruct)
{
    duint regCount = bitCount(opcodeStruct.regList);

    if (opcodeStruct.regDst == NO_REG) {
        if (opcodeStruct.opcode >= 0x40 && opcodeStruct.opcode <= 0x4F) {
            return car_emitOp64(CAR_FORMAT_J, opcodeStruct.opcode - 0x40,
                         NO_REG,
                         opcodeStruct.immediate);
        }
        else if ( opcodeStruct.opcode >= 0x50 && opcodeStruct.opcode <= 0x5F ) {
            return car_emitOp64(CAR_FORMAT_C, opcodeStruct.opcode - 0x50,
                         NO_REG,
                         opcodeStruct.immediate);
        }
    }

    switch (regCount) {
        case 0: {
            if (opcodeStruct.immediate <= 0xFFFF) {
                return car_emitOp32(CAR_FORMAT_I, opcodeStruct.opcode,
                                    opcodeStruct.regDst,
                                    NO_REG, NO_REG, NO_REG,
                                    opcodeStruct.immediate);
            } else {
                return car_emitOp64(CAR_FORMAT_I, opcodeStruct.opcode,
                                    opcodeStruct.regDst,
                                    opcodeStruct.immediate);
            }
        }
        case 1: {
            duint8 regSrc1 = getNextEnabledBit( opcodeStruct.regList );
            BIT_CLEAR( opcodeStruct.regList, regSrc1 );
            return car_emitOp32(CAR_FORMAT_R, opcodeStruct.opcode,
                                opcodeStruct.regDst,
                                opcodeStruct.regDst, regSrc1, NO_REG,
                                0);
        }
        case 2:
        case 3: {
            duint8 regSrc1 = getNextEnabledBit( opcodeStruct.regList );
            BIT_CLEAR( opcodeStruct.regList, regSrc1 );
            duint8 regSrc2 = getNextEnabledBit( opcodeStruct.regList );
            BIT_CLEAR( opcodeStruct.regList, regSrc2 );
            duint8 regSrc3 = getNextEnabledBit( opcodeStruct.regList );
            BIT_CLEAR( opcodeStruct.regList, regSrc3 );

            return car_emitOp32(CAR_FORMAT_R, opcodeStruct.opcode, opcodeStruct.regDst, regSrc1, regSrc2, regSrc3, 0);
        }
        default: {
            break;
        }
    }

    return car_emitOp64(CAR_FORMAT_L, opcodeStruct.opcode, opcodeStruct.regDst, opcodeStruct.regList);
}
