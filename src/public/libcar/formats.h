#ifndef VIRTUALDRAGON_FORMATS_H
#define VIRTUALDRAGON_FORMATS_H

#define CAR_FORMAT_N 0 // Nop
#define CAR_FORMAT_I 1 // Immediate
#define CAR_FORMAT_R 2 // Register
#define CAR_FORMAT_J 3 // Jump
#define CAR_FORMAT_C 4 // Call

#define CAR_FORMAT_LONG 8 // Long

#define CAR_FORMAT_L 9

#define CAR_FLAG_FORMAT_L (1 << 0)
#define CAR_FLAG_FORMAT_I (1 << 1)
#define CAR_FLAG_FORMAT_R (1 << 2)
#define CAR_FLAG_FORMAT_J (1 << 3)
#define CAR_FLAG_FORMAT_C (1 << 4)

#endif //VIRTUALDRAGON_FORMATS_H
