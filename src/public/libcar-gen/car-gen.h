#ifndef VIRTUALDRAGON_CAR_GEN_H
#define VIRTUALDRAGON_CAR_GEN_H

#include "datatypes.h"

#define NO_REG 0xFF

duint64 car_op32Pack64(duint32 opFirst, duint32 opSecond);

duint32 car_emit_op32(duint8 format, duint8 opcode,
                      duint8 regDst, duint8 regSrc1,
                      duint8 regSrc2, duint8 regSrc3,
                      duint32 imm);

duint64 car_emit_op64(duint8 format, duint8 opcode,
                      duint8 regDst, duint64 imm);

#endif //VIRTUALDRAGON_CAR_GEN_H
