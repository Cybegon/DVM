#include "car-gen.h"

#include "dvmdef.h"

#include "formats.h"

duint64 car_op32Pack64(duint32 opFirst, duint32 opSecond)
{
    return ( (duint64)opFirst << 32u ) | ( (duint64)opSecond );
}

void writeFormat32(duint32* opcode, duint8 format)
{
    *opcode |= ( ((duint32)format) << 28 );
}

void writeOperation32(duint32* opcode, duint8 op)
{
    *opcode |= ( ((duint32)op) << 21 );
}

void writeReg32(duint32* opcode, duint8 reg, duint8 offset)
{
    *opcode |= ( nR(reg) << offset );
}

void writeImm32(duint32* opcode, duint32 imm)
{
    *opcode |= imm;
}

duint32 car_emit_op32(duint8 format, duint8 op,
                      duint8 regDst, duint8 regSrc1,
                      duint8 regSrc2, duint8 regSrc3,
                      duint32 imm)
{
    duint32 opcode = 0;
    writeFormat32(&opcode, format);

    switch (format) {
        case CAR_FORMAT_I: {
            writeOperation32(&opcode, op & 0x7F);
            writeReg32(&opcode, regDst, 16);
            writeImm32(&opcode, imm);
            break;
        }
        case CAR_FORMAT_R: {
            writeOperation32(&opcode, op & 0x7F);
            writeReg32(&opcode, regDst, 16);
            writeReg32(&opcode, regSrc1, 11);
            writeReg32(&opcode, regSrc2, 6);
            if (regSrc3 != NO_REG) {
                writeReg32(&opcode, regSrc3, 1);
                opcode |= 1;
            }
            break;
        }
        case CAR_FORMAT_J:
        case CAR_FORMAT_C: {
            writeOperation32(&opcode, op & 0x0F);
            writeImm32(&opcode, imm & 0x00FFFFFF);
            break;
        }
        default: {
            break;
        }
    }

    return opcode;
}

void writeFormat64(duint64* opcode, duint8 format)
{
    *opcode |= ( ((duint64)format) << 56 );
}

void writeOperation64(duint64* opcode, duint8 op)
{
    *opcode |= ( ((duint64)op) << 48 );
}

void writeReg64(duint64* opcode, duint8 reg, duint8 offset)
{
    *opcode |= ( nR(reg) << offset );
}

void writeImm64(duint64* opcode, duint64 imm)
{
    *opcode |= imm;
}

duint64 car_emit_op64(duint8 format, duint8 op, duint8 regDst, duint64 imm)
{
    duint64 opcode = 0;
    writeFormat64(&opcode, format);

    switch (format) {
        case CAR_FORMAT_L:
        case CAR_FORMAT_I: {
            writeOperation64(&opcode, op);
            writeReg64(&opcode, regDst, 43);
            writeImm64(&opcode, imm & 0x00000000FFFFFFFFull);
            break;
        }
        case CAR_FORMAT_J:
        case CAR_FORMAT_C: {
            writeOperation64(&opcode, op);
            writeImm64(&opcode, imm & 0x0000FFFFFFFFFFFFull);
            break;
        }
        default: {
            break;
        }
    }

    return opcode;
}