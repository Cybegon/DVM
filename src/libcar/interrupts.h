#ifndef VIRTUALDRAGON_INTERRUPTS_H
#define VIRTUALDRAGON_INTERRUPTS_H

#define SVI_EXIT            ( 0x00 )
#define SVI_RESET           ( 0x01 )
#define SVI_TRACE           ( 0x02 )
#define SVI_BREAKPOINT      ( 0x03 )
#define SVI_IO              ( 0x04 )
#define SVI_ILLEGAL_OPCODE  ( 0x05 )
#define SVI_VCPU            ( 0x06 )

#define SVI_INVOKE          ( 0x0F )

#define SVI_CPU_SPECIFIC    ( 0x20 )
#define SVI_FREE            ( 0x40 )

#endif //VIRTUALDRAGON_INTERRUPTS_H
