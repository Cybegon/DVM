#include "car-gen.h"

#include "dvmdef.h"

#include "formats.h"

duint64 car_op32Pack64(duint32 opFirst, duint32 opSecond)
{
    return ( (duint64)opFirst << 32u ) | ( (duint64)opSecond );
}

void writeFormat32(duint32* byteCode, duint8 format)
{
    *byteCode |= ( ((duint32)format) << 28 );
}

void writeOperation32(duint32* byteCode, duint8 op)
{
    *byteCode |= ( ((duint32)op) << 21 );
}

void writeReg32(duint32* byteCode, duint8 reg, duint8 offset)
{
    *byteCode |= ( nR(reg) << offset );
}

void writeImm32(duint32* byteCode, duint32 imm)
{
    *byteCode |= imm;
}

duint32 car_emit_op32(duint8 format, duint8 opcode,
                      duint8 regDst, duint8 regSrc1,
                      duint8 regSrc2, duint8 regSrc3,
                      duint32 imm)
{
    duint32 byteCode = 0;
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

    return byteCode;
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
    *byteCode |= ( nR(reg) << offset );
}

void writeImm64(duint64* byteCode, duint64 imm)
{
    *byteCode |= imm;
}

duint64 car_emit_op64(duint8 format, duint8 opcode, duint8 regDst, duint64 imm)
{
    duint64 byteCode = 0;
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