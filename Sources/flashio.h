//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// flashio.h    header file for flashio.c
// =========
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           18/08/2008    
//----------------------------------------------------------------------------

#ifndef __flashio_H
#define __flashio_H 

uint8_t FlashErasePage(uint16_t page);
uint8_t FlashProgramByte(uint16_t address, uint8_t data);

#endif /* __flashio_H */