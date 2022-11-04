#include "libcar-gen/car-gen.h"

#include "libdvm/dvmdef.h"

#define FORMAT_I (1)
#define FORMAT_R (2)
#define FORMAT_J (3)
#define FORMAT_C (4)

void writeFormat(duint32* opcode, duint8 format)
{
    *opcode |= format << 28;
}

void writeOperation(duint32* opcode, duint8 op)
{
    *opcode |= op << 21;
}

void writeReg(duint32* opcode, duint8 reg, duint8 offset)
{
    *opcode |= ( nR(reg) << offset );
}

void writeImm(duint32* opcode, duint32 imm)
{
    *opcode |= imm;
}

duint32 car_emit_op32(duint8 format, duint8 op,
                      duint8 regDst, duint8 regSrc1,
                      duint8 regSrc2, duint8 regSrc3,
                      duint32 imm)
{
    duint32 opcode = 0;
    writeFormat(&opcode, format);

    switch (format) {
        case FORMAT_I: {
            writeOperation(&opcode, op & 0x7F);
            writeReg(&opcode, regDst, 16);
            writeImm(&opcode, imm & 0xFFFF);
            break;
        }
        case FORMAT_R: {
            writeOperation(&opcode, op & 0x7F);
            writeReg(&opcode, regDst, 16);
            writeReg(&opcode, regSrc1, 11);
            writeReg(&opcode, regSrc2, 6);
            if (regSrc3 != NO_REG) {
                writeReg(&opcode, regSrc3, 1);
                opcode |= 1;
            }
            break;
        }
        case FORMAT_J:
        case FORMAT_C: {
            writeOperation(&opcode, op & 0x0F);
            writeImm(&opcode, imm & 0x00FFFFFF);
            break;
        }
        default: {
            break;
        }
    }

    return opcode;
}
