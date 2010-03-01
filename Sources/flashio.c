//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
//  flashio.c : implement flash read/write routines
//  =========
//
//  Description
//      The MC9S08AW60 has 63280 bytes broken into 124 pages of 512 bytes each
//      The erase function can only work on whole pages.
//      The flash memory addresses are
//          $0870 -> $17FF     and     $1860 -> $FFFF
//      An erased byte location reads as 0xFF
//
//  Notes
//      Based on code outlined in the Freescale MCU forums
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Don            28/02/2008       Freescale 8-bit MCU forums
// Jim Herd           18/08/2008       Routines added to Robokid project
//----------------------------------------------------------------------------
 
#include "global.h"

//
//----------------------------------------------------------------------------
// In RAM subroutine code to manipulate FLASH ROM
//
volatile uint8_t PGM[6]  = {  
    0xf7,                // sta     ,X       FSTAT  
    0x44,                // lsra          -  delay and convert to FCCF bit
    0xf5,                // Bit     ,X       FSTAT
    0x27,0xfd,           // BEQ     *-1
    0x81                 // RTS
}; 

//----------------------------------------------------------------------------
// FlashErasePage : erase a 512 byte block of flash ROM
// ==============
//
// Description
//
uint8_t FlashErasePage(uint16_t page) 
{
   
    asm {
        TPA                ; Get status to A
        PSHA               ; Save current status  
        SEI                ; Disable interrupts
        LDA       #0x30
        STA       FSTAT                   ; Clear FACCERR & FPVIOL flags
        LDHX      page
        STA       ,X                      ; Save the data
        LDA       #0x40                   ; Erase command   #0x40
        STA       FCMD
        LDA       #FSTAT_FCBEF_MASK
        LDHX      @FSTAT 
        JSR       PGM
        PULA              ; Restore previous status
        TAP
    }
    return (FSTAT & 0x30);  
}

//----------------------------------------------------------------------------
// FlashProgramByte : write a byte to an erased flash location
// ================
//
// Notes
//
//
uint8_t FlashProgramByte(uint16_t address, uint8_t data) {
   
    asm{
        TPA  
        PSHA                 ; Save current status  
        SEI                  ; Disable interrupts
        LDA       #0x30
        STA       FSTAT      ; Clear FACCERR & FPVIOL flags
        LDHX      address
        LDA       data
        STA       ,X         ; Save the data
        LDA       #0x20      ; Burn command  #0x20
        STA       FCMD
        LDA       #FSTAT_FCBEF_MASK
        LDHX      @FSTAT 
        JSR       PGM
        PULA                 ; Restore previous status
        TAP
    }
    return (FSTAT & 0x30);
}
