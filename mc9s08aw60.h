/* Based on CPU DB MC9S08AW60_64, version 2.87.184 (RegistersPrg V2.18) */
/*
** ###################################################################
**     Filename  : mc9s08aw60.h
**     Processor : MC9S08AW60CFU
**     FileFormat: V2.18
**     DataSheet : MC9S08AW60 Rev 2 12/2006
**     Compiler  : CodeWarrior compiler
**     Date/Time : 25.7.2007, 8:49
**     Abstract  :
**         This header implements the mapping of I/O devices.
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2006
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
**
**     File-Format-Revisions:
**      - 14.11.2005, V2.00 :
**               - Deprecated symbols added for backward compatibility (section at the end of this file)
**      - 15.11.2005, V2.01 :
**               - Revision is not related to this file (CPU family)
**      - 17.12.2005, V2.02 :
**               - Arrays (symbols xx_ARR) are defined as pointer to volatile, see issue #2778
**      - 16.01.2006, V2.03 :
**               - Fixed declaration of non volatile registers. Now it does not require (but allows) their initialization, see issue #2920.
**               - "volatile" modifier removed from declaration of non volatile registers (that contain modifier "const")
**      - 08.03.2006, V2.04 :
**               - Support for bit(s) names duplicated with any register name in .h header files
**      - 24.03.2006, V2.05 :
**               - Revision is not related to this file (CPU family)
**      - 26.04.2006, V2.06 :
**               - Absolute assembly supported (depreciated symbols are not defined)
**      - 27.04.2006, V2.07 :
**               - Fixed macro __RESET_WATCHDOG for HCS12, HCS12X ,HCS08 DZ and HCS08 EN derivatives (write 0x55,0xAA).
**      - 07.06.2006, V2.08 :
**               - For .inc files added constants "RAMStart" and "RAMEnd" even there is only Z_RAM.
**      - 03.07.2006, V2.09 :
**               - Flash commands constants supported
**      - 27.10.2006, V2.10 :
**               - __RESET_WATCHDOG improved formating and re-definition
**      - 23.11.2006, V2.11 :
**               - Revision is not related to this file (CPU family)
**      - 22.01.2007, V2.12 :
**               - Revision is not related to this file (CPU family)
**      - 01.03.2007, V2.13 :
**               - Flash commands constants values converted to HEX format
**      - 02.03.2007, V2.14 :
**               - Interrupt vector numbers added into .H, see VectorNumber_*
**      - 26.03.2007, V2.15 :
**               - Revision is not related to this file (CPU family)
**      - 10.05.2007, V2.16 :
**               - Fixed flash commands definition for ColdFireV1 assembler (equ -> .equ)
**      - 05.06.2007, V2.17 :
**               - Revision is not related to this file (CPU family)
**      - 19.07.2007, V2.18 :
**               - Improved number of blanked lines inside register structures
**
**     CPU Registers Revisions:
**      - 20.02.2006, V2.87.152:
**              - Renamed ADC registers AD1* ==> ADC1*, Renamed bits NVPROT_FPS0..6 ==> NVPROT_FPS1..7, 
**              - Renamed bits IIC1A_ADDR0..6 ==> IIC1A_ADDR1..7
**              - REASON: Changes in data sheet (from rev 0 to rev 1.0)
**      - 23.02.2007, V2.87.180:
**              - Renamed register KBISC ==> KBI1SC,  Renamed register KBIPE ==> KBI1PE. REASON: Changes in data sheet (from rev 1.0 to rev 2.0) 
** ###################################################################
*/

#ifndef _MC9S08AW60_H
#define _MC9S08AW60_H

/* Types definition */
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;
typedef unsigned long dlong[2];

/* Watchdog reset macro */
#ifndef __RESET_WATCHDOG
#ifdef _lint
  #define __RESET_WATCHDOG()  /* empty */
#else
  #define __RESET_WATCHDOG() {asm sta SRS;}
#endif
#endif /* __RESET_WATCHDOG */

#define REG_BASE 0x0000                /* Base address for the I/O register block */


#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */

/**************** interrupt vector numbers ****************/
#define VectorNumber_Vrti               25
#define VectorNumber_Viic1              24
#define VectorNumber_Vadc1              23
#define VectorNumber_Vkeyboard1         22
#define VectorNumber_Vsci2tx            21
#define VectorNumber_Vsci2rx            20
#define VectorNumber_Vsci2err           19
#define VectorNumber_Vsci1tx            18
#define VectorNumber_Vsci1rx            17
#define VectorNumber_Vsci1err           16
#define VectorNumber_Vspi1              15
#define VectorNumber_Vtpm2ovf           14
#define VectorNumber_Vtpm2ch1           13
#define VectorNumber_Vtpm2ch0           12
#define VectorNumber_Vtpm1ovf           11
#define VectorNumber_Vtpm1ch5           10
#define VectorNumber_Vtpm1ch4           9
#define VectorNumber_Vtpm1ch3           8
#define VectorNumber_Vtpm1ch2           7
#define VectorNumber_Vtpm1ch1           6
#define VectorNumber_Vtpm1ch0           5
#define VectorNumber_Vicg               4
#define VectorNumber_Vlvd               3
#define VectorNumber_Virq               2
#define VectorNumber_Vswi               1
#define VectorNumber_Vreset             0

/**************** interrupt vector table ****************/
#define Vrti                            0x0000FFCC
#define Viic1                           0x0000FFCE
#define Vadc1                           0x0000FFD0
#define Vkeyboard1                      0x0000FFD2
#define Vsci2tx                         0x0000FFD4
#define Vsci2rx                         0x0000FFD6
#define Vsci2err                        0x0000FFD8
#define Vsci1tx                         0x0000FFDA
#define Vsci1rx                         0x0000FFDC
#define Vsci1err                        0x0000FFDE
#define Vspi1                           0x0000FFE0
#define Vtpm2ovf                        0x0000FFE2
#define Vtpm2ch1                        0x0000FFE4
#define Vtpm2ch0                        0x0000FFE6
#define Vtpm1ovf                        0x0000FFE8
#define Vtpm1ch5                        0x0000FFEA
#define Vtpm1ch4                        0x0000FFEC
#define Vtpm1ch3                        0x0000FFEE
#define Vtpm1ch2                        0x0000FFF0
#define Vtpm1ch1                        0x0000FFF2
#define Vtpm1ch0                        0x0000FFF4
#define Vicg                            0x0000FFF6
#define Vlvd                            0x0000FFF8
#define Virq                            0x0000FFFA
#define Vswi                            0x0000FFFC
#define Vreset                          0x0000FFFE

/**************** registers I/O map ****************/

/*** PTAD - Port A Data Register; 0x00000000 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAD0       :1;                                       /* Port A Data Register Bit 0 */
    byte PTAD1       :1;                                       /* Port A Data Register Bit 1 */
    byte PTAD2       :1;                                       /* Port A Data Register Bit 2 */
    byte PTAD3       :1;                                       /* Port A Data Register Bit 3 */
    byte PTAD4       :1;                                       /* Port A Data Register Bit 4 */
    byte PTAD5       :1;                                       /* Port A Data Register Bit 5 */
    byte PTAD6       :1;                                       /* Port A Data Register Bit 6 */
    byte PTAD7       :1;                                       /* Port A Data Register Bit 7 */
  } Bits;
} PTADSTR;
extern volatile PTADSTR _PTAD @0x00000000;
#define PTAD                            _PTAD.Byte
#define PTAD_PTAD0                      _PTAD.Bits.PTAD0
#define PTAD_PTAD1                      _PTAD.Bits.PTAD1
#define PTAD_PTAD2                      _PTAD.Bits.PTAD2
#define PTAD_PTAD3                      _PTAD.Bits.PTAD3
#define PTAD_PTAD4                      _PTAD.Bits.PTAD4
#define PTAD_PTAD5                      _PTAD.Bits.PTAD5
#define PTAD_PTAD6                      _PTAD.Bits.PTAD6
#define PTAD_PTAD7                      _PTAD.Bits.PTAD7

#define PTAD_PTAD0_MASK                 1
#define PTAD_PTAD1_MASK                 2
#define PTAD_PTAD2_MASK                 4
#define PTAD_PTAD3_MASK                 8
#define PTAD_PTAD4_MASK                 16
#define PTAD_PTAD5_MASK                 32
#define PTAD_PTAD6_MASK                 64
#define PTAD_PTAD7_MASK                 128


/*** PTADD - Data Direction Register A; 0x00000001 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADD0      :1;                                       /* Data Direction for Port A Bit 0 */
    byte PTADD1      :1;                                       /* Data Direction for Port A Bit 1 */
    byte PTADD2      :1;                                       /* Data Direction for Port A Bit 2 */
    byte PTADD3      :1;                                       /* Data Direction for Port A Bit 3 */
    byte PTADD4      :1;                                       /* Data Direction for Port A Bit 4 */
    byte PTADD5      :1;                                       /* Data Direction for Port A Bit 5 */
    byte PTADD6      :1;                                       /* Data Direction for Port A Bit 6 */
    byte PTADD7      :1;                                       /* Data Direction for Port A Bit 7 */
  } Bits;
} PTADDSTR;
extern volatile PTADDSTR _PTADD @0x00000001;
#define PTADD                           _PTADD.Byte
#define PTADD_PTADD0                    _PTADD.Bits.PTADD0
#define PTADD_PTADD1                    _PTADD.Bits.PTADD1
#define PTADD_PTADD2                    _PTADD.Bits.PTADD2
#define PTADD_PTADD3                    _PTADD.Bits.PTADD3
#define PTADD_PTADD4                    _PTADD.Bits.PTADD4
#define PTADD_PTADD5                    _PTADD.Bits.PTADD5
#define PTADD_PTADD6                    _PTADD.Bits.PTADD6
#define PTADD_PTADD7                    _PTADD.Bits.PTADD7

#define PTADD_PTADD0_MASK               1
#define PTADD_PTADD1_MASK               2
#define PTADD_PTADD2_MASK               4
#define PTADD_PTADD3_MASK               8
#define PTADD_PTADD4_MASK               16
#define PTADD_PTADD5_MASK               32
#define PTADD_PTADD6_MASK               64
#define PTADD_PTADD7_MASK               128


/*** PTBD - Port B Data Register; 0x00000002 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBD0       :1;                                       /* Port B Data Register Bit 0 */
    byte PTBD1       :1;                                       /* Port B Data Register Bit 1 */
    byte PTBD2       :1;                                       /* Port B Data Register Bit 2 */
    byte PTBD3       :1;                                       /* Port B Data Register Bit 3 */
    byte PTBD4       :1;                                       /* Port B Data Register Bit 4 */
    byte PTBD5       :1;                                       /* Port B Data Register Bit 5 */
    byte PTBD6       :1;                                       /* Port B Data Register Bit 6 */
    byte PTBD7       :1;                                       /* Port B Data Register Bit 7 */
  } Bits;
} PTBDSTR;
extern volatile PTBDSTR _PTBD @0x00000002;
#define PTBD                            _PTBD.Byte
#define PTBD_PTBD0                      _PTBD.Bits.PTBD0
#define PTBD_PTBD1                      _PTBD.Bits.PTBD1
#define PTBD_PTBD2                      _PTBD.Bits.PTBD2
#define PTBD_PTBD3                      _PTBD.Bits.PTBD3
#define PTBD_PTBD4                      _PTBD.Bits.PTBD4
#define PTBD_PTBD5                      _PTBD.Bits.PTBD5
#define PTBD_PTBD6                      _PTBD.Bits.PTBD6
#define PTBD_PTBD7                      _PTBD.Bits.PTBD7

#define PTBD_PTBD0_MASK                 1
#define PTBD_PTBD1_MASK                 2
#define PTBD_PTBD2_MASK                 4
#define PTBD_PTBD3_MASK                 8
#define PTBD_PTBD4_MASK                 16
#define PTBD_PTBD5_MASK                 32
#define PTBD_PTBD6_MASK                 64
#define PTBD_PTBD7_MASK                 128


/*** PTBDD - Data Direction Register B; 0x00000003 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDD0      :1;                                       /* Data Direction for Port B Bit 0 */
    byte PTBDD1      :1;                                       /* Data Direction for Port B Bit 1 */
    byte PTBDD2      :1;                                       /* Data Direction for Port B Bit 2 */
    byte PTBDD3      :1;                                       /* Data Direction for Port B Bit 3 */
    byte PTBDD4      :1;                                       /* Data Direction for Port B Bit 4 */
    byte PTBDD5      :1;                                       /* Data Direction for Port B Bit 5 */
    byte PTBDD6      :1;                                       /* Data Direction for Port B Bit 6 */
    byte PTBDD7      :1;                                       /* Data Direction for Port B Bit 7 */
  } Bits;
} PTBDDSTR;
extern volatile PTBDDSTR _PTBDD @0x00000003;
#define PTBDD                           _PTBDD.Byte
#define PTBDD_PTBDD0                    _PTBDD.Bits.PTBDD0
#define PTBDD_PTBDD1                    _PTBDD.Bits.PTBDD1
#define PTBDD_PTBDD2                    _PTBDD.Bits.PTBDD2
#define PTBDD_PTBDD3                    _PTBDD.Bits.PTBDD3
#define PTBDD_PTBDD4                    _PTBDD.Bits.PTBDD4
#define PTBDD_PTBDD5                    _PTBDD.Bits.PTBDD5
#define PTBDD_PTBDD6                    _PTBDD.Bits.PTBDD6
#define PTBDD_PTBDD7                    _PTBDD.Bits.PTBDD7

#define PTBDD_PTBDD0_MASK               1
#define PTBDD_PTBDD1_MASK               2
#define PTBDD_PTBDD2_MASK               4
#define PTBDD_PTBDD3_MASK               8
#define PTBDD_PTBDD4_MASK               16
#define PTBDD_PTBDD5_MASK               32
#define PTBDD_PTBDD6_MASK               64
#define PTBDD_PTBDD7_MASK               128


/*** PTCD - Port C Data Register; 0x00000004 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCD0       :1;                                       /* Port C Data Register Bit 0 */
    byte PTCD1       :1;                                       /* Port C Data Register Bit 1 */
    byte PTCD2       :1;                                       /* Port C Data Register Bit 2 */
    byte PTCD3       :1;                                       /* Port C Data Register Bit 3 */
    byte PTCD4       :1;                                       /* Port C Data Register Bit 4 */
    byte PTCD5       :1;                                       /* Port C Data Register Bit 5 */
    byte PTCD6       :1;                                       /* Port C Data Register Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTCD :7;
    byte         :1;
  } MergedBits;
} PTCDSTR;
extern volatile PTCDSTR _PTCD @0x00000004;
#define PTCD                            _PTCD.Byte
#define PTCD_PTCD0                      _PTCD.Bits.PTCD0
#define PTCD_PTCD1                      _PTCD.Bits.PTCD1
#define PTCD_PTCD2                      _PTCD.Bits.PTCD2
#define PTCD_PTCD3                      _PTCD.Bits.PTCD3
#define PTCD_PTCD4                      _PTCD.Bits.PTCD4
#define PTCD_PTCD5                      _PTCD.Bits.PTCD5
#define PTCD_PTCD6                      _PTCD.Bits.PTCD6
#define PTCD_PTCD                       _PTCD.MergedBits.grpPTCD

#define PTCD_PTCD0_MASK                 1
#define PTCD_PTCD1_MASK                 2
#define PTCD_PTCD2_MASK                 4
#define PTCD_PTCD3_MASK                 8
#define PTCD_PTCD4_MASK                 16
#define PTCD_PTCD5_MASK                 32
#define PTCD_PTCD6_MASK                 64
#define PTCD_PTCD_MASK                  127
#define PTCD_PTCD_BITNUM                0


/*** PTCDD - Data Direction Register C; 0x00000005 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDD0      :1;                                       /* Data Direction for Port C Bit 0 */
    byte PTCDD1      :1;                                       /* Data Direction for Port C Bit 1 */
    byte PTCDD2      :1;                                       /* Data Direction for Port C Bit 2 */
    byte PTCDD3      :1;                                       /* Data Direction for Port C Bit 3 */
    byte PTCDD4      :1;                                       /* Data Direction for Port C Bit 4 */
    byte PTCDD5      :1;                                       /* Data Direction for Port C Bit 5 */
    byte PTCDD6      :1;                                       /* Data Direction for Port C Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTCDD :7;
    byte         :1;
  } MergedBits;
} PTCDDSTR;
extern volatile PTCDDSTR _PTCDD @0x00000005;
#define PTCDD                           _PTCDD.Byte
#define PTCDD_PTCDD0                    _PTCDD.Bits.PTCDD0
#define PTCDD_PTCDD1                    _PTCDD.Bits.PTCDD1
#define PTCDD_PTCDD2                    _PTCDD.Bits.PTCDD2
#define PTCDD_PTCDD3                    _PTCDD.Bits.PTCDD3
#define PTCDD_PTCDD4                    _PTCDD.Bits.PTCDD4
#define PTCDD_PTCDD5                    _PTCDD.Bits.PTCDD5
#define PTCDD_PTCDD6                    _PTCDD.Bits.PTCDD6
#define PTCDD_PTCDD                     _PTCDD.MergedBits.grpPTCDD

#define PTCDD_PTCDD0_MASK               1
#define PTCDD_PTCDD1_MASK               2
#define PTCDD_PTCDD2_MASK               4
#define PTCDD_PTCDD3_MASK               8
#define PTCDD_PTCDD4_MASK               16
#define PTCDD_PTCDD5_MASK               32
#define PTCDD_PTCDD6_MASK               64
#define PTCDD_PTCDD_MASK                127
#define PTCDD_PTCDD_BITNUM              0


/*** PTDD - Port D Data Register; 0x00000006 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDD0       :1;                                       /* Port D Data Register Bit 0 */
    byte PTDD1       :1;                                       /* Port D Data Register Bit 1 */
    byte PTDD2       :1;                                       /* Port D Data Register Bit 2 */
    byte PTDD3       :1;                                       /* Port D Data Register Bit 3 */
    byte PTDD4       :1;                                       /* Port D Data Register Bit 4 */
    byte PTDD5       :1;                                       /* Port D Data Register Bit 5 */
    byte PTDD6       :1;                                       /* Port D Data Register Bit 6 */
    byte PTDD7       :1;                                       /* Port D Data Register Bit 7 */
  } Bits;
} PTDDSTR;
extern volatile PTDDSTR _PTDD @0x00000006;
#define PTDD                            _PTDD.Byte
#define PTDD_PTDD0                      _PTDD.Bits.PTDD0
#define PTDD_PTDD1                      _PTDD.Bits.PTDD1
#define PTDD_PTDD2                      _PTDD.Bits.PTDD2
#define PTDD_PTDD3                      _PTDD.Bits.PTDD3
#define PTDD_PTDD4                      _PTDD.Bits.PTDD4
#define PTDD_PTDD5                      _PTDD.Bits.PTDD5
#define PTDD_PTDD6                      _PTDD.Bits.PTDD6
#define PTDD_PTDD7                      _PTDD.Bits.PTDD7

#define PTDD_PTDD0_MASK                 1
#define PTDD_PTDD1_MASK                 2
#define PTDD_PTDD2_MASK                 4
#define PTDD_PTDD3_MASK                 8
#define PTDD_PTDD4_MASK                 16
#define PTDD_PTDD5_MASK                 32
#define PTDD_PTDD6_MASK                 64
#define PTDD_PTDD7_MASK                 128


/*** PTDDD - Data Direction Register D; 0x00000007 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDD0      :1;                                       /* Data Direction for Port D Bit 0 */
    byte PTDDD1      :1;                                       /* Data Direction for Port D Bit 1 */
    byte PTDDD2      :1;                                       /* Data Direction for Port D Bit 2 */
    byte PTDDD3      :1;                                       /* Data Direction for Port D Bit 3 */
    byte PTDDD4      :1;                                       /* Data Direction for Port D Bit 4 */
    byte PTDDD5      :1;                                       /* Data Direction for Port D Bit 5 */
    byte PTDDD6      :1;                                       /* Data Direction for Port D Bit 6 */
    byte PTDDD7      :1;                                       /* Data Direction for Port D Bit 7 */
  } Bits;
} PTDDDSTR;
extern volatile PTDDDSTR _PTDDD @0x00000007;
#define PTDDD                           _PTDDD.Byte
#define PTDDD_PTDDD0                    _PTDDD.Bits.PTDDD0
#define PTDDD_PTDDD1                    _PTDDD.Bits.PTDDD1
#define PTDDD_PTDDD2                    _PTDDD.Bits.PTDDD2
#define PTDDD_PTDDD3                    _PTDDD.Bits.PTDDD3
#define PTDDD_PTDDD4                    _PTDDD.Bits.PTDDD4
#define PTDDD_PTDDD5                    _PTDDD.Bits.PTDDD5
#define PTDDD_PTDDD6                    _PTDDD.Bits.PTDDD6
#define PTDDD_PTDDD7                    _PTDDD.Bits.PTDDD7

#define PTDDD_PTDDD0_MASK               1
#define PTDDD_PTDDD1_MASK               2
#define PTDDD_PTDDD2_MASK               4
#define PTDDD_PTDDD3_MASK               8
#define PTDDD_PTDDD4_MASK               16
#define PTDDD_PTDDD5_MASK               32
#define PTDDD_PTDDD6_MASK               64
#define PTDDD_PTDDD7_MASK               128


/*** PTED - Port E Data Register; 0x00000008 ***/
typedef union {
  byte Byte;
  struct {
    byte PTED0       :1;                                       /* Port E Data Register Bit 0 */
    byte PTED1       :1;                                       /* Port E Data Register Bit 1 */
    byte PTED2       :1;                                       /* Port E Data Register Bit 2 */
    byte PTED3       :1;                                       /* Port E Data Register Bit 3 */
    byte PTED4       :1;                                       /* Port E Data Register Bit 4 */
    byte PTED5       :1;                                       /* Port E Data Register Bit 5 */
    byte PTED6       :1;                                       /* Port E Data Register Bit 6 */
    byte PTED7       :1;                                       /* Port E Data Register Bit 7 */
  } Bits;
} PTEDSTR;
extern volatile PTEDSTR _PTED @0x00000008;
#define PTED                            _PTED.Byte
#define PTED_PTED0                      _PTED.Bits.PTED0
#define PTED_PTED1                      _PTED.Bits.PTED1
#define PTED_PTED2                      _PTED.Bits.PTED2
#define PTED_PTED3                      _PTED.Bits.PTED3
#define PTED_PTED4                      _PTED.Bits.PTED4
#define PTED_PTED5                      _PTED.Bits.PTED5
#define PTED_PTED6                      _PTED.Bits.PTED6
#define PTED_PTED7                      _PTED.Bits.PTED7

#define PTED_PTED0_MASK                 1
#define PTED_PTED1_MASK                 2
#define PTED_PTED2_MASK                 4
#define PTED_PTED3_MASK                 8
#define PTED_PTED4_MASK                 16
#define PTED_PTED5_MASK                 32
#define PTED_PTED6_MASK                 64
#define PTED_PTED7_MASK                 128


/*** PTEDD - Data Direction Register E; 0x00000009 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDD0      :1;                                       /* Data Direction for Port E Bit 0 */
    byte PTEDD1      :1;                                       /* Data Direction for Port E Bit 1 */
    byte PTEDD2      :1;                                       /* Data Direction for Port E Bit 2 */
    byte PTEDD3      :1;                                       /* Data Direction for Port E Bit 3 */
    byte PTEDD4      :1;                                       /* Data Direction for Port E Bit 4 */
    byte PTEDD5      :1;                                       /* Data Direction for Port E Bit 5 */
    byte PTEDD6      :1;                                       /* Data Direction for Port E Bit 6 */
    byte PTEDD7      :1;                                       /* Data Direction for Port E Bit 7 */
  } Bits;
} PTEDDSTR;
extern volatile PTEDDSTR _PTEDD @0x00000009;
#define PTEDD                           _PTEDD.Byte
#define PTEDD_PTEDD0                    _PTEDD.Bits.PTEDD0
#define PTEDD_PTEDD1                    _PTEDD.Bits.PTEDD1
#define PTEDD_PTEDD2                    _PTEDD.Bits.PTEDD2
#define PTEDD_PTEDD3                    _PTEDD.Bits.PTEDD3
#define PTEDD_PTEDD4                    _PTEDD.Bits.PTEDD4
#define PTEDD_PTEDD5                    _PTEDD.Bits.PTEDD5
#define PTEDD_PTEDD6                    _PTEDD.Bits.PTEDD6
#define PTEDD_PTEDD7                    _PTEDD.Bits.PTEDD7

#define PTEDD_PTEDD0_MASK               1
#define PTEDD_PTEDD1_MASK               2
#define PTEDD_PTEDD2_MASK               4
#define PTEDD_PTEDD3_MASK               8
#define PTEDD_PTEDD4_MASK               16
#define PTEDD_PTEDD5_MASK               32
#define PTEDD_PTEDD6_MASK               64
#define PTEDD_PTEDD7_MASK               128


/*** PTFD - Port F Data Register; 0x0000000A ***/
typedef union {
  byte Byte;
  struct {
    byte PTFD0       :1;                                       /* Port F Data Register Bit 0 */
    byte PTFD1       :1;                                       /* Port F Data Register Bit 1 */
    byte PTFD2       :1;                                       /* Port F Data Register Bit 2 */
    byte PTFD3       :1;                                       /* Port F Data Register Bit 3 */
    byte PTFD4       :1;                                       /* Port F Data Register Bit 4 */
    byte PTFD5       :1;                                       /* Port F Data Register Bit 5 */
    byte PTFD6       :1;                                       /* Port F Data Register Bit 6 */
    byte PTFD7       :1;                                       /* Port F Data Register Bit 7 */
  } Bits;
} PTFDSTR;
extern volatile PTFDSTR _PTFD @0x0000000A;
#define PTFD                            _PTFD.Byte
#define PTFD_PTFD0                      _PTFD.Bits.PTFD0
#define PTFD_PTFD1                      _PTFD.Bits.PTFD1
#define PTFD_PTFD2                      _PTFD.Bits.PTFD2
#define PTFD_PTFD3                      _PTFD.Bits.PTFD3
#define PTFD_PTFD4                      _PTFD.Bits.PTFD4
#define PTFD_PTFD5                      _PTFD.Bits.PTFD5
#define PTFD_PTFD6                      _PTFD.Bits.PTFD6
#define PTFD_PTFD7                      _PTFD.Bits.PTFD7

#define PTFD_PTFD0_MASK                 1
#define PTFD_PTFD1_MASK                 2
#define PTFD_PTFD2_MASK                 4
#define PTFD_PTFD3_MASK                 8
#define PTFD_PTFD4_MASK                 16
#define PTFD_PTFD5_MASK                 32
#define PTFD_PTFD6_MASK                 64
#define PTFD_PTFD7_MASK                 128


/*** PTFDD - Data Direction Register F; 0x0000000B ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDD0      :1;                                       /* Data Direction for Port F Bit 0 */
    byte PTFDD1      :1;                                       /* Data Direction for Port F Bit 1 */
    byte PTFDD2      :1;                                       /* Data Direction for Port F Bit 2 */
    byte PTFDD3      :1;                                       /* Data Direction for Port F Bit 3 */
    byte PTFDD4      :1;                                       /* Data Direction for Port F Bit 4 */
    byte PTFDD5      :1;                                       /* Data Direction for Port F Bit 5 */
    byte PTFDD6      :1;                                       /* Data Direction for Port F Bit 6 */
    byte PTFDD7      :1;                                       /* Data Direction for Port F Bit 7 */
  } Bits;
} PTFDDSTR;
extern volatile PTFDDSTR _PTFDD @0x0000000B;
#define PTFDD                           _PTFDD.Byte
#define PTFDD_PTFDD0                    _PTFDD.Bits.PTFDD0
#define PTFDD_PTFDD1                    _PTFDD.Bits.PTFDD1
#define PTFDD_PTFDD2                    _PTFDD.Bits.PTFDD2
#define PTFDD_PTFDD3                    _PTFDD.Bits.PTFDD3
#define PTFDD_PTFDD4                    _PTFDD.Bits.PTFDD4
#define PTFDD_PTFDD5                    _PTFDD.Bits.PTFDD5
#define PTFDD_PTFDD6                    _PTFDD.Bits.PTFDD6
#define PTFDD_PTFDD7                    _PTFDD.Bits.PTFDD7

#define PTFDD_PTFDD0_MASK               1
#define PTFDD_PTFDD1_MASK               2
#define PTFDD_PTFDD2_MASK               4
#define PTFDD_PTFDD3_MASK               8
#define PTFDD_PTFDD4_MASK               16
#define PTFDD_PTFDD5_MASK               32
#define PTFDD_PTFDD6_MASK               64
#define PTFDD_PTFDD7_MASK               128


/*** PTGD - Port G Data Register; 0x0000000C ***/
typedef union {
  byte Byte;
  struct {
    byte PTGD0       :1;                                       /* Port G Data Register Bit 0 */
    byte PTGD1       :1;                                       /* Port G Data Register Bit 1 */
    byte PTGD2       :1;                                       /* Port G Data Register Bit 2 */
    byte PTGD3       :1;                                       /* Port G Data Register Bit 3 */
    byte PTGD4       :1;                                       /* Port G Data Register Bit 4 */
    byte PTGD5       :1;                                       /* Port G Data Register Bit 5 */
    byte PTGD6       :1;                                       /* Port G Data Register Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTGD :7;
    byte         :1;
  } MergedBits;
} PTGDSTR;
extern volatile PTGDSTR _PTGD @0x0000000C;
#define PTGD                            _PTGD.Byte
#define PTGD_PTGD0                      _PTGD.Bits.PTGD0
#define PTGD_PTGD1                      _PTGD.Bits.PTGD1
#define PTGD_PTGD2                      _PTGD.Bits.PTGD2
#define PTGD_PTGD3                      _PTGD.Bits.PTGD3
#define PTGD_PTGD4                      _PTGD.Bits.PTGD4
#define PTGD_PTGD5                      _PTGD.Bits.PTGD5
#define PTGD_PTGD6                      _PTGD.Bits.PTGD6
#define PTGD_PTGD                       _PTGD.MergedBits.grpPTGD

#define PTGD_PTGD0_MASK                 1
#define PTGD_PTGD1_MASK                 2
#define PTGD_PTGD2_MASK                 4
#define PTGD_PTGD3_MASK                 8
#define PTGD_PTGD4_MASK                 16
#define PTGD_PTGD5_MASK                 32
#define PTGD_PTGD6_MASK                 64
#define PTGD_PTGD_MASK                  127
#define PTGD_PTGD_BITNUM                0


/*** PTGDD - Data Direction Register G; 0x0000000D ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDD0      :1;                                       /* Data Direction for Port G Bit 0 */
    byte PTGDD1      :1;                                       /* Data Direction for Port G Bit 1 */
    byte PTGDD2      :1;                                       /* Data Direction for Port G Bit 2 */
    byte PTGDD3      :1;                                       /* Data Direction for Port G Bit 3 */
    byte PTGDD4      :1;                                       /* Data Direction for Port G Bit 4 */
    byte PTGDD5      :1;                                       /* Data Direction for Port G Bit 5 */
    byte PTGDD6      :1;                                       /* Data Direction for Port G Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTGDD :7;
    byte         :1;
  } MergedBits;
} PTGDDSTR;
extern volatile PTGDDSTR _PTGDD @0x0000000D;
#define PTGDD                           _PTGDD.Byte
#define PTGDD_PTGDD0                    _PTGDD.Bits.PTGDD0
#define PTGDD_PTGDD1                    _PTGDD.Bits.PTGDD1
#define PTGDD_PTGDD2                    _PTGDD.Bits.PTGDD2
#define PTGDD_PTGDD3                    _PTGDD.Bits.PTGDD3
#define PTGDD_PTGDD4                    _PTGDD.Bits.PTGDD4
#define PTGDD_PTGDD5                    _PTGDD.Bits.PTGDD5
#define PTGDD_PTGDD6                    _PTGDD.Bits.PTGDD6
#define PTGDD_PTGDD                     _PTGDD.MergedBits.grpPTGDD

#define PTGDD_PTGDD0_MASK               1
#define PTGDD_PTGDD1_MASK               2
#define PTGDD_PTGDD2_MASK               4
#define PTGDD_PTGDD3_MASK               8
#define PTGDD_PTGDD4_MASK               16
#define PTGDD_PTGDD5_MASK               32
#define PTGDD_PTGDD6_MASK               64
#define PTGDD_PTGDD_MASK                127
#define PTGDD_PTGDD_BITNUM              0


/*** ADC1SC1 - Status and Control Register; 0x00000010 ***/
typedef union {
  byte Byte;
  struct {
    byte ADCH0       :1;                                       /* Input Channel Select Bit 0 */
    byte ADCH1       :1;                                       /* Input Channel Select Bit 1 */
    byte ADCH2       :1;                                       /* Input Channel Select Bit 2 */
    byte ADCH3       :1;                                       /* Input Channel Select Bit 3 */
    byte ADCH4       :1;                                       /* Input Channel Select Bit 4 */
    byte ADCO        :1;                                       /* Continuous Conversion Enable */
    byte AIEN        :1;                                       /* Interrupt Enable */
    byte COCO        :1;                                       /* Conversion Complete Flag */
  } Bits;
  struct {
    byte grpADCH :5;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ADC1SC1STR;
extern volatile ADC1SC1STR _ADC1SC1 @0x00000010;
#define ADC1SC1                         _ADC1SC1.Byte
#define ADC1SC1_ADCH0                   _ADC1SC1.Bits.ADCH0
#define ADC1SC1_ADCH1                   _ADC1SC1.Bits.ADCH1
#define ADC1SC1_ADCH2                   _ADC1SC1.Bits.ADCH2
#define ADC1SC1_ADCH3                   _ADC1SC1.Bits.ADCH3
#define ADC1SC1_ADCH4                   _ADC1SC1.Bits.ADCH4
#define ADC1SC1_ADCO                    _ADC1SC1.Bits.ADCO
#define ADC1SC1_AIEN                    _ADC1SC1.Bits.AIEN
#define ADC1SC1_COCO                    _ADC1SC1.Bits.COCO
#define ADC1SC1_ADCH                    _ADC1SC1.MergedBits.grpADCH

#define ADC1SC1_ADCH0_MASK              1
#define ADC1SC1_ADCH1_MASK              2
#define ADC1SC1_ADCH2_MASK              4
#define ADC1SC1_ADCH3_MASK              8
#define ADC1SC1_ADCH4_MASK              16
#define ADC1SC1_ADCO_MASK               32
#define ADC1SC1_AIEN_MASK               64
#define ADC1SC1_COCO_MASK               128
#define ADC1SC1_ADCH_MASK               31
#define ADC1SC1_ADCH_BITNUM             0


/*** ADC1SC2 - Status and Control Register 2; 0x00000011 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ACFGT       :1;                                       /* Compare Function Greater Than Enable */
    byte ACFE        :1;                                       /* Compare Function Enable */
    byte ADTRG       :1;                                       /* Conversion Trigger Select */
    byte ADACT       :1;                                       /* Conversion Active */
  } Bits;
} ADC1SC2STR;
extern volatile ADC1SC2STR _ADC1SC2 @0x00000011;
#define ADC1SC2                         _ADC1SC2.Byte
#define ADC1SC2_ACFGT                   _ADC1SC2.Bits.ACFGT
#define ADC1SC2_ACFE                    _ADC1SC2.Bits.ACFE
#define ADC1SC2_ADTRG                   _ADC1SC2.Bits.ADTRG
#define ADC1SC2_ADACT                   _ADC1SC2.Bits.ADACT

#define ADC1SC2_ACFGT_MASK              16
#define ADC1SC2_ACFE_MASK               32
#define ADC1SC2_ADTRG_MASK              64
#define ADC1SC2_ADACT_MASK              128


/*** ADC1R - ADC10 Result Data Right Justified; 0x00000012 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADC1RH - ADC10 Result Data Right Justified High; 0x00000012 ***/
    union {
      byte Byte;
      struct {
        byte ADR8        :1;                                       /* ADC10 Result Data Bit 8 */
        byte ADR9        :1;                                       /* ADC10 Result Data Bit 9 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpADR_8 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADC1RHSTR;
    #define ADC1RH                      _ADC1R.Overlap_STR.ADC1RHSTR.Byte
    #define ADC1RH_ADR8                 _ADC1R.Overlap_STR.ADC1RHSTR.Bits.ADR8
    #define ADC1RH_ADR9                 _ADC1R.Overlap_STR.ADC1RHSTR.Bits.ADR9
    #define ADC1RH_ADR_8                _ADC1R.Overlap_STR.ADC1RHSTR.MergedBits.grpADR_8
    #define ADC1RH_ADR                  ADC1RH_ADR_8
    
    #define ADC1RH_ADR8_MASK            1
    #define ADC1RH_ADR9_MASK            2
    #define ADC1RH_ADR_8_MASK           3
    #define ADC1RH_ADR_8_BITNUM         0
    

    /*** ADC1RL - ADC10 Result Data Right Justified Low; 0x00000013 ***/
    union {
      byte Byte;
      struct {
        byte ADR0        :1;                                       /* ADC10 Result Data Bit 0 */
        byte ADR1        :1;                                       /* ADC10 Result Data Bit 1 */
        byte ADR2        :1;                                       /* ADC10 Result Data Bit 2 */
        byte ADR3        :1;                                       /* ADC10 Result Data Bit 3 */
        byte ADR4        :1;                                       /* ADC10 Result Data Bit 4 */
        byte ADR5        :1;                                       /* ADC10 Result Data Bit 5 */
        byte ADR6        :1;                                       /* ADC10 Result Data Bit 6 */
        byte ADR7        :1;                                       /* ADC10 Result Data Bit 7 */
      } Bits;
    } ADC1RLSTR;
    #define ADC1RL                      _ADC1R.Overlap_STR.ADC1RLSTR.Byte
    #define ADC1RL_ADR0                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR0
    #define ADC1RL_ADR1                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR1
    #define ADC1RL_ADR2                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR2
    #define ADC1RL_ADR3                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR3
    #define ADC1RL_ADR4                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR4
    #define ADC1RL_ADR5                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR5
    #define ADC1RL_ADR6                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR6
    #define ADC1RL_ADR7                 _ADC1R.Overlap_STR.ADC1RLSTR.Bits.ADR7
    
    #define ADC1RL_ADR0_MASK            1
    #define ADC1RL_ADR1_MASK            2
    #define ADC1RL_ADR2_MASK            4
    #define ADC1RL_ADR3_MASK            8
    #define ADC1RL_ADR4_MASK            16
    #define ADC1RL_ADR5_MASK            32
    #define ADC1RL_ADR6_MASK            64
    #define ADC1RL_ADR7_MASK            128
    
  } Overlap_STR;

} ADC1RSTR;
extern volatile ADC1RSTR _ADC1R @0x00000012;
#define ADC1R                           _ADC1R.Word


/*** ADC1CV - Compare Value Register; 0x00000014 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADC1CVH - Compare Value Register High; 0x00000014 ***/
    union {
      byte Byte;
      struct {
        byte ADCV8       :1;                                       /* Compare Function Value 8 */
        byte ADCV9       :1;                                       /* Compare Function Value 9 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpADCV_8 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADC1CVHSTR;
    #define ADC1CVH                     _ADC1CV.Overlap_STR.ADC1CVHSTR.Byte
    #define ADC1CVH_ADCV8               _ADC1CV.Overlap_STR.ADC1CVHSTR.Bits.ADCV8
    #define ADC1CVH_ADCV9               _ADC1CV.Overlap_STR.ADC1CVHSTR.Bits.ADCV9
    #define ADC1CVH_ADCV_8              _ADC1CV.Overlap_STR.ADC1CVHSTR.MergedBits.grpADCV_8
    #define ADC1CVH_ADCV                ADC1CVH_ADCV_8
    
    #define ADC1CVH_ADCV8_MASK          1
    #define ADC1CVH_ADCV9_MASK          2
    #define ADC1CVH_ADCV_8_MASK         3
    #define ADC1CVH_ADCV_8_BITNUM       0
    

    /*** ADC1CVL - Compare Value Register Low; 0x00000015 ***/
    union {
      byte Byte;
      struct {
        byte ADCV0       :1;                                       /* Compare Function Value 0 */
        byte ADCV1       :1;                                       /* Compare Function Value 1 */
        byte ADCV2       :1;                                       /* Compare Function Value 2 */
        byte ADCV3       :1;                                       /* Compare Function Value 3 */
        byte ADCV4       :1;                                       /* Compare Function Value 4 */
        byte ADCV5       :1;                                       /* Compare Function Value 5 */
        byte ADCV6       :1;                                       /* Compare Function Value 6 */
        byte ADCV7       :1;                                       /* Compare Function Value 7 */
      } Bits;
    } ADC1CVLSTR;
    #define ADC1CVL                     _ADC1CV.Overlap_STR.ADC1CVLSTR.Byte
    #define ADC1CVL_ADCV0               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV0
    #define ADC1CVL_ADCV1               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV1
    #define ADC1CVL_ADCV2               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV2
    #define ADC1CVL_ADCV3               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV3
    #define ADC1CVL_ADCV4               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV4
    #define ADC1CVL_ADCV5               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV5
    #define ADC1CVL_ADCV6               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV6
    #define ADC1CVL_ADCV7               _ADC1CV.Overlap_STR.ADC1CVLSTR.Bits.ADCV7
    
    #define ADC1CVL_ADCV0_MASK          1
    #define ADC1CVL_ADCV1_MASK          2
    #define ADC1CVL_ADCV2_MASK          4
    #define ADC1CVL_ADCV3_MASK          8
    #define ADC1CVL_ADCV4_MASK          16
    #define ADC1CVL_ADCV5_MASK          32
    #define ADC1CVL_ADCV6_MASK          64
    #define ADC1CVL_ADCV7_MASK          128
    
  } Overlap_STR;

} ADC1CVSTR;
extern volatile ADC1CVSTR _ADC1CV @0x00000014;
#define ADC1CV                          _ADC1CV.Word


/*** ADC1CFG - Configuration Register; 0x00000016 ***/
typedef union {
  byte Byte;
  struct {
    byte ADICLK0     :1;                                       /* Input Clock Select Bit 0 */
    byte ADICLK1     :1;                                       /* Input Clock Select Bit 1 */
    byte MODE0       :1;                                       /* Conversion Mode Selection Bit 0 */
    byte MODE1       :1;                                       /* Conversion Mode Selection Bit 1 */
    byte ADLSMP      :1;                                       /* Long Sample Time Configuration */
    byte ADIV0       :1;                                       /* Clock Divide Select Bit 0 */
    byte ADIV1       :1;                                       /* Clock Divide Select Bit 1 */
    byte ADLPC       :1;                                       /* Low Power Configuration */
  } Bits;
  struct {
    byte grpADICLK :2;
    byte grpMODE :2;
    byte         :1;
    byte grpADIV :2;
    byte         :1;
  } MergedBits;
} ADC1CFGSTR;
extern volatile ADC1CFGSTR _ADC1CFG @0x00000016;
#define ADC1CFG                         _ADC1CFG.Byte
#define ADC1CFG_ADICLK0                 _ADC1CFG.Bits.ADICLK0
#define ADC1CFG_ADICLK1                 _ADC1CFG.Bits.ADICLK1
#define ADC1CFG_MODE0                   _ADC1CFG.Bits.MODE0
#define ADC1CFG_MODE1                   _ADC1CFG.Bits.MODE1
#define ADC1CFG_ADLSMP                  _ADC1CFG.Bits.ADLSMP
#define ADC1CFG_ADIV0                   _ADC1CFG.Bits.ADIV0
#define ADC1CFG_ADIV1                   _ADC1CFG.Bits.ADIV1
#define ADC1CFG_ADLPC                   _ADC1CFG.Bits.ADLPC
#define ADC1CFG_ADICLK                  _ADC1CFG.MergedBits.grpADICLK
#define ADC1CFG_MODE                    _ADC1CFG.MergedBits.grpMODE
#define ADC1CFG_ADIV                    _ADC1CFG.MergedBits.grpADIV

#define ADC1CFG_ADICLK0_MASK            1
#define ADC1CFG_ADICLK1_MASK            2
#define ADC1CFG_MODE0_MASK              4
#define ADC1CFG_MODE1_MASK              8
#define ADC1CFG_ADLSMP_MASK             16
#define ADC1CFG_ADIV0_MASK              32
#define ADC1CFG_ADIV1_MASK              64
#define ADC1CFG_ADLPC_MASK              128
#define ADC1CFG_ADICLK_MASK             3
#define ADC1CFG_ADICLK_BITNUM           0
#define ADC1CFG_MODE_MASK               12
#define ADC1CFG_MODE_BITNUM             2
#define ADC1CFG_ADIV_MASK               96
#define ADC1CFG_ADIV_BITNUM             5


/*** APCTL1 - ADC10 Pin Control 1 Register; 0x00000017 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC0       :1;                                       /* ADC10 Pin Control 0 */
    byte ADPC1       :1;                                       /* ADC10 Pin Control 1 */
    byte ADPC2       :1;                                       /* ADC10 Pin Control 2 */
    byte ADPC3       :1;                                       /* ADC10 Pin Control 3 */
    byte ADPC4       :1;                                       /* ADC10 Pin Control 4 */
    byte ADPC5       :1;                                       /* ADC10 Pin Control 5 */
    byte ADPC6       :1;                                       /* ADC10 Pin Control 6 */
    byte ADPC7       :1;                                       /* ADC10 Pin Control 7 */
  } Bits;
} APCTL1STR;
extern volatile APCTL1STR _APCTL1 @0x00000017;
#define APCTL1                          _APCTL1.Byte
#define APCTL1_ADPC0                    _APCTL1.Bits.ADPC0
#define APCTL1_ADPC1                    _APCTL1.Bits.ADPC1
#define APCTL1_ADPC2                    _APCTL1.Bits.ADPC2
#define APCTL1_ADPC3                    _APCTL1.Bits.ADPC3
#define APCTL1_ADPC4                    _APCTL1.Bits.ADPC4
#define APCTL1_ADPC5                    _APCTL1.Bits.ADPC5
#define APCTL1_ADPC6                    _APCTL1.Bits.ADPC6
#define APCTL1_ADPC7                    _APCTL1.Bits.ADPC7

#define APCTL1_ADPC0_MASK               1
#define APCTL1_ADPC1_MASK               2
#define APCTL1_ADPC2_MASK               4
#define APCTL1_ADPC3_MASK               8
#define APCTL1_ADPC4_MASK               16
#define APCTL1_ADPC5_MASK               32
#define APCTL1_ADPC6_MASK               64
#define APCTL1_ADPC7_MASK               128


/*** APCTL2 - ADC10 Pin Control 2 Register; 0x00000018 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC8       :1;                                       /* ADC10 Pin Control 8 */
    byte ADPC9       :1;                                       /* ADC10 Pin Control 9 */
    byte ADPC10      :1;                                       /* ADC10 Pin Control 10 */
    byte ADPC11      :1;                                       /* ADC10 Pin Control 11 */
    byte ADPC12      :1;                                       /* ADC10 Pin Control 12 */
    byte ADPC13      :1;                                       /* ADC10 Pin Control 13 */
    byte ADPC14      :1;                                       /* ADC10 Pin Control 14 */
    byte ADPC15      :1;                                       /* ADC10 Pin Control 15 */
  } Bits;
} APCTL2STR;
extern volatile APCTL2STR _APCTL2 @0x00000018;
#define APCTL2                          _APCTL2.Byte
#define APCTL2_ADPC8                    _APCTL2.Bits.ADPC8
#define APCTL2_ADPC9                    _APCTL2.Bits.ADPC9
#define APCTL2_ADPC10                   _APCTL2.Bits.ADPC10
#define APCTL2_ADPC11                   _APCTL2.Bits.ADPC11
#define APCTL2_ADPC12                   _APCTL2.Bits.ADPC12
#define APCTL2_ADPC13                   _APCTL2.Bits.ADPC13
#define APCTL2_ADPC14                   _APCTL2.Bits.ADPC14
#define APCTL2_ADPC15                   _APCTL2.Bits.ADPC15

#define APCTL2_ADPC8_MASK               1
#define APCTL2_ADPC9_MASK               2
#define APCTL2_ADPC10_MASK              4
#define APCTL2_ADPC11_MASK              8
#define APCTL2_ADPC12_MASK              16
#define APCTL2_ADPC13_MASK              32
#define APCTL2_ADPC14_MASK              64
#define APCTL2_ADPC15_MASK              128


/*** APCTL3 - ADC10 Pin Control 3 Register; 0x00000019 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC16      :1;                                       /* ADC10 Pin Control 16 */
    byte ADPC17      :1;                                       /* ADC10 Pin Control 17 */
    byte ADPC18      :1;                                       /* ADC10 Pin Control 18 */
    byte ADPC19      :1;                                       /* ADC10 Pin Control 19 */
    byte ADPC20      :1;                                       /* ADC10 Pin Control 20 */
    byte ADPC21      :1;                                       /* ADC10 Pin Control 21 */
    byte ADPC22      :1;                                       /* ADC10 Pin Control 22 */
    byte ADPC23      :1;                                       /* ADC10 Pin Control 23 */
  } Bits;
} APCTL3STR;
extern volatile APCTL3STR _APCTL3 @0x00000019;
#define APCTL3                          _APCTL3.Byte
#define APCTL3_ADPC16                   _APCTL3.Bits.ADPC16
#define APCTL3_ADPC17                   _APCTL3.Bits.ADPC17
#define APCTL3_ADPC18                   _APCTL3.Bits.ADPC18
#define APCTL3_ADPC19                   _APCTL3.Bits.ADPC19
#define APCTL3_ADPC20                   _APCTL3.Bits.ADPC20
#define APCTL3_ADPC21                   _APCTL3.Bits.ADPC21
#define APCTL3_ADPC22                   _APCTL3.Bits.ADPC22
#define APCTL3_ADPC23                   _APCTL3.Bits.ADPC23

#define APCTL3_ADPC16_MASK              1
#define APCTL3_ADPC17_MASK              2
#define APCTL3_ADPC18_MASK              4
#define APCTL3_ADPC19_MASK              8
#define APCTL3_ADPC20_MASK              16
#define APCTL3_ADPC21_MASK              32
#define APCTL3_ADPC22_MASK              64
#define APCTL3_ADPC23_MASK              128


/*** IRQSC - Interrupt Request Status and Control Register; 0x0000001C ***/
typedef union {
  byte Byte;
  struct {
    byte IRQMOD      :1;                                       /* IRQ Detection Mode */
    byte IRQIE       :1;                                       /* IRQ Interrupt Enable */
    byte IRQACK      :1;                                       /* IRQ Acknowledge */
    byte IRQF        :1;                                       /* IRQ Flag */
    byte IRQPE       :1;                                       /* IRQ Pin Enable */
    byte IRQEDG      :1;                                       /* Interrupt Request (IRQ) Edge Select */
    byte             :1; 
    byte             :1; 
  } Bits;
} IRQSCSTR;
extern volatile IRQSCSTR _IRQSC @0x0000001C;
#define IRQSC                           _IRQSC.Byte
#define IRQSC_IRQMOD                    _IRQSC.Bits.IRQMOD
#define IRQSC_IRQIE                     _IRQSC.Bits.IRQIE
#define IRQSC_IRQACK                    _IRQSC.Bits.IRQACK
#define IRQSC_IRQF                      _IRQSC.Bits.IRQF
#define IRQSC_IRQPE                     _IRQSC.Bits.IRQPE
#define IRQSC_IRQEDG                    _IRQSC.Bits.IRQEDG

#define IRQSC_IRQMOD_MASK               1
#define IRQSC_IRQIE_MASK                2
#define IRQSC_IRQACK_MASK               4
#define IRQSC_IRQF_MASK                 8
#define IRQSC_IRQPE_MASK                16
#define IRQSC_IRQEDG_MASK               32


/*** KBI1SC - KBI1 Status and Control; 0x0000001E ***/
typedef union {
  byte Byte;
  struct {
    byte KBIMOD      :1;                                       /* Keyboard Detection Mode */
    byte KBIE        :1;                                       /* Keyboard Interrupt Enable */
    byte KBACK       :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KBF         :1;                                       /* Keyboard Interrupt Flag */
    byte KBEDG4      :1;                                       /* Keyboard Edge Select for Port A Bit 4 */
    byte KBEDG5      :1;                                       /* Keyboard Edge Select for Port A Bit 5 */
    byte KBEDG6      :1;                                       /* Keyboard Edge Select for Port A Bit 6 */
    byte KBEDG7      :1;                                       /* Keyboard Edge Select for Port A Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKBEDG_4 :4;
  } MergedBits;
} KBI1SCSTR;
extern volatile KBI1SCSTR _KBI1SC @0x0000001E;
#define KBI1SC                          _KBI1SC.Byte
#define KBI1SC_KBIMOD                   _KBI1SC.Bits.KBIMOD
#define KBI1SC_KBIE                     _KBI1SC.Bits.KBIE
#define KBI1SC_KBACK                    _KBI1SC.Bits.KBACK
#define KBI1SC_KBF                      _KBI1SC.Bits.KBF
#define KBI1SC_KBEDG4                   _KBI1SC.Bits.KBEDG4
#define KBI1SC_KBEDG5                   _KBI1SC.Bits.KBEDG5
#define KBI1SC_KBEDG6                   _KBI1SC.Bits.KBEDG6
#define KBI1SC_KBEDG7                   _KBI1SC.Bits.KBEDG7
#define KBI1SC_KBEDG_4                  _KBI1SC.MergedBits.grpKBEDG_4
#define KBI1SC_KBEDG                    KBI1SC_KBEDG_4

#define KBI1SC_KBIMOD_MASK              1
#define KBI1SC_KBIE_MASK                2
#define KBI1SC_KBACK_MASK               4
#define KBI1SC_KBF_MASK                 8
#define KBI1SC_KBEDG4_MASK              16
#define KBI1SC_KBEDG5_MASK              32
#define KBI1SC_KBEDG6_MASK              64
#define KBI1SC_KBEDG7_MASK              128
#define KBI1SC_KBEDG_4_MASK             240
#define KBI1SC_KBEDG_4_BITNUM           4


/*** KBI1PE - KBI1 Pin Enable Register; 0x0000001F ***/
typedef union {
  byte Byte;
  struct {
    byte KBIPE0      :1;                                       /* Keyboard Pin Enable for Port A Bit 0 */
    byte KBIPE1      :1;                                       /* Keyboard Pin Enable for Port A Bit 1 */
    byte KBIPE2      :1;                                       /* Keyboard Pin Enable for Port A Bit 2 */
    byte KBIPE3      :1;                                       /* Keyboard Pin Enable for Port A Bit 3 */
    byte KBIPE4      :1;                                       /* Keyboard Pin Enable for Port A Bit 4 */
    byte KBIPE5      :1;                                       /* Keyboard Pin Enable for Port A Bit 5 */
    byte KBIPE6      :1;                                       /* Keyboard Pin Enable for Port A Bit 6 */
    byte KBIPE7      :1;                                       /* Keyboard Pin Enable for Port A Bit 7 */
  } Bits;
} KBI1PESTR;
extern volatile KBI1PESTR _KBI1PE @0x0000001F;
#define KBI1PE                          _KBI1PE.Byte
#define KBI1PE_KBIPE0                   _KBI1PE.Bits.KBIPE0
#define KBI1PE_KBIPE1                   _KBI1PE.Bits.KBIPE1
#define KBI1PE_KBIPE2                   _KBI1PE.Bits.KBIPE2
#define KBI1PE_KBIPE3                   _KBI1PE.Bits.KBIPE3
#define KBI1PE_KBIPE4                   _KBI1PE.Bits.KBIPE4
#define KBI1PE_KBIPE5                   _KBI1PE.Bits.KBIPE5
#define KBI1PE_KBIPE6                   _KBI1PE.Bits.KBIPE6
#define KBI1PE_KBIPE7                   _KBI1PE.Bits.KBIPE7

#define KBI1PE_KBIPE0_MASK              1
#define KBI1PE_KBIPE1_MASK              2
#define KBI1PE_KBIPE2_MASK              4
#define KBI1PE_KBIPE3_MASK              8
#define KBI1PE_KBIPE4_MASK              16
#define KBI1PE_KBIPE5_MASK              32
#define KBI1PE_KBIPE6_MASK              64
#define KBI1PE_KBIPE7_MASK              128


/*** TPM1SC - TPM 1 Status and Control Register; 0x00000020 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1SCSTR;
extern volatile TPM1SCSTR _TPM1SC @0x00000020;
#define TPM1SC                          _TPM1SC.Byte
#define TPM1SC_PS0                      _TPM1SC.Bits.PS0
#define TPM1SC_PS1                      _TPM1SC.Bits.PS1
#define TPM1SC_PS2                      _TPM1SC.Bits.PS2
#define TPM1SC_CLKSA                    _TPM1SC.Bits.CLKSA
#define TPM1SC_CLKSB                    _TPM1SC.Bits.CLKSB
#define TPM1SC_CPWMS                    _TPM1SC.Bits.CPWMS
#define TPM1SC_TOIE                     _TPM1SC.Bits.TOIE
#define TPM1SC_TOF                      _TPM1SC.Bits.TOF
#define TPM1SC_PS                       _TPM1SC.MergedBits.grpPS
#define TPM1SC_CLKSx                    _TPM1SC.MergedBits.grpCLKSx

#define TPM1SC_PS0_MASK                 1
#define TPM1SC_PS1_MASK                 2
#define TPM1SC_PS2_MASK                 4
#define TPM1SC_CLKSA_MASK               8
#define TPM1SC_CLKSB_MASK               16
#define TPM1SC_CPWMS_MASK               32
#define TPM1SC_TOIE_MASK                64
#define TPM1SC_TOF_MASK                 128
#define TPM1SC_PS_MASK                  7
#define TPM1SC_PS_BITNUM                0
#define TPM1SC_CLKSx_MASK               24
#define TPM1SC_CLKSx_BITNUM             3


/*** TPM1CNT - TPM 1 Counter Register; 0x00000021 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1CNTH - TPM 1 Counter Register High; 0x00000021 ***/
    union {
      byte Byte;
    } TPM1CNTHSTR;
    #define TPM1CNTH                    _TPM1CNT.Overlap_STR.TPM1CNTHSTR.Byte
    

    /*** TPM1CNTL - TPM 1 Counter Register Low; 0x00000022 ***/
    union {
      byte Byte;
    } TPM1CNTLSTR;
    #define TPM1CNTL                    _TPM1CNT.Overlap_STR.TPM1CNTLSTR.Byte
    
  } Overlap_STR;

} TPM1CNTSTR;
extern volatile TPM1CNTSTR _TPM1CNT @0x00000021;
#define TPM1CNT                         _TPM1CNT.Word


/*** TPM1MOD - TPM 1 Timer Counter Modulo Register; 0x00000023 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1MODH - TPM 1 Timer Counter Modulo Register High; 0x00000023 ***/
    union {
      byte Byte;
    } TPM1MODHSTR;
    #define TPM1MODH                    _TPM1MOD.Overlap_STR.TPM1MODHSTR.Byte
    

    /*** TPM1MODL - TPM 1 Timer Counter Modulo Register Low; 0x00000024 ***/
    union {
      byte Byte;
    } TPM1MODLSTR;
    #define TPM1MODL                    _TPM1MOD.Overlap_STR.TPM1MODLSTR.Byte
    
  } Overlap_STR;

} TPM1MODSTR;
extern volatile TPM1MODSTR _TPM1MOD @0x00000023;
#define TPM1MOD                         _TPM1MOD.Word


/*** TPM1C0SC - TPM 1 Timer Channel 0 Status and Control Register; 0x00000025 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C0SCSTR;
extern volatile TPM1C0SCSTR _TPM1C0SC @0x00000025;
#define TPM1C0SC                        _TPM1C0SC.Byte
#define TPM1C0SC_ELS0A                  _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELS0B                  _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MS0A                   _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MS0B                   _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CH0IE                  _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CH0F                   _TPM1C0SC.Bits.CH0F
#define TPM1C0SC_ELS0x                  _TPM1C0SC.MergedBits.grpELS0x
#define TPM1C0SC_MS0x                   _TPM1C0SC.MergedBits.grpMS0x

#define TPM1C0SC_ELS0A_MASK             4
#define TPM1C0SC_ELS0B_MASK             8
#define TPM1C0SC_MS0A_MASK              16
#define TPM1C0SC_MS0B_MASK              32
#define TPM1C0SC_CH0IE_MASK             64
#define TPM1C0SC_CH0F_MASK              128
#define TPM1C0SC_ELS0x_MASK             12
#define TPM1C0SC_ELS0x_BITNUM           2
#define TPM1C0SC_MS0x_MASK              48
#define TPM1C0SC_MS0x_BITNUM            4


/*** TPM1C0V - TPM 1 Timer Channel 0 Value Register; 0x00000026 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C0VH - TPM 1 Timer Channel 0 Value Register High; 0x00000026 ***/
    union {
      byte Byte;
    } TPM1C0VHSTR;
    #define TPM1C0VH                    _TPM1C0V.Overlap_STR.TPM1C0VHSTR.Byte
    

    /*** TPM1C0VL - TPM 1 Timer Channel 0 Value Register Low; 0x00000027 ***/
    union {
      byte Byte;
    } TPM1C0VLSTR;
    #define TPM1C0VL                    _TPM1C0V.Overlap_STR.TPM1C0VLSTR.Byte
    
  } Overlap_STR;

} TPM1C0VSTR;
extern volatile TPM1C0VSTR _TPM1C0V @0x00000026;
#define TPM1C0V                         _TPM1C0V.Word


/*** TPM1C1SC - TPM 1 Timer Channel 1 Status and Control Register; 0x00000028 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C1SCSTR;
extern volatile TPM1C1SCSTR _TPM1C1SC @0x00000028;
#define TPM1C1SC                        _TPM1C1SC.Byte
#define TPM1C1SC_ELS1A                  _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELS1B                  _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MS1A                   _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MS1B                   _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CH1IE                  _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CH1F                   _TPM1C1SC.Bits.CH1F
#define TPM1C1SC_ELS1x                  _TPM1C1SC.MergedBits.grpELS1x
#define TPM1C1SC_MS1x                   _TPM1C1SC.MergedBits.grpMS1x

#define TPM1C1SC_ELS1A_MASK             4
#define TPM1C1SC_ELS1B_MASK             8
#define TPM1C1SC_MS1A_MASK              16
#define TPM1C1SC_MS1B_MASK              32
#define TPM1C1SC_CH1IE_MASK             64
#define TPM1C1SC_CH1F_MASK              128
#define TPM1C1SC_ELS1x_MASK             12
#define TPM1C1SC_ELS1x_BITNUM           2
#define TPM1C1SC_MS1x_MASK              48
#define TPM1C1SC_MS1x_BITNUM            4


/*** TPM1C1V - TPM 1 Timer Channel 1 Value Register; 0x00000029 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C1VH - TPM 1 Timer Channel 1 Value Register High; 0x00000029 ***/
    union {
      byte Byte;
    } TPM1C1VHSTR;
    #define TPM1C1VH                    _TPM1C1V.Overlap_STR.TPM1C1VHSTR.Byte
    

    /*** TPM1C1VL - TPM 1 Timer Channel 1 Value Register Low; 0x0000002A ***/
    union {
      byte Byte;
    } TPM1C1VLSTR;
    #define TPM1C1VL                    _TPM1C1V.Overlap_STR.TPM1C1VLSTR.Byte
    
  } Overlap_STR;

} TPM1C1VSTR;
extern volatile TPM1C1VSTR _TPM1C1V @0x00000029;
#define TPM1C1V                         _TPM1C1V.Word


/*** TPM1C2SC - TPM 1 Timer Channel 2 Status and Control Register; 0x0000002B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C2SCSTR;
extern volatile TPM1C2SCSTR _TPM1C2SC @0x0000002B;
#define TPM1C2SC                        _TPM1C2SC.Byte
#define TPM1C2SC_ELS2A                  _TPM1C2SC.Bits.ELS2A
#define TPM1C2SC_ELS2B                  _TPM1C2SC.Bits.ELS2B
#define TPM1C2SC_MS2A                   _TPM1C2SC.Bits.MS2A
#define TPM1C2SC_MS2B                   _TPM1C2SC.Bits.MS2B
#define TPM1C2SC_CH2IE                  _TPM1C2SC.Bits.CH2IE
#define TPM1C2SC_CH2F                   _TPM1C2SC.Bits.CH2F
#define TPM1C2SC_ELS2x                  _TPM1C2SC.MergedBits.grpELS2x
#define TPM1C2SC_MS2x                   _TPM1C2SC.MergedBits.grpMS2x

#define TPM1C2SC_ELS2A_MASK             4
#define TPM1C2SC_ELS2B_MASK             8
#define TPM1C2SC_MS2A_MASK              16
#define TPM1C2SC_MS2B_MASK              32
#define TPM1C2SC_CH2IE_MASK             64
#define TPM1C2SC_CH2F_MASK              128
#define TPM1C2SC_ELS2x_MASK             12
#define TPM1C2SC_ELS2x_BITNUM           2
#define TPM1C2SC_MS2x_MASK              48
#define TPM1C2SC_MS2x_BITNUM            4


/*** TPM1C2V - TPM 1 Timer Channel 2 Value Register; 0x0000002C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C2VH - TPM 1 Timer Channel 2 Value Register High; 0x0000002C ***/
    union {
      byte Byte;
    } TPM1C2VHSTR;
    #define TPM1C2VH                    _TPM1C2V.Overlap_STR.TPM1C2VHSTR.Byte
    

    /*** TPM1C2VL - TPM 1 Timer Channel 2 Value Register Low; 0x0000002D ***/
    union {
      byte Byte;
    } TPM1C2VLSTR;
    #define TPM1C2VL                    _TPM1C2V.Overlap_STR.TPM1C2VLSTR.Byte
    
  } Overlap_STR;

} TPM1C2VSTR;
extern volatile TPM1C2VSTR _TPM1C2V @0x0000002C;
#define TPM1C2V                         _TPM1C2V.Word


/*** TPM1C3SC - TPM 1 Timer Channel 3 Status and Control Register; 0x0000002E ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS3A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS3B       :1;                                       /* Edge/Level Select Bit B */
    byte MS3A        :1;                                       /* Mode Select A for TPM Channel 3 */
    byte MS3B        :1;                                       /* Mode Select B for TPM Channel 3 */
    byte CH3IE       :1;                                       /* Channel 3 Interrupt Enable */
    byte CH3F        :1;                                       /* Channel 3 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS3x :2;
    byte grpMS3x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C3SCSTR;
extern volatile TPM1C3SCSTR _TPM1C3SC @0x0000002E;
#define TPM1C3SC                        _TPM1C3SC.Byte
#define TPM1C3SC_ELS3A                  _TPM1C3SC.Bits.ELS3A
#define TPM1C3SC_ELS3B                  _TPM1C3SC.Bits.ELS3B
#define TPM1C3SC_MS3A                   _TPM1C3SC.Bits.MS3A
#define TPM1C3SC_MS3B                   _TPM1C3SC.Bits.MS3B
#define TPM1C3SC_CH3IE                  _TPM1C3SC.Bits.CH3IE
#define TPM1C3SC_CH3F                   _TPM1C3SC.Bits.CH3F
#define TPM1C3SC_ELS3x                  _TPM1C3SC.MergedBits.grpELS3x
#define TPM1C3SC_MS3x                   _TPM1C3SC.MergedBits.grpMS3x

#define TPM1C3SC_ELS3A_MASK             4
#define TPM1C3SC_ELS3B_MASK             8
#define TPM1C3SC_MS3A_MASK              16
#define TPM1C3SC_MS3B_MASK              32
#define TPM1C3SC_CH3IE_MASK             64
#define TPM1C3SC_CH3F_MASK              128
#define TPM1C3SC_ELS3x_MASK             12
#define TPM1C3SC_ELS3x_BITNUM           2
#define TPM1C3SC_MS3x_MASK              48
#define TPM1C3SC_MS3x_BITNUM            4


/*** TPM1C3V - TPM 1 Timer Channel 3 Value Register; 0x0000002F ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C3VH - TPM 1 Timer Channel 3 Value Register High; 0x0000002F ***/
    union {
      byte Byte;
    } TPM1C3VHSTR;
    #define TPM1C3VH                    _TPM1C3V.Overlap_STR.TPM1C3VHSTR.Byte
    

    /*** TPM1C3VL - TPM 1 Timer Channel 3 Value Register Low; 0x00000030 ***/
    union {
      byte Byte;
    } TPM1C3VLSTR;
    #define TPM1C3VL                    _TPM1C3V.Overlap_STR.TPM1C3VLSTR.Byte
    
  } Overlap_STR;

} TPM1C3VSTR;
extern volatile TPM1C3VSTR _TPM1C3V @0x0000002F;
#define TPM1C3V                         _TPM1C3V.Word


/*** TPM1C4SC - TPM 1 Timer Channel 4 Status and Control Register; 0x00000031 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS4A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS4B       :1;                                       /* Edge/Level Select Bit B */
    byte MS4A        :1;                                       /* Mode Select A for TPM Channel 4 */
    byte MS4B        :1;                                       /* Mode Select B for TPM Channel 4 */
    byte CH4IE       :1;                                       /* Channel 4 Interrupt Enable */
    byte CH4F        :1;                                       /* Channel 4 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS4x :2;
    byte grpMS4x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C4SCSTR;
extern volatile TPM1C4SCSTR _TPM1C4SC @0x00000031;
#define TPM1C4SC                        _TPM1C4SC.Byte
#define TPM1C4SC_ELS4A                  _TPM1C4SC.Bits.ELS4A
#define TPM1C4SC_ELS4B                  _TPM1C4SC.Bits.ELS4B
#define TPM1C4SC_MS4A                   _TPM1C4SC.Bits.MS4A
#define TPM1C4SC_MS4B                   _TPM1C4SC.Bits.MS4B
#define TPM1C4SC_CH4IE                  _TPM1C4SC.Bits.CH4IE
#define TPM1C4SC_CH4F                   _TPM1C4SC.Bits.CH4F
#define TPM1C4SC_ELS4x                  _TPM1C4SC.MergedBits.grpELS4x
#define TPM1C4SC_MS4x                   _TPM1C4SC.MergedBits.grpMS4x

#define TPM1C4SC_ELS4A_MASK             4
#define TPM1C4SC_ELS4B_MASK             8
#define TPM1C4SC_MS4A_MASK              16
#define TPM1C4SC_MS4B_MASK              32
#define TPM1C4SC_CH4IE_MASK             64
#define TPM1C4SC_CH4F_MASK              128
#define TPM1C4SC_ELS4x_MASK             12
#define TPM1C4SC_ELS4x_BITNUM           2
#define TPM1C4SC_MS4x_MASK              48
#define TPM1C4SC_MS4x_BITNUM            4


/*** TPM1C4V - TPM 1 Timer Channel 4 Value Register; 0x00000032 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C4VH - TPM 1 Timer Channel 4 Value Register High; 0x00000032 ***/
    union {
      byte Byte;
    } TPM1C4VHSTR;
    #define TPM1C4VH                    _TPM1C4V.Overlap_STR.TPM1C4VHSTR.Byte
    

    /*** TPM1C4VL - TPM 1 Timer Channel 4 Value Register Low; 0x00000033 ***/
    union {
      byte Byte;
    } TPM1C4VLSTR;
    #define TPM1C4VL                    _TPM1C4V.Overlap_STR.TPM1C4VLSTR.Byte
    
  } Overlap_STR;

} TPM1C4VSTR;
extern volatile TPM1C4VSTR _TPM1C4V @0x00000032;
#define TPM1C4V                         _TPM1C4V.Word


/*** TPM1C5SC - TPM 1 Timer Channel 5 Status and Control Register; 0x00000034 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS5A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS5B       :1;                                       /* Edge/Level Select Bit B */
    byte MS5A        :1;                                       /* Mode Select A for TPM Channel 5 */
    byte MS5B        :1;                                       /* Mode Select B for TPM Channel 5 */
    byte CH5IE       :1;                                       /* Channel 5 Interrupt Enable */
    byte CH5F        :1;                                       /* Channel 5 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS5x :2;
    byte grpMS5x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C5SCSTR;
extern volatile TPM1C5SCSTR _TPM1C5SC @0x00000034;
#define TPM1C5SC                        _TPM1C5SC.Byte
#define TPM1C5SC_ELS5A                  _TPM1C5SC.Bits.ELS5A
#define TPM1C5SC_ELS5B                  _TPM1C5SC.Bits.ELS5B
#define TPM1C5SC_MS5A                   _TPM1C5SC.Bits.MS5A
#define TPM1C5SC_MS5B                   _TPM1C5SC.Bits.MS5B
#define TPM1C5SC_CH5IE                  _TPM1C5SC.Bits.CH5IE
#define TPM1C5SC_CH5F                   _TPM1C5SC.Bits.CH5F
#define TPM1C5SC_ELS5x                  _TPM1C5SC.MergedBits.grpELS5x
#define TPM1C5SC_MS5x                   _TPM1C5SC.MergedBits.grpMS5x

#define TPM1C5SC_ELS5A_MASK             4
#define TPM1C5SC_ELS5B_MASK             8
#define TPM1C5SC_MS5A_MASK              16
#define TPM1C5SC_MS5B_MASK              32
#define TPM1C5SC_CH5IE_MASK             64
#define TPM1C5SC_CH5F_MASK              128
#define TPM1C5SC_ELS5x_MASK             12
#define TPM1C5SC_ELS5x_BITNUM           2
#define TPM1C5SC_MS5x_MASK              48
#define TPM1C5SC_MS5x_BITNUM            4


/*** TPM1C5V - TPM 1 Timer Channel 5 Value Register; 0x00000035 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C5VH - TPM 1 Timer Channel 5 Value Register High; 0x00000035 ***/
    union {
      byte Byte;
    } TPM1C5VHSTR;
    #define TPM1C5VH                    _TPM1C5V.Overlap_STR.TPM1C5VHSTR.Byte
    

    /*** TPM1C5VL - TPM 1 Timer Channel 5 Value Register Low; 0x00000036 ***/
    union {
      byte Byte;
    } TPM1C5VLSTR;
    #define TPM1C5VL                    _TPM1C5V.Overlap_STR.TPM1C5VLSTR.Byte
    
  } Overlap_STR;

} TPM1C5VSTR;
extern volatile TPM1C5VSTR _TPM1C5V @0x00000035;
#define TPM1C5V                         _TPM1C5V.Word


/*** SCI1BD - SCI1 Baud Rate Register; 0x00000038 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI1BDH - SCI1 Baud Rate Register High; 0x00000038 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI1BDHSTR;
    #define SCI1BDH                     _SCI1BD.Overlap_STR.SCI1BDHSTR.Byte
    #define SCI1BDH_SBR8                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR8
    #define SCI1BDH_SBR9                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR9
    #define SCI1BDH_SBR10               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR10
    #define SCI1BDH_SBR11               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR11
    #define SCI1BDH_SBR12               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR12
    #define SCI1BDH_SBR_8               _SCI1BD.Overlap_STR.SCI1BDHSTR.MergedBits.grpSBR_8
    #define SCI1BDH_SBR                 SCI1BDH_SBR_8
    
    #define SCI1BDH_SBR8_MASK           1
    #define SCI1BDH_SBR9_MASK           2
    #define SCI1BDH_SBR10_MASK          4
    #define SCI1BDH_SBR11_MASK          8
    #define SCI1BDH_SBR12_MASK          16
    #define SCI1BDH_SBR_8_MASK          31
    #define SCI1BDH_SBR_8_BITNUM        0
    

    /*** SCI1BDL - SCI1 Baud Rate Register Low; 0x00000039 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI1BDLSTR;
    #define SCI1BDL                     _SCI1BD.Overlap_STR.SCI1BDLSTR.Byte
    #define SCI1BDL_SBR0                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR0
    #define SCI1BDL_SBR1                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR1
    #define SCI1BDL_SBR2                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR2
    #define SCI1BDL_SBR3                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR3
    #define SCI1BDL_SBR4                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR4
    #define SCI1BDL_SBR5                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR5
    #define SCI1BDL_SBR6                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR6
    #define SCI1BDL_SBR7                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR7
    
    #define SCI1BDL_SBR0_MASK           1
    #define SCI1BDL_SBR1_MASK           2
    #define SCI1BDL_SBR2_MASK           4
    #define SCI1BDL_SBR3_MASK           8
    #define SCI1BDL_SBR4_MASK           16
    #define SCI1BDL_SBR5_MASK           32
    #define SCI1BDL_SBR6_MASK           64
    #define SCI1BDL_SBR7_MASK           128
    
  } Overlap_STR;

} SCI1BDSTR;
extern volatile SCI1BDSTR _SCI1BD @0x00000038;
#define SCI1BD                          _SCI1BD.Word


/*** SCI1C1 - SCI1 Control Register 1; 0x0000003A ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI1C1STR;
extern volatile SCI1C1STR _SCI1C1 @0x0000003A;
#define SCI1C1                          _SCI1C1.Byte
#define SCI1C1_PT                       _SCI1C1.Bits.PT
#define SCI1C1_PE                       _SCI1C1.Bits.PE
#define SCI1C1_ILT                      _SCI1C1.Bits.ILT
#define SCI1C1_WAKE                     _SCI1C1.Bits.WAKE
#define SCI1C1_M                        _SCI1C1.Bits.M
#define SCI1C1_RSRC                     _SCI1C1.Bits.RSRC
#define SCI1C1_SCISWAI                  _SCI1C1.Bits.SCISWAI
#define SCI1C1_LOOPS                    _SCI1C1.Bits.LOOPS

#define SCI1C1_PT_MASK                  1
#define SCI1C1_PE_MASK                  2
#define SCI1C1_ILT_MASK                 4
#define SCI1C1_WAKE_MASK                8
#define SCI1C1_M_MASK                   16
#define SCI1C1_RSRC_MASK                32
#define SCI1C1_SCISWAI_MASK             64
#define SCI1C1_LOOPS_MASK               128


/*** SCI1C2 - SCI1 Control Register 2; 0x0000003B ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI1C2STR;
extern volatile SCI1C2STR _SCI1C2 @0x0000003B;
#define SCI1C2                          _SCI1C2.Byte
#define SCI1C2_SBK                      _SCI1C2.Bits.SBK
#define SCI1C2_RWU                      _SCI1C2.Bits.RWU
#define SCI1C2_RE                       _SCI1C2.Bits.RE
#define SCI1C2_TE                       _SCI1C2.Bits.TE
#define SCI1C2_ILIE                     _SCI1C2.Bits.ILIE
#define SCI1C2_RIE                      _SCI1C2.Bits.RIE
#define SCI1C2_TCIE                     _SCI1C2.Bits.TCIE
#define SCI1C2_TIE                      _SCI1C2.Bits.TIE

#define SCI1C2_SBK_MASK                 1
#define SCI1C2_RWU_MASK                 2
#define SCI1C2_RE_MASK                  4
#define SCI1C2_TE_MASK                  8
#define SCI1C2_ILIE_MASK                16
#define SCI1C2_RIE_MASK                 32
#define SCI1C2_TCIE_MASK                64
#define SCI1C2_TIE_MASK                 128


/*** SCI1S1 - SCI1 Status Register 1; 0x0000003C ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI1S1STR;
extern volatile SCI1S1STR _SCI1S1 @0x0000003C;
#define SCI1S1                          _SCI1S1.Byte
#define SCI1S1_PF                       _SCI1S1.Bits.PF
#define SCI1S1_FE                       _SCI1S1.Bits.FE
#define SCI1S1_NF                       _SCI1S1.Bits.NF
#define SCI1S1_OR                       _SCI1S1.Bits.OR
#define SCI1S1_IDLE                     _SCI1S1.Bits.IDLE
#define SCI1S1_RDRF                     _SCI1S1.Bits.RDRF
#define SCI1S1_TC                       _SCI1S1.Bits.TC
#define SCI1S1_TDRE                     _SCI1S1.Bits.TDRE

#define SCI1S1_PF_MASK                  1
#define SCI1S1_FE_MASK                  2
#define SCI1S1_NF_MASK                  4
#define SCI1S1_OR_MASK                  8
#define SCI1S1_IDLE_MASK                16
#define SCI1S1_RDRF_MASK                32
#define SCI1S1_TC_MASK                  64
#define SCI1S1_TDRE_MASK                128


/*** SCI1S2 - SCI1 Status Register 2; 0x0000003D ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte             :1; 
    byte BRK13       :1;                                       /* Break Character Length */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SCI1S2STR;
extern volatile SCI1S2STR _SCI1S2 @0x0000003D;
#define SCI1S2                          _SCI1S2.Byte
#define SCI1S2_RAF                      _SCI1S2.Bits.RAF
#define SCI1S2_BRK13                    _SCI1S2.Bits.BRK13

#define SCI1S2_RAF_MASK                 1
#define SCI1S2_BRK13_MASK               4


/*** SCI1C3 - SCI1 Control Register 3; 0x0000003E ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI1C3STR;
extern volatile SCI1C3STR _SCI1C3 @0x0000003E;
#define SCI1C3                          _SCI1C3.Byte
#define SCI1C3_PEIE                     _SCI1C3.Bits.PEIE
#define SCI1C3_FEIE                     _SCI1C3.Bits.FEIE
#define SCI1C3_NEIE                     _SCI1C3.Bits.NEIE
#define SCI1C3_ORIE                     _SCI1C3.Bits.ORIE
#define SCI1C3_TXINV                    _SCI1C3.Bits.TXINV
#define SCI1C3_TXDIR                    _SCI1C3.Bits.TXDIR
#define SCI1C3_T8                       _SCI1C3.Bits.T8
#define SCI1C3_R8                       _SCI1C3.Bits.R8

#define SCI1C3_PEIE_MASK                1
#define SCI1C3_FEIE_MASK                2
#define SCI1C3_NEIE_MASK                4
#define SCI1C3_ORIE_MASK                8
#define SCI1C3_TXINV_MASK               16
#define SCI1C3_TXDIR_MASK               32
#define SCI1C3_T8_MASK                  64
#define SCI1C3_R8_MASK                  128


/*** SCI1D - SCI1 Data Register; 0x0000003F ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI1DSTR;
extern volatile SCI1DSTR _SCI1D @0x0000003F;
#define SCI1D                           _SCI1D.Byte
#define SCI1D_R0_T0                     _SCI1D.Bits.R0_T0
#define SCI1D_R1_T1                     _SCI1D.Bits.R1_T1
#define SCI1D_R2_T2                     _SCI1D.Bits.R2_T2
#define SCI1D_R3_T3                     _SCI1D.Bits.R3_T3
#define SCI1D_R4_T4                     _SCI1D.Bits.R4_T4
#define SCI1D_R5_T5                     _SCI1D.Bits.R5_T5
#define SCI1D_R6_T6                     _SCI1D.Bits.R6_T6
#define SCI1D_R7_T7                     _SCI1D.Bits.R7_T7

#define SCI1D_R0_T0_MASK                1
#define SCI1D_R1_T1_MASK                2
#define SCI1D_R2_T2_MASK                4
#define SCI1D_R3_T3_MASK                8
#define SCI1D_R4_T4_MASK                16
#define SCI1D_R5_T5_MASK                32
#define SCI1D_R6_T6_MASK                64
#define SCI1D_R7_T7_MASK                128


/*** SCI2BD - SCI2 Baud Rate Register; 0x00000040 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI2BDH - SCI2 Baud Rate Register High; 0x00000040 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI2BDHSTR;
    #define SCI2BDH                     _SCI2BD.Overlap_STR.SCI2BDHSTR.Byte
    #define SCI2BDH_SBR8                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR8
    #define SCI2BDH_SBR9                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR9
    #define SCI2BDH_SBR10               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR10
    #define SCI2BDH_SBR11               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR11
    #define SCI2BDH_SBR12               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR12
    #define SCI2BDH_SBR_8               _SCI2BD.Overlap_STR.SCI2BDHSTR.MergedBits.grpSBR_8
    #define SCI2BDH_SBR                 SCI2BDH_SBR_8
    
    #define SCI2BDH_SBR8_MASK           1
    #define SCI2BDH_SBR9_MASK           2
    #define SCI2BDH_SBR10_MASK          4
    #define SCI2BDH_SBR11_MASK          8
    #define SCI2BDH_SBR12_MASK          16
    #define SCI2BDH_SBR_8_MASK          31
    #define SCI2BDH_SBR_8_BITNUM        0
    

    /*** SCI2BDL - SCI2 Baud Rate Register Low; 0x00000041 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI2BDLSTR;
    #define SCI2BDL                     _SCI2BD.Overlap_STR.SCI2BDLSTR.Byte
    #define SCI2BDL_SBR0                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR0
    #define SCI2BDL_SBR1                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR1
    #define SCI2BDL_SBR2                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR2
    #define SCI2BDL_SBR3                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR3
    #define SCI2BDL_SBR4                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR4
    #define SCI2BDL_SBR5                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR5
    #define SCI2BDL_SBR6                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR6
    #define SCI2BDL_SBR7                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR7
    
    #define SCI2BDL_SBR0_MASK           1
    #define SCI2BDL_SBR1_MASK           2
    #define SCI2BDL_SBR2_MASK           4
    #define SCI2BDL_SBR3_MASK           8
    #define SCI2BDL_SBR4_MASK           16
    #define SCI2BDL_SBR5_MASK           32
    #define SCI2BDL_SBR6_MASK           64
    #define SCI2BDL_SBR7_MASK           128
    
  } Overlap_STR;

} SCI2BDSTR;
extern volatile SCI2BDSTR _SCI2BD @0x00000040;
#define SCI2BD                          _SCI2BD.Word


/*** SCI2C1 - SCI1 Control Register 1; 0x00000042 ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI2C1STR;
extern volatile SCI2C1STR _SCI2C1 @0x00000042;
#define SCI2C1                          _SCI2C1.Byte
#define SCI2C1_PT                       _SCI2C1.Bits.PT
#define SCI2C1_PE                       _SCI2C1.Bits.PE
#define SCI2C1_ILT                      _SCI2C1.Bits.ILT
#define SCI2C1_WAKE                     _SCI2C1.Bits.WAKE
#define SCI2C1_M                        _SCI2C1.Bits.M
#define SCI2C1_RSRC                     _SCI2C1.Bits.RSRC
#define SCI2C1_SCISWAI                  _SCI2C1.Bits.SCISWAI
#define SCI2C1_LOOPS                    _SCI2C1.Bits.LOOPS

#define SCI2C1_PT_MASK                  1
#define SCI2C1_PE_MASK                  2
#define SCI2C1_ILT_MASK                 4
#define SCI2C1_WAKE_MASK                8
#define SCI2C1_M_MASK                   16
#define SCI2C1_RSRC_MASK                32
#define SCI2C1_SCISWAI_MASK             64
#define SCI2C1_LOOPS_MASK               128


/*** SCI2C2 - SCI2 Control Register 2; 0x00000043 ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI2C2STR;
extern volatile SCI2C2STR _SCI2C2 @0x00000043;
#define SCI2C2                          _SCI2C2.Byte
#define SCI2C2_SBK                      _SCI2C2.Bits.SBK
#define SCI2C2_RWU                      _SCI2C2.Bits.RWU
#define SCI2C2_RE                       _SCI2C2.Bits.RE
#define SCI2C2_TE                       _SCI2C2.Bits.TE
#define SCI2C2_ILIE                     _SCI2C2.Bits.ILIE
#define SCI2C2_RIE                      _SCI2C2.Bits.RIE
#define SCI2C2_TCIE                     _SCI2C2.Bits.TCIE
#define SCI2C2_TIE                      _SCI2C2.Bits.TIE

#define SCI2C2_SBK_MASK                 1
#define SCI2C2_RWU_MASK                 2
#define SCI2C2_RE_MASK                  4
#define SCI2C2_TE_MASK                  8
#define SCI2C2_ILIE_MASK                16
#define SCI2C2_RIE_MASK                 32
#define SCI2C2_TCIE_MASK                64
#define SCI2C2_TIE_MASK                 128


/*** SCI2S1 - SCI2 Status Register 1; 0x00000044 ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI2S1STR;
extern volatile SCI2S1STR _SCI2S1 @0x00000044;
#define SCI2S1                          _SCI2S1.Byte
#define SCI2S1_PF                       _SCI2S1.Bits.PF
#define SCI2S1_FE                       _SCI2S1.Bits.FE
#define SCI2S1_NF                       _SCI2S1.Bits.NF
#define SCI2S1_OR                       _SCI2S1.Bits.OR
#define SCI2S1_IDLE                     _SCI2S1.Bits.IDLE
#define SCI2S1_RDRF                     _SCI2S1.Bits.RDRF
#define SCI2S1_TC                       _SCI2S1.Bits.TC
#define SCI2S1_TDRE                     _SCI2S1.Bits.TDRE

#define SCI2S1_PF_MASK                  1
#define SCI2S1_FE_MASK                  2
#define SCI2S1_NF_MASK                  4
#define SCI2S1_OR_MASK                  8
#define SCI2S1_IDLE_MASK                16
#define SCI2S1_RDRF_MASK                32
#define SCI2S1_TC_MASK                  64
#define SCI2S1_TDRE_MASK                128


/*** SCI2S2 - SCI2 Status Register 2; 0x00000045 ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte             :1; 
    byte BRK13       :1;                                       /* Break Character Length */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SCI2S2STR;
extern volatile SCI2S2STR _SCI2S2 @0x00000045;
#define SCI2S2                          _SCI2S2.Byte
#define SCI2S2_RAF                      _SCI2S2.Bits.RAF
#define SCI2S2_BRK13                    _SCI2S2.Bits.BRK13

#define SCI2S2_RAF_MASK                 1
#define SCI2S2_BRK13_MASK               4


/*** SCI2C3 - SCI2 Control Register 3; 0x00000046 ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI2C3STR;
extern volatile SCI2C3STR _SCI2C3 @0x00000046;
#define SCI2C3                          _SCI2C3.Byte
#define SCI2C3_PEIE                     _SCI2C3.Bits.PEIE
#define SCI2C3_FEIE                     _SCI2C3.Bits.FEIE
#define SCI2C3_NEIE                     _SCI2C3.Bits.NEIE
#define SCI2C3_ORIE                     _SCI2C3.Bits.ORIE
#define SCI2C3_TXINV                    _SCI2C3.Bits.TXINV
#define SCI2C3_TXDIR                    _SCI2C3.Bits.TXDIR
#define SCI2C3_T8                       _SCI2C3.Bits.T8
#define SCI2C3_R8                       _SCI2C3.Bits.R8

#define SCI2C3_PEIE_MASK                1
#define SCI2C3_FEIE_MASK                2
#define SCI2C3_NEIE_MASK                4
#define SCI2C3_ORIE_MASK                8
#define SCI2C3_TXINV_MASK               16
#define SCI2C3_TXDIR_MASK               32
#define SCI2C3_T8_MASK                  64
#define SCI2C3_R8_MASK                  128


/*** SCI2D - SCI2 Data Register; 0x00000047 ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI2DSTR;
extern volatile SCI2DSTR _SCI2D @0x00000047;
#define SCI2D                           _SCI2D.Byte
#define SCI2D_R0_T0                     _SCI2D.Bits.R0_T0
#define SCI2D_R1_T1                     _SCI2D.Bits.R1_T1
#define SCI2D_R2_T2                     _SCI2D.Bits.R2_T2
#define SCI2D_R3_T3                     _SCI2D.Bits.R3_T3
#define SCI2D_R4_T4                     _SCI2D.Bits.R4_T4
#define SCI2D_R5_T5                     _SCI2D.Bits.R5_T5
#define SCI2D_R6_T6                     _SCI2D.Bits.R6_T6
#define SCI2D_R7_T7                     _SCI2D.Bits.R7_T7

#define SCI2D_R0_T0_MASK                1
#define SCI2D_R1_T1_MASK                2
#define SCI2D_R2_T2_MASK                4
#define SCI2D_R3_T3_MASK                8
#define SCI2D_R4_T4_MASK                16
#define SCI2D_R5_T5_MASK                32
#define SCI2D_R6_T6_MASK                64
#define SCI2D_R7_T7_MASK                128


/*** ICGC1 - ICG Control Register 1; 0x00000048 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte LOCD        :1;                                       /* Loss of Clock Disable */
    byte OSCSTEN     :1;                                       /* Enable Oscillator in Off Mode */
    byte CLKS0       :1;                                       /* Clock Mode Select Bit 0 */
    byte CLKS1       :1;                                       /* Clock Mode Select Bit 1 */
    byte REFS        :1;                                       /* External Reference Select */
    byte RANGE       :1;                                       /* Frequency Range Select */
    byte HGO         :1;                                       /* High Gain Oscillator Select */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpCLKS :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ICGC1STR;
extern volatile ICGC1STR _ICGC1 @0x00000048;
#define ICGC1                           _ICGC1.Byte
#define ICGC1_LOCD                      _ICGC1.Bits.LOCD
#define ICGC1_OSCSTEN                   _ICGC1.Bits.OSCSTEN
#define ICGC1_CLKS0                     _ICGC1.Bits.CLKS0
#define ICGC1_CLKS1                     _ICGC1.Bits.CLKS1
#define ICGC1_REFS                      _ICGC1.Bits.REFS
#define ICGC1_RANGE                     _ICGC1.Bits.RANGE
#define ICGC1_HGO                       _ICGC1.Bits.HGO
#define ICGC1_CLKS                      _ICGC1.MergedBits.grpCLKS

#define ICGC1_LOCD_MASK                 2
#define ICGC1_OSCSTEN_MASK              4
#define ICGC1_CLKS0_MASK                8
#define ICGC1_CLKS1_MASK                16
#define ICGC1_REFS_MASK                 32
#define ICGC1_RANGE_MASK                64
#define ICGC1_HGO_MASK                  128
#define ICGC1_CLKS_MASK                 24
#define ICGC1_CLKS_BITNUM               3


/*** ICGC2 - ICG Control Register 2; 0x00000049 ***/
typedef union {
  byte Byte;
  struct {
    byte RFD0        :1;                                       /* Reduced Frequency Divider Bit 0 */
    byte RFD1        :1;                                       /* Reduced Frequency Divider Bit 1 */
    byte RFD2        :1;                                       /* Reduced Frequency Divider Bit 2 */
    byte LOCRE       :1;                                       /* Loss of Clock Reset Enable */
    byte MFD0        :1;                                       /* Multiplication Factor Bit 0 */
    byte MFD1        :1;                                       /* Multiplication Factor Bit 1 */
    byte MFD2        :1;                                       /* Multiplication Factor Bit 2 */
    byte LOLRE       :1;                                       /* Loss of Lock Reset Enable */
  } Bits;
  struct {
    byte grpRFD  :3;
    byte         :1;
    byte grpMFD  :3;
    byte         :1;
  } MergedBits;
} ICGC2STR;
extern volatile ICGC2STR _ICGC2 @0x00000049;
#define ICGC2                           _ICGC2.Byte
#define ICGC2_RFD0                      _ICGC2.Bits.RFD0
#define ICGC2_RFD1                      _ICGC2.Bits.RFD1
#define ICGC2_RFD2                      _ICGC2.Bits.RFD2
#define ICGC2_LOCRE                     _ICGC2.Bits.LOCRE
#define ICGC2_MFD0                      _ICGC2.Bits.MFD0
#define ICGC2_MFD1                      _ICGC2.Bits.MFD1
#define ICGC2_MFD2                      _ICGC2.Bits.MFD2
#define ICGC2_LOLRE                     _ICGC2.Bits.LOLRE
#define ICGC2_RFD                       _ICGC2.MergedBits.grpRFD
#define ICGC2_MFD                       _ICGC2.MergedBits.grpMFD

#define ICGC2_RFD0_MASK                 1
#define ICGC2_RFD1_MASK                 2
#define ICGC2_RFD2_MASK                 4
#define ICGC2_LOCRE_MASK                8
#define ICGC2_MFD0_MASK                 16
#define ICGC2_MFD1_MASK                 32
#define ICGC2_MFD2_MASK                 64
#define ICGC2_LOLRE_MASK                128
#define ICGC2_RFD_MASK                  7
#define ICGC2_RFD_BITNUM                0
#define ICGC2_MFD_MASK                  112
#define ICGC2_MFD_BITNUM                4


/*** ICGS1 - ICG Status Register 1; 0x0000004A ***/
typedef union {
  byte Byte;
  struct {
    byte ICGIF       :1;                                       /* ICG Interrupt Flag */
    byte ERCS        :1;                                       /* External Reference Clock Status */
    byte LOCS        :1;                                       /* Loss Of Clock Status */
    byte LOCK        :1;                                       /* FLL Lock Status */
    byte LOLS        :1;                                       /* FLL Loss of Lock Status */
    byte REFST       :1;                                       /* Reference Clock Status */
    byte CLKST0      :1;                                       /* Clock Mode Status Bit 0 */
    byte CLKST1      :1;                                       /* Clock Mode Status Bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpCLKST :2;
  } MergedBits;
} ICGS1STR;
extern volatile ICGS1STR _ICGS1 @0x0000004A;
#define ICGS1                           _ICGS1.Byte
#define ICGS1_ICGIF                     _ICGS1.Bits.ICGIF
#define ICGS1_ERCS                      _ICGS1.Bits.ERCS
#define ICGS1_LOCS                      _ICGS1.Bits.LOCS
#define ICGS1_LOCK                      _ICGS1.Bits.LOCK
#define ICGS1_LOLS                      _ICGS1.Bits.LOLS
#define ICGS1_REFST                     _ICGS1.Bits.REFST
#define ICGS1_CLKST0                    _ICGS1.Bits.CLKST0
#define ICGS1_CLKST1                    _ICGS1.Bits.CLKST1
#define ICGS1_CLKST                     _ICGS1.MergedBits.grpCLKST

#define ICGS1_ICGIF_MASK                1
#define ICGS1_ERCS_MASK                 2
#define ICGS1_LOCS_MASK                 4
#define ICGS1_LOCK_MASK                 8
#define ICGS1_LOLS_MASK                 16
#define ICGS1_REFST_MASK                32
#define ICGS1_CLKST0_MASK               64
#define ICGS1_CLKST1_MASK               128
#define ICGS1_CLKST_MASK                192
#define ICGS1_CLKST_BITNUM              6


/*** ICGS2 - ICG Status Register 2; 0x0000004B ***/
typedef union {
  byte Byte;
  struct {
    byte DCOS        :1;                                       /* DCO Clock Stable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} ICGS2STR;
extern volatile ICGS2STR _ICGS2 @0x0000004B;
#define ICGS2                           _ICGS2.Byte
#define ICGS2_DCOS                      _ICGS2.Bits.DCOS

#define ICGS2_DCOS_MASK                 1


/*** ICGFLT - ICG Upper Filter; 0x0000004C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ICGFLTU - ICG Upper Filter Register; 0x0000004C ***/
    union {
      byte Byte;
      struct {
        byte FILT8       :1;                                       /* ICG Filter Bit 8 */
        byte FILT9       :1;                                       /* ICG Filter Bit 9 */
        byte FILT10      :1;                                       /* ICG Filter Bit 10 */
        byte FILT11      :1;                                       /* ICG Filter Bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpFILT_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ICGFLTUSTR;
    #define ICGFLTU                     _ICGFLT.Overlap_STR.ICGFLTUSTR.Byte
    #define ICGFLTU_FILT8               _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT8
    #define ICGFLTU_FILT9               _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT9
    #define ICGFLTU_FILT10              _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT10
    #define ICGFLTU_FILT11              _ICGFLT.Overlap_STR.ICGFLTUSTR.Bits.FILT11
    #define ICGFLTU_FILT_8              _ICGFLT.Overlap_STR.ICGFLTUSTR.MergedBits.grpFILT_8
    #define ICGFLTU_FILT                ICGFLTU_FILT_8
    
    #define ICGFLTU_FILT8_MASK          1
    #define ICGFLTU_FILT9_MASK          2
    #define ICGFLTU_FILT10_MASK         4
    #define ICGFLTU_FILT11_MASK         8
    #define ICGFLTU_FILT_8_MASK         15
    #define ICGFLTU_FILT_8_BITNUM       0
    

    /*** ICGFLTL - ICG Lower Filter Register; 0x0000004D ***/
    union {
      byte Byte;
      struct {
        byte FILT0       :1;                                       /* ICG Filter Bit 0 */
        byte FILT1       :1;                                       /* ICG Filter Bit 1 */
        byte FILT2       :1;                                       /* ICG Filter Bit 2 */
        byte FILT3       :1;                                       /* ICG Filter Bit 3 */
        byte FILT4       :1;                                       /* ICG Filter Bit 4 */
        byte FILT5       :1;                                       /* ICG Filter Bit 5 */
        byte FILT6       :1;                                       /* ICG Filter Bit 6 */
        byte FILT7       :1;                                       /* ICG Filter Bit 7 */
      } Bits;
    } ICGFLTLSTR;
    #define ICGFLTL                     _ICGFLT.Overlap_STR.ICGFLTLSTR.Byte
    #define ICGFLTL_FILT0               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT0
    #define ICGFLTL_FILT1               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT1
    #define ICGFLTL_FILT2               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT2
    #define ICGFLTL_FILT3               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT3
    #define ICGFLTL_FILT4               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT4
    #define ICGFLTL_FILT5               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT5
    #define ICGFLTL_FILT6               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT6
    #define ICGFLTL_FILT7               _ICGFLT.Overlap_STR.ICGFLTLSTR.Bits.FILT7
    
    #define ICGFLTL_FILT0_MASK          1
    #define ICGFLTL_FILT1_MASK          2
    #define ICGFLTL_FILT2_MASK          4
    #define ICGFLTL_FILT3_MASK          8
    #define ICGFLTL_FILT4_MASK          16
    #define ICGFLTL_FILT5_MASK          32
    #define ICGFLTL_FILT6_MASK          64
    #define ICGFLTL_FILT7_MASK          128
    
  } Overlap_STR;

} ICGFLTSTR;
extern volatile ICGFLTSTR _ICGFLT @0x0000004C;
#define ICGFLT                          _ICGFLT.Word


/*** ICGTRM - ICG Trim Register; 0x0000004E ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* ICG Trim Bit 0 */
    byte TRIM1       :1;                                       /* ICG Trim Bit 1 */
    byte TRIM2       :1;                                       /* ICG Trim Bit 2 */
    byte TRIM3       :1;                                       /* ICG Trim Bit 3 */
    byte TRIM4       :1;                                       /* ICG Trim Bit 4 */
    byte TRIM5       :1;                                       /* ICG Trim Bit 5 */
    byte TRIM6       :1;                                       /* ICG Trim Bit 6 */
    byte TRIM7       :1;                                       /* ICG Trim Bit 7 */
  } Bits;
} ICGTRMSTR;
extern volatile ICGTRMSTR _ICGTRM @0x0000004E;
#define ICGTRM                          _ICGTRM.Byte
#define ICGTRM_TRIM0                    _ICGTRM.Bits.TRIM0
#define ICGTRM_TRIM1                    _ICGTRM.Bits.TRIM1
#define ICGTRM_TRIM2                    _ICGTRM.Bits.TRIM2
#define ICGTRM_TRIM3                    _ICGTRM.Bits.TRIM3
#define ICGTRM_TRIM4                    _ICGTRM.Bits.TRIM4
#define ICGTRM_TRIM5                    _ICGTRM.Bits.TRIM5
#define ICGTRM_TRIM6                    _ICGTRM.Bits.TRIM6
#define ICGTRM_TRIM7                    _ICGTRM.Bits.TRIM7

#define ICGTRM_TRIM0_MASK               1
#define ICGTRM_TRIM1_MASK               2
#define ICGTRM_TRIM2_MASK               4
#define ICGTRM_TRIM3_MASK               8
#define ICGTRM_TRIM4_MASK               16
#define ICGTRM_TRIM5_MASK               32
#define ICGTRM_TRIM6_MASK               64
#define ICGTRM_TRIM7_MASK               128


/*** SPI1C1 - SPI1 Control Register 1; 0x00000050 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (shifter direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI1 Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI1 System Enable */
    byte SPIE        :1;                                       /* SPI1 Interrupt Enable */
  } Bits;
} SPI1C1STR;
extern volatile SPI1C1STR _SPI1C1 @0x00000050;
#define SPI1C1                          _SPI1C1.Byte
#define SPI1C1_LSBFE                    _SPI1C1.Bits.LSBFE
#define SPI1C1_SSOE                     _SPI1C1.Bits.SSOE
#define SPI1C1_CPHA                     _SPI1C1.Bits.CPHA
#define SPI1C1_CPOL                     _SPI1C1.Bits.CPOL
#define SPI1C1_MSTR                     _SPI1C1.Bits.MSTR
#define SPI1C1_SPTIE                    _SPI1C1.Bits.SPTIE
#define SPI1C1_SPE                      _SPI1C1.Bits.SPE
#define SPI1C1_SPIE                     _SPI1C1.Bits.SPIE

#define SPI1C1_LSBFE_MASK               1
#define SPI1C1_SSOE_MASK                2
#define SPI1C1_CPHA_MASK                4
#define SPI1C1_CPOL_MASK                8
#define SPI1C1_MSTR_MASK                16
#define SPI1C1_SPTIE_MASK               32
#define SPI1C1_SPE_MASK                 64
#define SPI1C1_SPIE_MASK                128


/*** SPI1C2 - SPI1 Control Register 2; 0x00000051 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI1 Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI1 Stop in Wait Mode */
    byte             :1; 
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SPI1C2STR;
extern volatile SPI1C2STR _SPI1C2 @0x00000051;
#define SPI1C2                          _SPI1C2.Byte
#define SPI1C2_SPC0                     _SPI1C2.Bits.SPC0
#define SPI1C2_SPISWAI                  _SPI1C2.Bits.SPISWAI
#define SPI1C2_BIDIROE                  _SPI1C2.Bits.BIDIROE
#define SPI1C2_MODFEN                   _SPI1C2.Bits.MODFEN

#define SPI1C2_SPC0_MASK                1
#define SPI1C2_SPISWAI_MASK             2
#define SPI1C2_BIDIROE_MASK             8
#define SPI1C2_MODFEN_MASK              16


/*** SPI1BR - SPI1 Baud Rate Register; 0x00000052 ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI1 Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI1 Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI1 Baud Rate Divisor Bit 2 */
    byte             :1; 
    byte SPPR0       :1;                                       /* SPI1 Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI1 Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI1 Baud Rate Prescale Divisor Bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpSPR  :3;
    byte         :1;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPI1BRSTR;
extern volatile SPI1BRSTR _SPI1BR @0x00000052;
#define SPI1BR                          _SPI1BR.Byte
#define SPI1BR_SPR0                     _SPI1BR.Bits.SPR0
#define SPI1BR_SPR1                     _SPI1BR.Bits.SPR1
#define SPI1BR_SPR2                     _SPI1BR.Bits.SPR2
#define SPI1BR_SPPR0                    _SPI1BR.Bits.SPPR0
#define SPI1BR_SPPR1                    _SPI1BR.Bits.SPPR1
#define SPI1BR_SPPR2                    _SPI1BR.Bits.SPPR2
#define SPI1BR_SPR                      _SPI1BR.MergedBits.grpSPR
#define SPI1BR_SPPR                     _SPI1BR.MergedBits.grpSPPR

#define SPI1BR_SPR0_MASK                1
#define SPI1BR_SPR1_MASK                2
#define SPI1BR_SPR2_MASK                4
#define SPI1BR_SPPR0_MASK               16
#define SPI1BR_SPPR1_MASK               32
#define SPI1BR_SPPR2_MASK               64
#define SPI1BR_SPR_MASK                 7
#define SPI1BR_SPR_BITNUM               0
#define SPI1BR_SPPR_MASK                112
#define SPI1BR_SPPR_BITNUM              4


/*** SPI1S - SPI1 Status Register; 0x00000053 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI1 Transmit Buffer Empty Flag */
    byte             :1; 
    byte SPRF        :1;                                       /* SPI1 Read Buffer Full Flag */
  } Bits;
} SPI1SSTR;
extern volatile SPI1SSTR _SPI1S @0x00000053;
#define SPI1S                           _SPI1S.Byte
#define SPI1S_MODF                      _SPI1S.Bits.MODF
#define SPI1S_SPTEF                     _SPI1S.Bits.SPTEF
#define SPI1S_SPRF                      _SPI1S.Bits.SPRF

#define SPI1S_MODF_MASK                 16
#define SPI1S_SPTEF_MASK                32
#define SPI1S_SPRF_MASK                 128


/*** SPI1D - SPI1 Data Register; 0x00000055 ***/
typedef union {
  byte Byte;
} SPI1DSTR;
extern volatile SPI1DSTR _SPI1D @0x00000055;
#define SPI1D                           _SPI1D.Byte


/*** IIC1A - IIC1 Address Register; 0x00000058 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte ADDR1       :1;                                       /* IIC Address Bit 1 */
    byte ADDR2       :1;                                       /* IIC Address Bit 2 */
    byte ADDR3       :1;                                       /* IIC Address Bit 3 */
    byte ADDR4       :1;                                       /* IIC Address Bit 4 */
    byte ADDR5       :1;                                       /* IIC Address Bit 5 */
    byte ADDR6       :1;                                       /* IIC Address Bit 6 */
    byte ADDR7       :1;                                       /* IIC Address Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpADDR_1 :7;
  } MergedBits;
} IIC1ASTR;
extern volatile IIC1ASTR _IIC1A @0x00000058;
#define IIC1A                           _IIC1A.Byte
#define IIC1A_ADDR1                     _IIC1A.Bits.ADDR1
#define IIC1A_ADDR2                     _IIC1A.Bits.ADDR2
#define IIC1A_ADDR3                     _IIC1A.Bits.ADDR3
#define IIC1A_ADDR4                     _IIC1A.Bits.ADDR4
#define IIC1A_ADDR5                     _IIC1A.Bits.ADDR5
#define IIC1A_ADDR6                     _IIC1A.Bits.ADDR6
#define IIC1A_ADDR7                     _IIC1A.Bits.ADDR7
#define IIC1A_ADDR_1                    _IIC1A.MergedBits.grpADDR_1
#define IIC1A_ADDR                      IIC1A_ADDR_1

#define IIC1A_ADDR1_MASK                2
#define IIC1A_ADDR2_MASK                4
#define IIC1A_ADDR3_MASK                8
#define IIC1A_ADDR4_MASK                16
#define IIC1A_ADDR5_MASK                32
#define IIC1A_ADDR6_MASK                64
#define IIC1A_ADDR7_MASK                128
#define IIC1A_ADDR_1_MASK               254
#define IIC1A_ADDR_1_BITNUM             1


/*** IIC1F - IIC1 Frequency Divider Register; 0x00000059 ***/
typedef union {
  byte Byte;
  struct {
    byte ICR0        :1;                                       /* IIC Clock Rate Bit 0 */
    byte ICR1        :1;                                       /* IIC Clock Rate Bit 1 */
    byte ICR2        :1;                                       /* IIC Clock Rate Bit 2 */
    byte ICR3        :1;                                       /* IIC Clock Rate Bit 3 */
    byte ICR4        :1;                                       /* IIC Clock Rate Bit 4 */
    byte ICR5        :1;                                       /* IIC Clock Rate Bit 5 */
    byte MULT0       :1;                                       /* Multiplier Factor Bit 0 */
    byte MULT1       :1;                                       /* Multiplier Factor Bit 1 */
  } Bits;
  struct {
    byte grpICR  :6;
    byte grpMULT :2;
  } MergedBits;
} IIC1FSTR;
extern volatile IIC1FSTR _IIC1F @0x00000059;
#define IIC1F                           _IIC1F.Byte
#define IIC1F_ICR0                      _IIC1F.Bits.ICR0
#define IIC1F_ICR1                      _IIC1F.Bits.ICR1
#define IIC1F_ICR2                      _IIC1F.Bits.ICR2
#define IIC1F_ICR3                      _IIC1F.Bits.ICR3
#define IIC1F_ICR4                      _IIC1F.Bits.ICR4
#define IIC1F_ICR5                      _IIC1F.Bits.ICR5
#define IIC1F_MULT0                     _IIC1F.Bits.MULT0
#define IIC1F_MULT1                     _IIC1F.Bits.MULT1
#define IIC1F_ICR                       _IIC1F.MergedBits.grpICR
#define IIC1F_MULT                      _IIC1F.MergedBits.grpMULT

#define IIC1F_ICR0_MASK                 1
#define IIC1F_ICR1_MASK                 2
#define IIC1F_ICR2_MASK                 4
#define IIC1F_ICR3_MASK                 8
#define IIC1F_ICR4_MASK                 16
#define IIC1F_ICR5_MASK                 32
#define IIC1F_MULT0_MASK                64
#define IIC1F_MULT1_MASK                128
#define IIC1F_ICR_MASK                  63
#define IIC1F_ICR_BITNUM                0
#define IIC1F_MULT_MASK                 192
#define IIC1F_MULT_BITNUM               6


/*** IIC1C - IIC1 Control Register; 0x0000005A ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte RSTA        :1;                                       /* Repeat START Bit */
    byte TXAK        :1;                                       /* Transmit Acknowledge Enable Bit */
    byte TX          :1;                                       /* Transmit Mode Select Bit */
    byte MST         :1;                                       /* Master Mode Select Bit */
    byte IICIE       :1;                                       /* IIC Interrupt Enable Bit */
    byte IICEN       :1;                                       /* IIC Enable Bit */
  } Bits;
} IIC1CSTR;
extern volatile IIC1CSTR _IIC1C @0x0000005A;
#define IIC1C                           _IIC1C.Byte
#define IIC1C_RSTA                      _IIC1C.Bits.RSTA
#define IIC1C_TXAK                      _IIC1C.Bits.TXAK
#define IIC1C_TX                        _IIC1C.Bits.TX
#define IIC1C_MST                       _IIC1C.Bits.MST
#define IIC1C_IICIE                     _IIC1C.Bits.IICIE
#define IIC1C_IICEN                     _IIC1C.Bits.IICEN

#define IIC1C_RSTA_MASK                 4
#define IIC1C_TXAK_MASK                 8
#define IIC1C_TX_MASK                   16
#define IIC1C_MST_MASK                  32
#define IIC1C_IICIE_MASK                64
#define IIC1C_IICEN_MASK                128


/*** IIC1S - IIC1 Status Register; 0x0000005B ***/
typedef union {
  byte Byte;
  struct {
    byte RXAK        :1;                                       /* Receive Acknowledge */
    byte IICIF       :1;                                       /* IIC Interrupt Flag */
    byte SRW         :1;                                       /* Slave Read/Write */
    byte             :1; 
    byte ARBL        :1;                                       /* Arbitration Lost */
    byte BUSY        :1;                                       /* Bus Busy bit */
    byte IAAS        :1;                                       /* Addressed as a Slave Bit */
    byte TCF         :1;                                       /* Transfer Complete Flag */
  } Bits;
} IIC1SSTR;
extern volatile IIC1SSTR _IIC1S @0x0000005B;
#define IIC1S                           _IIC1S.Byte
#define IIC1S_RXAK                      _IIC1S.Bits.RXAK
#define IIC1S_IICIF                     _IIC1S.Bits.IICIF
#define IIC1S_SRW                       _IIC1S.Bits.SRW
#define IIC1S_ARBL                      _IIC1S.Bits.ARBL
#define IIC1S_BUSY                      _IIC1S.Bits.BUSY
#define IIC1S_IAAS                      _IIC1S.Bits.IAAS
#define IIC1S_TCF                       _IIC1S.Bits.TCF

#define IIC1S_RXAK_MASK                 1
#define IIC1S_IICIF_MASK                2
#define IIC1S_SRW_MASK                  4
#define IIC1S_ARBL_MASK                 16
#define IIC1S_BUSY_MASK                 32
#define IIC1S_IAAS_MASK                 64
#define IIC1S_TCF_MASK                  128


/*** IIC1D - IIC1 Data I/O Register; 0x0000005C ***/
typedef union {
  byte Byte;
  struct {
    byte DATA0       :1;                                       /* IIC Data Bit 0 */
    byte DATA1       :1;                                       /* IIC Data Bit 1 */
    byte DATA2       :1;                                       /* IIC Data Bit 2 */
    byte DATA3       :1;                                       /* IIC Data Bit 3 */
    byte DATA4       :1;                                       /* IIC Data Bit 4 */
    byte DATA5       :1;                                       /* IIC Data Bit 5 */
    byte DATA6       :1;                                       /* IIC Data Bit 6 */
    byte DATA7       :1;                                       /* IIC Data Bit 7 */
  } Bits;
} IIC1DSTR;
extern volatile IIC1DSTR _IIC1D @0x0000005C;
#define IIC1D                           _IIC1D.Byte
#define IIC1D_DATA0                     _IIC1D.Bits.DATA0
#define IIC1D_DATA1                     _IIC1D.Bits.DATA1
#define IIC1D_DATA2                     _IIC1D.Bits.DATA2
#define IIC1D_DATA3                     _IIC1D.Bits.DATA3
#define IIC1D_DATA4                     _IIC1D.Bits.DATA4
#define IIC1D_DATA5                     _IIC1D.Bits.DATA5
#define IIC1D_DATA6                     _IIC1D.Bits.DATA6
#define IIC1D_DATA7                     _IIC1D.Bits.DATA7

#define IIC1D_DATA0_MASK                1
#define IIC1D_DATA1_MASK                2
#define IIC1D_DATA2_MASK                4
#define IIC1D_DATA3_MASK                8
#define IIC1D_DATA4_MASK                16
#define IIC1D_DATA5_MASK                32
#define IIC1D_DATA6_MASK                64
#define IIC1D_DATA7_MASK                128


/*** TPM2SC - TPM 2 Status and Control Register; 0x00000060 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2SCSTR;
extern volatile TPM2SCSTR _TPM2SC @0x00000060;
#define TPM2SC                          _TPM2SC.Byte
#define TPM2SC_PS0                      _TPM2SC.Bits.PS0
#define TPM2SC_PS1                      _TPM2SC.Bits.PS1
#define TPM2SC_PS2                      _TPM2SC.Bits.PS2
#define TPM2SC_CLKSA                    _TPM2SC.Bits.CLKSA
#define TPM2SC_CLKSB                    _TPM2SC.Bits.CLKSB
#define TPM2SC_CPWMS                    _TPM2SC.Bits.CPWMS
#define TPM2SC_TOIE                     _TPM2SC.Bits.TOIE
#define TPM2SC_TOF                      _TPM2SC.Bits.TOF
#define TPM2SC_PS                       _TPM2SC.MergedBits.grpPS
#define TPM2SC_CLKSx                    _TPM2SC.MergedBits.grpCLKSx

#define TPM2SC_PS0_MASK                 1
#define TPM2SC_PS1_MASK                 2
#define TPM2SC_PS2_MASK                 4
#define TPM2SC_CLKSA_MASK               8
#define TPM2SC_CLKSB_MASK               16
#define TPM2SC_CPWMS_MASK               32
#define TPM2SC_TOIE_MASK                64
#define TPM2SC_TOF_MASK                 128
#define TPM2SC_PS_MASK                  7
#define TPM2SC_PS_BITNUM                0
#define TPM2SC_CLKSx_MASK               24
#define TPM2SC_CLKSx_BITNUM             3


/*** TPM2CNT - TPM 2 Counter Register; 0x00000061 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2CNTH - TPM 2 Counter Register High; 0x00000061 ***/
    union {
      byte Byte;
    } TPM2CNTHSTR;
    #define TPM2CNTH                    _TPM2CNT.Overlap_STR.TPM2CNTHSTR.Byte
    

    /*** TPM2CNTL - TPM 2 Counter Register Low; 0x00000062 ***/
    union {
      byte Byte;
    } TPM2CNTLSTR;
    #define TPM2CNTL                    _TPM2CNT.Overlap_STR.TPM2CNTLSTR.Byte
    
  } Overlap_STR;

} TPM2CNTSTR;
extern volatile TPM2CNTSTR _TPM2CNT @0x00000061;
#define TPM2CNT                         _TPM2CNT.Word


/*** TPM2MOD - TPM 2 Timer Counter Modulo Register; 0x00000063 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2MODH - TPM 2 Timer Counter Modulo Register High; 0x00000063 ***/
    union {
      byte Byte;
    } TPM2MODHSTR;
    #define TPM2MODH                    _TPM2MOD.Overlap_STR.TPM2MODHSTR.Byte
    

    /*** TPM2MODL - TPM 2 Timer Counter Modulo Register Low; 0x00000064 ***/
    union {
      byte Byte;
    } TPM2MODLSTR;
    #define TPM2MODL                    _TPM2MOD.Overlap_STR.TPM2MODLSTR.Byte
    
  } Overlap_STR;

} TPM2MODSTR;
extern volatile TPM2MODSTR _TPM2MOD @0x00000063;
#define TPM2MOD                         _TPM2MOD.Word


/*** TPM2C0SC - TPM 2 Timer Channel 0 Status and Control Register; 0x00000065 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C0SCSTR;
extern volatile TPM2C0SCSTR _TPM2C0SC @0x00000065;
#define TPM2C0SC                        _TPM2C0SC.Byte
#define TPM2C0SC_ELS0A                  _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELS0B                  _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MS0A                   _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MS0B                   _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CH0IE                  _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CH0F                   _TPM2C0SC.Bits.CH0F
#define TPM2C0SC_ELS0x                  _TPM2C0SC.MergedBits.grpELS0x
#define TPM2C0SC_MS0x                   _TPM2C0SC.MergedBits.grpMS0x

#define TPM2C0SC_ELS0A_MASK             4
#define TPM2C0SC_ELS0B_MASK             8
#define TPM2C0SC_MS0A_MASK              16
#define TPM2C0SC_MS0B_MASK              32
#define TPM2C0SC_CH0IE_MASK             64
#define TPM2C0SC_CH0F_MASK              128
#define TPM2C0SC_ELS0x_MASK             12
#define TPM2C0SC_ELS0x_BITNUM           2
#define TPM2C0SC_MS0x_MASK              48
#define TPM2C0SC_MS0x_BITNUM            4


/*** TPM2C0V - TPM 2 Timer Channel 0 Value Register; 0x00000066 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C0VH - TPM 2 Timer Channel 0 Value Register High; 0x00000066 ***/
    union {
      byte Byte;
    } TPM2C0VHSTR;
    #define TPM2C0VH                    _TPM2C0V.Overlap_STR.TPM2C0VHSTR.Byte
    

    /*** TPM2C0VL - TPM 2 Timer Channel 0 Value Register Low; 0x00000067 ***/
    union {
      byte Byte;
    } TPM2C0VLSTR;
    #define TPM2C0VL                    _TPM2C0V.Overlap_STR.TPM2C0VLSTR.Byte
    
  } Overlap_STR;

} TPM2C0VSTR;
extern volatile TPM2C0VSTR _TPM2C0V @0x00000066;
#define TPM2C0V                         _TPM2C0V.Word


/*** TPM2C1SC - TPM 2 Timer Channel 1 Status and Control Register; 0x00000068 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C1SCSTR;
extern volatile TPM2C1SCSTR _TPM2C1SC @0x00000068;
#define TPM2C1SC                        _TPM2C1SC.Byte
#define TPM2C1SC_ELS1A                  _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELS1B                  _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MS1A                   _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MS1B                   _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CH1IE                  _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CH1F                   _TPM2C1SC.Bits.CH1F
#define TPM2C1SC_ELS1x                  _TPM2C1SC.MergedBits.grpELS1x
#define TPM2C1SC_MS1x                   _TPM2C1SC.MergedBits.grpMS1x

#define TPM2C1SC_ELS1A_MASK             4
#define TPM2C1SC_ELS1B_MASK             8
#define TPM2C1SC_MS1A_MASK              16
#define TPM2C1SC_MS1B_MASK              32
#define TPM2C1SC_CH1IE_MASK             64
#define TPM2C1SC_CH1F_MASK              128
#define TPM2C1SC_ELS1x_MASK             12
#define TPM2C1SC_ELS1x_BITNUM           2
#define TPM2C1SC_MS1x_MASK              48
#define TPM2C1SC_MS1x_BITNUM            4


/*** TPM2C1V - TPM 2 Timer Channel 1 Value Register; 0x00000069 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C1VH - TPM 2 Timer Channel 1 Value Register High; 0x00000069 ***/
    union {
      byte Byte;
    } TPM2C1VHSTR;
    #define TPM2C1VH                    _TPM2C1V.Overlap_STR.TPM2C1VHSTR.Byte
    

    /*** TPM2C1VL - TPM 2 Timer Channel 1 Value Register Low; 0x0000006A ***/
    union {
      byte Byte;
    } TPM2C1VLSTR;
    #define TPM2C1VL                    _TPM2C1V.Overlap_STR.TPM2C1VLSTR.Byte
    
  } Overlap_STR;

} TPM2C1VSTR;
extern volatile TPM2C1VSTR _TPM2C1V @0x00000069;
#define TPM2C1V                         _TPM2C1V.Word


/*** SRS - System Reset Status; 0x00001800 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte LVD         :1;                                       /* Low Voltage Detect */
    byte ICG         :1;                                       /* Internal Clock Generation Module Reset */
    byte             :1; 
    byte ILOP        :1;                                       /* Illegal Opcode */
    byte COP         :1;                                       /* Computer Operating Properly (COP) Watchdog */
    byte PIN         :1;                                       /* External Reset Pin */
    byte POR         :1;                                       /* Power-On Reset */
  } Bits;
} SRSSTR;
extern volatile SRSSTR _SRS @0x00001800;
#define SRS                             _SRS.Byte
#define SRS_LVD                         _SRS.Bits.LVD
#define SRS_ICG                         _SRS.Bits.ICG
#define SRS_ILOP                        _SRS.Bits.ILOP
#define SRS_COP                         _SRS.Bits.COP
#define SRS_PIN                         _SRS.Bits.PIN
#define SRS_POR                         _SRS.Bits.POR

#define SRS_LVD_MASK                    2
#define SRS_ICG_MASK                    4
#define SRS_ILOP_MASK                   16
#define SRS_COP_MASK                    32
#define SRS_PIN_MASK                    64
#define SRS_POR_MASK                    128


/*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***/
typedef union {
  byte Byte;
  struct {
    byte BDFR        :1;                                       /* Background Debug Force Reset */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SBDFRSTR;
extern volatile SBDFRSTR _SBDFR @0x00001801;
#define SBDFR                           _SBDFR.Byte
#define SBDFR_BDFR                      _SBDFR.Bits.BDFR

#define SBDFR_BDFR_MASK                 1


/*** SOPT - System Options Register; 0x00001802 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte STOPE       :1;                                       /* Stop Mode Enable */
    byte COPT        :1;                                       /* COP Watchdog Timeout */
    byte COPE        :1;                                       /* COP Watchdog Enable */
  } Bits;
} SOPTSTR;
extern volatile SOPTSTR _SOPT @0x00001802;
#define SOPT                            _SOPT.Byte
#define SOPT_STOPE                      _SOPT.Bits.STOPE
#define SOPT_COPT                       _SOPT.Bits.COPT
#define SOPT_COPE                       _SOPT.Bits.COPE

#define SOPT_STOPE_MASK                 32
#define SOPT_COPT_MASK                  64
#define SOPT_COPE_MASK                  128


/*** SMCLK - System MCLK Control Register; 0x00001803 ***/
typedef union {
  byte Byte;
  struct {
    byte MCSEL0      :1;                                       /* MCLK Divide Select, bit 0 */
    byte MCSEL1      :1;                                       /* MCLK Divide Select, bit 1 */
    byte MCSEL2      :1;                                       /* MCLK Divide Select, bit 2 */
    byte             :1; 
    byte MPE         :1;                                       /* MCLK Pin Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpMCSEL :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SMCLKSTR;
extern volatile SMCLKSTR _SMCLK @0x00001803;
#define SMCLK                           _SMCLK.Byte
#define SMCLK_MCSEL0                    _SMCLK.Bits.MCSEL0
#define SMCLK_MCSEL1                    _SMCLK.Bits.MCSEL1
#define SMCLK_MCSEL2                    _SMCLK.Bits.MCSEL2
#define SMCLK_MPE                       _SMCLK.Bits.MPE
#define SMCLK_MCSEL                     _SMCLK.MergedBits.grpMCSEL

#define SMCLK_MCSEL0_MASK               1
#define SMCLK_MCSEL1_MASK               2
#define SMCLK_MCSEL2_MASK               4
#define SMCLK_MPE_MASK                  16
#define SMCLK_MCSEL_MASK                7
#define SMCLK_MCSEL_BITNUM              0


/*** SDID - System Integration Module Part ID Register; 0x00001806 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SDIDH - System Integration Module Part ID Register High; 0x00001806 ***/
    union {
      byte Byte;
      struct {
        byte ID8         :1;                                       /* Part Identification Number 8 */
        byte ID9         :1;                                       /* Part Identification Number 9 */
        byte ID10        :1;                                       /* Part Identification Number 10 */
        byte ID11        :1;                                       /* Part Identification Number 11 */
        byte REV0        :1;                                       /* Revision Number 0 */
        byte REV1        :1;                                       /* Revision Number 1 */
        byte REV2        :1;                                       /* Revision Number 2 */
        byte REV3        :1;                                       /* Revision Number 3 */
      } Bits;
      struct {
        byte grpID_8 :4;
        byte grpREV :4;
      } MergedBits;
    } SDIDHSTR;
    #define SDIDH                       _SDID.Overlap_STR.SDIDHSTR.Byte
    #define SDIDH_ID8                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID8
    #define SDIDH_ID9                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID9
    #define SDIDH_ID10                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID10
    #define SDIDH_ID11                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID11
    #define SDIDH_REV0                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV0
    #define SDIDH_REV1                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV1
    #define SDIDH_REV2                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV2
    #define SDIDH_REV3                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV3
    #define SDIDH_ID_8                  _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpID_8
    #define SDIDH_REV                   _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpREV
    #define SDIDH_ID                    SDIDH_ID_8
    
    #define SDIDH_ID8_MASK              1
    #define SDIDH_ID9_MASK              2
    #define SDIDH_ID10_MASK             4
    #define SDIDH_ID11_MASK             8
    #define SDIDH_REV0_MASK             16
    #define SDIDH_REV1_MASK             32
    #define SDIDH_REV2_MASK             64
    #define SDIDH_REV3_MASK             128
    #define SDIDH_ID_8_MASK             15
    #define SDIDH_ID_8_BITNUM           0
    #define SDIDH_REV_MASK              240
    #define SDIDH_REV_BITNUM            4
    

    /*** SDIDL - System Integration Module Part ID Register Low; 0x00001807 ***/
    union {
      byte Byte;
      struct {
        byte ID0         :1;                                       /* Part Identification Number 0 */
        byte ID1         :1;                                       /* Part Identification Number 1 */
        byte ID2         :1;                                       /* Part Identification Number 2 */
        byte ID3         :1;                                       /* Part Identification Number 3 */
        byte ID4         :1;                                       /* Part Identification Number 4 */
        byte ID5         :1;                                       /* Part Identification Number 5 */
        byte ID6         :1;                                       /* Part Identification Number 6 */
        byte ID7         :1;                                       /* Part Identification Number 7 */
      } Bits;
    } SDIDLSTR;
    #define SDIDL                       _SDID.Overlap_STR.SDIDLSTR.Byte
    #define SDIDL_ID0                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID0
    #define SDIDL_ID1                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID1
    #define SDIDL_ID2                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID2
    #define SDIDL_ID3                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID3
    #define SDIDL_ID4                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID4
    #define SDIDL_ID5                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID5
    #define SDIDL_ID6                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID6
    #define SDIDL_ID7                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID7
    
    #define SDIDL_ID0_MASK              1
    #define SDIDL_ID1_MASK              2
    #define SDIDL_ID2_MASK              4
    #define SDIDL_ID3_MASK              8
    #define SDIDL_ID4_MASK              16
    #define SDIDL_ID5_MASK              32
    #define SDIDL_ID6_MASK              64
    #define SDIDL_ID7_MASK              128
    
  } Overlap_STR;

} SDIDSTR;
extern volatile SDIDSTR _SDID @0x00001806;
#define SDID                            _SDID.Word


/*** SRTISC - System RTI Status and Control Register; 0x00001808 ***/
typedef union {
  byte Byte;
  struct {
    byte RTIS0       :1;                                       /* Real-Time Interrupt Delay Select Bit 0 */
    byte RTIS1       :1;                                       /* Real-Time Interrupt Delay Select Bit 1 */
    byte RTIS2       :1;                                       /* Real-Time Interrupt Delay Select Bit 2 */
    byte             :1; 
    byte RTIE        :1;                                       /* Real-Time Interrupt Enable */
    byte RTICLKS     :1;                                       /* Real-Time Interrupt Clock Select */
    byte RTIACK      :1;                                       /* Real-Time Interrupt Acknowledge */
    byte RTIF        :1;                                       /* Real-Time Interrupt Flag */
  } Bits;
  struct {
    byte grpRTIS :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SRTISCSTR;
extern volatile SRTISCSTR _SRTISC @0x00001808;
#define SRTISC                          _SRTISC.Byte
#define SRTISC_RTIS0                    _SRTISC.Bits.RTIS0
#define SRTISC_RTIS1                    _SRTISC.Bits.RTIS1
#define SRTISC_RTIS2                    _SRTISC.Bits.RTIS2
#define SRTISC_RTIE                     _SRTISC.Bits.RTIE
#define SRTISC_RTICLKS                  _SRTISC.Bits.RTICLKS
#define SRTISC_RTIACK                   _SRTISC.Bits.RTIACK
#define SRTISC_RTIF                     _SRTISC.Bits.RTIF
#define SRTISC_RTIS                     _SRTISC.MergedBits.grpRTIS

#define SRTISC_RTIS0_MASK               1
#define SRTISC_RTIS1_MASK               2
#define SRTISC_RTIS2_MASK               4
#define SRTISC_RTIE_MASK                16
#define SRTISC_RTICLKS_MASK             32
#define SRTISC_RTIACK_MASK              64
#define SRTISC_RTIF_MASK                128
#define SRTISC_RTIS_MASK                7
#define SRTISC_RTIS_BITNUM              0


/*** SPMSC1 - PM Status and Control 1 Register; 0x00001809 ***/
typedef union {
  byte Byte;
  struct {
    byte BGBE        :1;                                       /* Bandgap Buffer Enable */
    byte             :1; 
    byte LVDE        :1;                                       /* Low-Voltage Detect Enable */
    byte LVDSE       :1;                                       /* Low-Voltage Detect Stop Enable */
    byte LVDRE       :1;                                       /* Low-Voltage Detect Reset Enable */
    byte LVDIE       :1;                                       /* Low-Voltage Detect Interrrupt Enable */
    byte LVDACK      :1;                                       /* Low-Voltage Detect Acknowledge */
    byte LVDF        :1;                                       /* Low-Voltage Detect Flag */
  } Bits;
} SPMSC1STR;
extern volatile SPMSC1STR _SPMSC1 @0x00001809;
#define SPMSC1                          _SPMSC1.Byte
#define SPMSC1_BGBE                     _SPMSC1.Bits.BGBE
#define SPMSC1_LVDE                     _SPMSC1.Bits.LVDE
#define SPMSC1_LVDSE                    _SPMSC1.Bits.LVDSE
#define SPMSC1_LVDRE                    _SPMSC1.Bits.LVDRE
#define SPMSC1_LVDIE                    _SPMSC1.Bits.LVDIE
#define SPMSC1_LVDACK                   _SPMSC1.Bits.LVDACK
#define SPMSC1_LVDF                     _SPMSC1.Bits.LVDF

#define SPMSC1_BGBE_MASK                1
#define SPMSC1_LVDE_MASK                4
#define SPMSC1_LVDSE_MASK               8
#define SPMSC1_LVDRE_MASK               16
#define SPMSC1_LVDIE_MASK               32
#define SPMSC1_LVDACK_MASK              64
#define SPMSC1_LVDF_MASK                128


/*** SPMSC2 - PM Status and Control 2 Register; 0x0000180A ***/
typedef union {
  byte Byte;
  struct {
    byte PPDC        :1;                                       /* Partial Power Down Control */
    byte             :1; 
    byte PPDACK      :1;                                       /* Partial Power Down Acknowlege */
    byte PPDF        :1;                                       /* Partial Power Down Flag */
    byte LVWV        :1;                                       /* Low-Voltage Warning Voltage Select */
    byte LVDV        :1;                                       /* Low-Voltage Detect Voltage Select */
    byte LVWACK      :1;                                       /* Low-Voltage Warning Acknowlege */
    byte LVWF        :1;                                       /* Low-Voltage Warning Flag */
  } Bits;
} SPMSC2STR;
extern volatile SPMSC2STR _SPMSC2 @0x0000180A;
#define SPMSC2                          _SPMSC2.Byte
#define SPMSC2_PPDC                     _SPMSC2.Bits.PPDC
#define SPMSC2_PPDACK                   _SPMSC2.Bits.PPDACK
#define SPMSC2_PPDF                     _SPMSC2.Bits.PPDF
#define SPMSC2_LVWV                     _SPMSC2.Bits.LVWV
#define SPMSC2_LVDV                     _SPMSC2.Bits.LVDV
#define SPMSC2_LVWACK                   _SPMSC2.Bits.LVWACK
#define SPMSC2_LVWF                     _SPMSC2.Bits.LVWF

#define SPMSC2_PPDC_MASK                1
#define SPMSC2_PPDACK_MASK              4
#define SPMSC2_PPDF_MASK                8
#define SPMSC2_LVWV_MASK                16
#define SPMSC2_LVDV_MASK                32
#define SPMSC2_LVWACK_MASK              64
#define SPMSC2_LVWF_MASK                128


/*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit8        :1;                                       /* Debug Comparator A Bit 8 */
    byte Bit9        :1;                                       /* Debug Comparator A Bit 9 */
    byte Bit10       :1;                                       /* Debug Comparator A Bit 10 */
    byte Bit11       :1;                                       /* Debug Comparator A Bit 11 */
    byte Bit12       :1;                                       /* Debug Comparator A Bit 12 */
    byte Bit13       :1;                                       /* Debug Comparator A Bit 13 */
    byte Bit14       :1;                                       /* Debug Comparator A Bit 14 */
    byte Bit15       :1;                                       /* Debug Comparator A Bit 15 */
  } Bits;
} DBGCAHSTR;
extern volatile DBGCAHSTR _DBGCAH @0x00001810;
#define DBGCAH                          _DBGCAH.Byte
#define DBGCAH_Bit8                     _DBGCAH.Bits.Bit8
#define DBGCAH_Bit9                     _DBGCAH.Bits.Bit9
#define DBGCAH_Bit10                    _DBGCAH.Bits.Bit10
#define DBGCAH_Bit11                    _DBGCAH.Bits.Bit11
#define DBGCAH_Bit12                    _DBGCAH.Bits.Bit12
#define DBGCAH_Bit13                    _DBGCAH.Bits.Bit13
#define DBGCAH_Bit14                    _DBGCAH.Bits.Bit14
#define DBGCAH_Bit15                    _DBGCAH.Bits.Bit15

#define DBGCAH_Bit8_MASK                1
#define DBGCAH_Bit9_MASK                2
#define DBGCAH_Bit10_MASK               4
#define DBGCAH_Bit11_MASK               8
#define DBGCAH_Bit12_MASK               16
#define DBGCAH_Bit13_MASK               32
#define DBGCAH_Bit14_MASK               64
#define DBGCAH_Bit15_MASK               128


/*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit0        :1;                                       /* Debug Comparator A Bit 0 */
    byte Bit1        :1;                                       /* Debug Comparator A Bit 1 */
    byte Bit2        :1;                                       /* Debug Comparator A Bit 2 */
    byte Bit3        :1;                                       /* Debug Comparator A Bit 3 */
    byte Bit4        :1;                                       /* Debug Comparator A Bit 4 */
    byte Bit5        :1;                                       /* Debug Comparator A Bit 5 */
    byte Bit6        :1;                                       /* Debug Comparator A Bit 6 */
    byte Bit7        :1;                                       /* Debug Comparator A Bit 7 */
  } Bits;
} DBGCALSTR;
extern volatile DBGCALSTR _DBGCAL @0x00001811;
#define DBGCAL                          _DBGCAL.Byte
#define DBGCAL_Bit0                     _DBGCAL.Bits.Bit0
#define DBGCAL_Bit1                     _DBGCAL.Bits.Bit1
#define DBGCAL_Bit2                     _DBGCAL.Bits.Bit2
#define DBGCAL_Bit3                     _DBGCAL.Bits.Bit3
#define DBGCAL_Bit4                     _DBGCAL.Bits.Bit4
#define DBGCAL_Bit5                     _DBGCAL.Bits.Bit5
#define DBGCAL_Bit6                     _DBGCAL.Bits.Bit6
#define DBGCAL_Bit7                     _DBGCAL.Bits.Bit7

#define DBGCAL_Bit0_MASK                1
#define DBGCAL_Bit1_MASK                2
#define DBGCAL_Bit2_MASK                4
#define DBGCAL_Bit3_MASK                8
#define DBGCAL_Bit4_MASK                16
#define DBGCAL_Bit5_MASK                32
#define DBGCAL_Bit6_MASK                64
#define DBGCAL_Bit7_MASK                128


/*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit8        :1;                                       /* Debug Comparator B Bit 8 */
    byte Bit9        :1;                                       /* Debug Comparator B Bit 9 */
    byte Bit10       :1;                                       /* Debug Comparator B Bit 10 */
    byte Bit11       :1;                                       /* Debug Comparator B Bit 11 */
    byte Bit12       :1;                                       /* Debug Comparator B Bit 12 */
    byte Bit13       :1;                                       /* Debug Comparator B Bit 13 */
    byte Bit14       :1;                                       /* Debug Comparator B Bit 14 */
    byte Bit15       :1;                                       /* Debug Comparator B Bit 15 */
  } Bits;
} DBGCBHSTR;
extern volatile DBGCBHSTR _DBGCBH @0x00001812;
#define DBGCBH                          _DBGCBH.Byte
#define DBGCBH_Bit8                     _DBGCBH.Bits.Bit8
#define DBGCBH_Bit9                     _DBGCBH.Bits.Bit9
#define DBGCBH_Bit10                    _DBGCBH.Bits.Bit10
#define DBGCBH_Bit11                    _DBGCBH.Bits.Bit11
#define DBGCBH_Bit12                    _DBGCBH.Bits.Bit12
#define DBGCBH_Bit13                    _DBGCBH.Bits.Bit13
#define DBGCBH_Bit14                    _DBGCBH.Bits.Bit14
#define DBGCBH_Bit15                    _DBGCBH.Bits.Bit15

#define DBGCBH_Bit8_MASK                1
#define DBGCBH_Bit9_MASK                2
#define DBGCBH_Bit10_MASK               4
#define DBGCBH_Bit11_MASK               8
#define DBGCBH_Bit12_MASK               16
#define DBGCBH_Bit13_MASK               32
#define DBGCBH_Bit14_MASK               64
#define DBGCBH_Bit15_MASK               128


/*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit0        :1;                                       /* Debug Comparator B Bit 0 */
    byte Bit1        :1;                                       /* Debug Comparator B Bit 1 */
    byte Bit2        :1;                                       /* Debug Comparator B Bit 2 */
    byte Bit3        :1;                                       /* Debug Comparator B Bit 3 */
    byte Bit4        :1;                                       /* Debug Comparator B Bit 4 */
    byte Bit5        :1;                                       /* Debug Comparator B Bit 5 */
    byte Bit6        :1;                                       /* Debug Comparator B Bit 6 */
    byte Bit7        :1;                                       /* Debug Comparator B Bit 7 */
  } Bits;
} DBGCBLSTR;
extern volatile DBGCBLSTR _DBGCBL @0x00001813;
#define DBGCBL                          _DBGCBL.Byte
#define DBGCBL_Bit0                     _DBGCBL.Bits.Bit0
#define DBGCBL_Bit1                     _DBGCBL.Bits.Bit1
#define DBGCBL_Bit2                     _DBGCBL.Bits.Bit2
#define DBGCBL_Bit3                     _DBGCBL.Bits.Bit3
#define DBGCBL_Bit4                     _DBGCBL.Bits.Bit4
#define DBGCBL_Bit5                     _DBGCBL.Bits.Bit5
#define DBGCBL_Bit6                     _DBGCBL.Bits.Bit6
#define DBGCBL_Bit7                     _DBGCBL.Bits.Bit7

#define DBGCBL_Bit0_MASK                1
#define DBGCBL_Bit1_MASK                2
#define DBGCBL_Bit2_MASK                4
#define DBGCBL_Bit3_MASK                8
#define DBGCBL_Bit4_MASK                16
#define DBGCBL_Bit5_MASK                32
#define DBGCBL_Bit6_MASK                64
#define DBGCBL_Bit7_MASK                128


/*** DBGF - Debug FIFO Register; 0x00001814 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGFH - Debug FIFO High Register; 0x00001814 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Debug FIFO Bit 8 */
        byte Bit9        :1;                                       /* Debug FIFO Bit 9 */
        byte Bit10       :1;                                       /* Debug FIFO Bit 10 */
        byte Bit11       :1;                                       /* Debug FIFO Bit 11 */
        byte Bit12       :1;                                       /* Debug FIFO Bit 12 */
        byte Bit13       :1;                                       /* Debug FIFO Bit 13 */
        byte Bit14       :1;                                       /* Debug FIFO Bit 14 */
        byte Bit15       :1;                                       /* Debug FIFO Bit 15 */
      } Bits;
    } DBGFHSTR;
    #define DBGFH                       _DBGF.Overlap_STR.DBGFHSTR.Byte
    #define DBGFH_Bit8                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit8
    #define DBGFH_Bit9                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit9
    #define DBGFH_Bit10                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit10
    #define DBGFH_Bit11                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit11
    #define DBGFH_Bit12                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit12
    #define DBGFH_Bit13                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit13
    #define DBGFH_Bit14                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit14
    #define DBGFH_Bit15                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit15
    
    #define DBGFH_Bit8_MASK             1
    #define DBGFH_Bit9_MASK             2
    #define DBGFH_Bit10_MASK            4
    #define DBGFH_Bit11_MASK            8
    #define DBGFH_Bit12_MASK            16
    #define DBGFH_Bit13_MASK            32
    #define DBGFH_Bit14_MASK            64
    #define DBGFH_Bit15_MASK            128
    

    /*** DBGFL - Debug FIFO Low Register; 0x00001815 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Debug FIFO Bit 0 */
        byte Bit1        :1;                                       /* Debug FIFO Bit 1 */
        byte Bit2        :1;                                       /* Debug FIFO Bit 2 */
        byte Bit3        :1;                                       /* Debug FIFO Bit 3 */
        byte Bit4        :1;                                       /* Debug FIFO Bit 4 */
        byte Bit5        :1;                                       /* Debug FIFO Bit 5 */
        byte Bit6        :1;                                       /* Debug FIFO Bit 6 */
        byte Bit7        :1;                                       /* Debug FIFO Bit 7 */
      } Bits;
    } DBGFLSTR;
    #define DBGFL                       _DBGF.Overlap_STR.DBGFLSTR.Byte
    #define DBGFL_Bit0                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit0
    #define DBGFL_Bit1                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit1
    #define DBGFL_Bit2                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit2
    #define DBGFL_Bit3                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit3
    #define DBGFL_Bit4                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit4
    #define DBGFL_Bit5                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit5
    #define DBGFL_Bit6                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit6
    #define DBGFL_Bit7                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit7
    
    #define DBGFL_Bit0_MASK             1
    #define DBGFL_Bit1_MASK             2
    #define DBGFL_Bit2_MASK             4
    #define DBGFL_Bit3_MASK             8
    #define DBGFL_Bit4_MASK             16
    #define DBGFL_Bit5_MASK             32
    #define DBGFL_Bit6_MASK             64
    #define DBGFL_Bit7_MASK             128
    
  } Overlap_STR;

} DBGFSTR;
extern volatile DBGFSTR _DBGF @0x00001814;
#define DBGF                            _DBGF.Word


/*** DBGC - Debug Control Register; 0x00001816 ***/
typedef union {
  byte Byte;
  struct {
    byte RWBEN       :1;                                       /* Enable R/W for Comparator B */
    byte RWB         :1;                                       /* R/W Comparison Value for Comparator B */
    byte RWAEN       :1;                                       /* Enable R/W for Comparator A */
    byte RWA         :1;                                       /* R/W Comparison Value for Comparator A */
    byte BRKEN       :1;                                       /* Break Enable */
    byte TAG         :1;                                       /* Tag/Force Select */
    byte ARM         :1;                                       /* Arm Control */
    byte DBGEN       :1;                                       /* Debug Module Enable */
  } Bits;
} DBGCSTR;
extern volatile DBGCSTR _DBGC @0x00001816;
#define DBGC                            _DBGC.Byte
#define DBGC_RWBEN                      _DBGC.Bits.RWBEN
#define DBGC_RWB                        _DBGC.Bits.RWB
#define DBGC_RWAEN                      _DBGC.Bits.RWAEN
#define DBGC_RWA                        _DBGC.Bits.RWA
#define DBGC_BRKEN                      _DBGC.Bits.BRKEN
#define DBGC_TAG                        _DBGC.Bits.TAG
#define DBGC_ARM                        _DBGC.Bits.ARM
#define DBGC_DBGEN                      _DBGC.Bits.DBGEN

#define DBGC_RWBEN_MASK                 1
#define DBGC_RWB_MASK                   2
#define DBGC_RWAEN_MASK                 4
#define DBGC_RWA_MASK                   8
#define DBGC_BRKEN_MASK                 16
#define DBGC_TAG_MASK                   32
#define DBGC_ARM_MASK                   64
#define DBGC_DBGEN_MASK                 128


/*** DBGT - Debug Trigger Register; 0x00001817 ***/
typedef union {
  byte Byte;
  struct {
    byte TRG0        :1;                                       /* Select Trigger Mode Bit 0 */
    byte TRG1        :1;                                       /* Select Trigger Mode Bit 1 */
    byte TRG2        :1;                                       /* Select Trigger Mode Bit 2 */
    byte TRG3        :1;                                       /* Select Trigger Mode Bit 3 */
    byte             :1; 
    byte             :1; 
    byte BEGIN       :1;                                       /* Begin/End Trigger Select */
    byte TRGSEL      :1;                                       /* Trigger Type */
  } Bits;
  struct {
    byte grpTRG  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGTSTR;
extern volatile DBGTSTR _DBGT @0x00001817;
#define DBGT                            _DBGT.Byte
#define DBGT_TRG0                       _DBGT.Bits.TRG0
#define DBGT_TRG1                       _DBGT.Bits.TRG1
#define DBGT_TRG2                       _DBGT.Bits.TRG2
#define DBGT_TRG3                       _DBGT.Bits.TRG3
#define DBGT_BEGIN                      _DBGT.Bits.BEGIN
#define DBGT_TRGSEL                     _DBGT.Bits.TRGSEL
#define DBGT_TRG                        _DBGT.MergedBits.grpTRG

#define DBGT_TRG0_MASK                  1
#define DBGT_TRG1_MASK                  2
#define DBGT_TRG2_MASK                  4
#define DBGT_TRG3_MASK                  8
#define DBGT_BEGIN_MASK                 64
#define DBGT_TRGSEL_MASK                128
#define DBGT_TRG_MASK                   15
#define DBGT_TRG_BITNUM                 0


/*** DBGS - Debug Status Register; 0x00001818 ***/
typedef union {
  byte Byte;
  struct {
    byte CNT0        :1;                                       /* FIFO Valid Count Bit 0 */
    byte CNT1        :1;                                       /* FIFO Valid Count Bit 1 */
    byte CNT2        :1;                                       /* FIFO Valid Count Bit 2 */
    byte CNT3        :1;                                       /* FIFO Valid Count Bit 3 */
    byte             :1; 
    byte ARMF        :1;                                       /* Arm Flag */
    byte BF          :1;                                       /* Trigger Match B Flag */
    byte AF          :1;                                       /* Trigger Match A Flag */
  } Bits;
  struct {
    byte grpCNT  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGSSTR;
extern volatile DBGSSTR _DBGS @0x00001818;
#define DBGS                            _DBGS.Byte
#define DBGS_CNT0                       _DBGS.Bits.CNT0
#define DBGS_CNT1                       _DBGS.Bits.CNT1
#define DBGS_CNT2                       _DBGS.Bits.CNT2
#define DBGS_CNT3                       _DBGS.Bits.CNT3
#define DBGS_ARMF                       _DBGS.Bits.ARMF
#define DBGS_BF                         _DBGS.Bits.BF
#define DBGS_AF                         _DBGS.Bits.AF
#define DBGS_CNT                        _DBGS.MergedBits.grpCNT

#define DBGS_CNT0_MASK                  1
#define DBGS_CNT1_MASK                  2
#define DBGS_CNT2_MASK                  4
#define DBGS_CNT3_MASK                  8
#define DBGS_ARMF_MASK                  32
#define DBGS_BF_MASK                    64
#define DBGS_AF_MASK                    128
#define DBGS_CNT_MASK                   15
#define DBGS_CNT_BITNUM                 0


/*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***/
typedef union {
  byte Byte;
  struct {
    byte DIV0        :1;                                       /* Divisor for FLASH Clock Divider Bit 0 */
    byte DIV1        :1;                                       /* Divisor for FLASH Clock Divider Bit 1 */
    byte DIV2        :1;                                       /* Divisor for FLASH Clock Divider Bit 2 */
    byte DIV3        :1;                                       /* Divisor for FLASH Clock Divider Bit 3 */
    byte DIV4        :1;                                       /* Divisor for FLASH Clock Divider Bit 4 */
    byte DIV5        :1;                                       /* Divisor for FLASH Clock Divider Bit 5 */
    byte PRDIV8      :1;                                       /* Prescale (Divide) FLASH Clock by 8 */
    byte DIVLD       :1;                                       /* Divisor Loaded Status Flag */
  } Bits;
  struct {
    byte grpDIV  :6;
    byte grpPRDIV_8 :1;
    byte         :1;
  } MergedBits;
} FCDIVSTR;
extern volatile FCDIVSTR _FCDIV @0x00001820;
#define FCDIV                           _FCDIV.Byte
#define FCDIV_DIV0                      _FCDIV.Bits.DIV0
#define FCDIV_DIV1                      _FCDIV.Bits.DIV1
#define FCDIV_DIV2                      _FCDIV.Bits.DIV2
#define FCDIV_DIV3                      _FCDIV.Bits.DIV3
#define FCDIV_DIV4                      _FCDIV.Bits.DIV4
#define FCDIV_DIV5                      _FCDIV.Bits.DIV5
#define FCDIV_PRDIV8                    _FCDIV.Bits.PRDIV8
#define FCDIV_DIVLD                     _FCDIV.Bits.DIVLD
#define FCDIV_DIV                       _FCDIV.MergedBits.grpDIV

#define FCDIV_DIV0_MASK                 1
#define FCDIV_DIV1_MASK                 2
#define FCDIV_DIV2_MASK                 4
#define FCDIV_DIV3_MASK                 8
#define FCDIV_DIV4_MASK                 16
#define FCDIV_DIV5_MASK                 32
#define FCDIV_PRDIV8_MASK               64
#define FCDIV_DIVLD_MASK                128
#define FCDIV_DIV_MASK                  63
#define FCDIV_DIV_BITNUM                0


/*** FOPT - FLASH Options Register; 0x00001821 ***/
typedef union {
  byte Byte;
  struct {
    byte SEC00       :1;                                       /* Security State Code Bit 0 */
    byte SEC01       :1;                                       /* Security State Code Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte FNORED      :1;                                       /* Vector Redirection Disable */
    byte KEYEN       :1;                                       /* Backdoor Key Mechanism Enable */
  } Bits;
  struct {
    byte grpSEC0 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} FOPTSTR;
extern volatile FOPTSTR _FOPT @0x00001821;
#define FOPT                            _FOPT.Byte
#define FOPT_SEC00                      _FOPT.Bits.SEC00
#define FOPT_SEC01                      _FOPT.Bits.SEC01
#define FOPT_FNORED                     _FOPT.Bits.FNORED
#define FOPT_KEYEN                      _FOPT.Bits.KEYEN
#define FOPT_SEC0                       _FOPT.MergedBits.grpSEC0

#define FOPT_SEC00_MASK                 1
#define FOPT_SEC01_MASK                 2
#define FOPT_FNORED_MASK                64
#define FOPT_KEYEN_MASK                 128
#define FOPT_SEC0_MASK                  3
#define FOPT_SEC0_BITNUM                0


/*** FCNFG - FLASH Configuration Register; 0x00001823 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYACC      :1;                                       /* Enable Writing of Access Key */
    byte             :1; 
    byte             :1; 
  } Bits;
} FCNFGSTR;
extern volatile FCNFGSTR _FCNFG @0x00001823;
#define FCNFG                           _FCNFG.Byte
#define FCNFG_KEYACC                    _FCNFG.Bits.KEYACC

#define FCNFG_KEYACC_MASK               32


/*** FPROT - FLASH Protection Register; 0x00001824 ***/
typedef union {
  byte Byte;
  struct {
    byte FPDIS       :1;                                       /* FLASH Protection Disable */
    byte FPS1        :1;                                       /* FLASH Protect Select Bit 1 */
    byte FPS2        :1;                                       /* FLASH Protect Select Bit 2 */
    byte FPS3        :1;                                       /* FLASH Protect Select Bit 3 */
    byte FPS4        :1;                                       /* FLASH Protect Select Bit 4 */
    byte FPS5        :1;                                       /* FLASH Protect Select Bit 5 */
    byte FPS6        :1;                                       /* FLASH Protect Select Bit 6 */
    byte FPS7        :1;                                       /* FLASH Protect Select Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS_1 :7;
  } MergedBits;
} FPROTSTR;
extern volatile FPROTSTR _FPROT @0x00001824;
#define FPROT                           _FPROT.Byte
#define FPROT_FPDIS                     _FPROT.Bits.FPDIS
#define FPROT_FPS1                      _FPROT.Bits.FPS1
#define FPROT_FPS2                      _FPROT.Bits.FPS2
#define FPROT_FPS3                      _FPROT.Bits.FPS3
#define FPROT_FPS4                      _FPROT.Bits.FPS4
#define FPROT_FPS5                      _FPROT.Bits.FPS5
#define FPROT_FPS6                      _FPROT.Bits.FPS6
#define FPROT_FPS7                      _FPROT.Bits.FPS7
#define FPROT_FPS_1                     _FPROT.MergedBits.grpFPS_1
#define FPROT_FPS                       FPROT_FPS_1

#define FPROT_FPDIS_MASK                1
#define FPROT_FPS1_MASK                 2
#define FPROT_FPS2_MASK                 4
#define FPROT_FPS3_MASK                 8
#define FPROT_FPS4_MASK                 16
#define FPROT_FPS5_MASK                 32
#define FPROT_FPS6_MASK                 64
#define FPROT_FPS7_MASK                 128
#define FPROT_FPS_1_MASK                254
#define FPROT_FPS_1_BITNUM              1


/*** FSTAT - FLASH Status Register; 0x00001825 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte FBLANK      :1;                                       /* FLASH Verified as All Blank (erased) Flag */
    byte             :1; 
    byte FACCERR     :1;                                       /* Access Error Flag */
    byte FPVIOL      :1;                                       /* Protection Violation Flag */
    byte FCCF        :1;                                       /* FLASH Command Complete Flag */
    byte FCBEF       :1;                                       /* FLASH Command Buffer Empty Flag */
  } Bits;
} FSTATSTR;
extern volatile FSTATSTR _FSTAT @0x00001825;
#define FSTAT                           _FSTAT.Byte
#define FSTAT_FBLANK                    _FSTAT.Bits.FBLANK
#define FSTAT_FACCERR                   _FSTAT.Bits.FACCERR
#define FSTAT_FPVIOL                    _FSTAT.Bits.FPVIOL
#define FSTAT_FCCF                      _FSTAT.Bits.FCCF
#define FSTAT_FCBEF                     _FSTAT.Bits.FCBEF

#define FSTAT_FBLANK_MASK               4
#define FSTAT_FACCERR_MASK              16
#define FSTAT_FPVIOL_MASK               32
#define FSTAT_FCCF_MASK                 64
#define FSTAT_FCBEF_MASK                128


/*** FCMD - FLASH Command Register; 0x00001826 ***/
typedef union {
  byte Byte;
  struct {
    byte FCMD0       :1;                                       /* FLASH Command Bit 0 */
    byte FCMD1       :1;                                       /* FLASH Command Bit 1 */
    byte FCMD2       :1;                                       /* FLASH Command Bit 2 */
    byte FCMD3       :1;                                       /* FLASH Command Bit 3 */
    byte FCMD4       :1;                                       /* FLASH Command Bit 4 */
    byte FCMD5       :1;                                       /* FLASH Command Bit 5 */
    byte FCMD6       :1;                                       /* FLASH Command Bit 6 */
    byte FCMD7       :1;                                       /* FLASH Command Bit 7 */
  } Bits;
} FCMDSTR;
extern volatile FCMDSTR _FCMD @0x00001826;
#define FCMD                            _FCMD.Byte
#define FCMD_FCMD0                      _FCMD.Bits.FCMD0
#define FCMD_FCMD1                      _FCMD.Bits.FCMD1
#define FCMD_FCMD2                      _FCMD.Bits.FCMD2
#define FCMD_FCMD3                      _FCMD.Bits.FCMD3
#define FCMD_FCMD4                      _FCMD.Bits.FCMD4
#define FCMD_FCMD5                      _FCMD.Bits.FCMD5
#define FCMD_FCMD6                      _FCMD.Bits.FCMD6
#define FCMD_FCMD7                      _FCMD.Bits.FCMD7

#define FCMD_FCMD0_MASK                 1
#define FCMD_FCMD1_MASK                 2
#define FCMD_FCMD2_MASK                 4
#define FCMD_FCMD3_MASK                 8
#define FCMD_FCMD4_MASK                 16
#define FCMD_FCMD5_MASK                 32
#define FCMD_FCMD6_MASK                 64
#define FCMD_FCMD7_MASK                 128


/*** PTAPE - Pullup Enable for Port A; 0x00001840 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAPE0      :1;                                       /* Pullup Enable for Port A Bit 0 */
    byte PTAPE1      :1;                                       /* Pullup Enable for Port A Bit 1 */
    byte PTAPE2      :1;                                       /* Pullup Enable for Port A Bit 2 */
    byte PTAPE3      :1;                                       /* Pullup Enable for Port A Bit 3 */
    byte PTAPE4      :1;                                       /* Pullup Enable for Port A Bit 4 */
    byte PTAPE5      :1;                                       /* Pullup Enable for Port A Bit 5 */
    byte PTAPE6      :1;                                       /* Pullup Enable for Port A Bit 6 */
    byte PTAPE7      :1;                                       /* Pullup Enable for Port A Bit 7 */
  } Bits;
} PTAPESTR;
extern volatile PTAPESTR _PTAPE @0x00001840;
#define PTAPE                           _PTAPE.Byte
#define PTAPE_PTAPE0                    _PTAPE.Bits.PTAPE0
#define PTAPE_PTAPE1                    _PTAPE.Bits.PTAPE1
#define PTAPE_PTAPE2                    _PTAPE.Bits.PTAPE2
#define PTAPE_PTAPE3                    _PTAPE.Bits.PTAPE3
#define PTAPE_PTAPE4                    _PTAPE.Bits.PTAPE4
#define PTAPE_PTAPE5                    _PTAPE.Bits.PTAPE5
#define PTAPE_PTAPE6                    _PTAPE.Bits.PTAPE6
#define PTAPE_PTAPE7                    _PTAPE.Bits.PTAPE7

#define PTAPE_PTAPE0_MASK               1
#define PTAPE_PTAPE1_MASK               2
#define PTAPE_PTAPE2_MASK               4
#define PTAPE_PTAPE3_MASK               8
#define PTAPE_PTAPE4_MASK               16
#define PTAPE_PTAPE5_MASK               32
#define PTAPE_PTAPE6_MASK               64
#define PTAPE_PTAPE7_MASK               128


/*** PTASE - Slew Rate Control Enable for Port A; 0x00001841 ***/
typedef union {
  byte Byte;
  struct {
    byte PTASE0      :1;                                       /* Slew Rate Control Enable for Port A Bit 0 */
    byte PTASE1      :1;                                       /* Slew Rate Control Enable for Port A Bit 1 */
    byte PTASE2      :1;                                       /* Slew Rate Control Enable for Port A Bit 2 */
    byte PTASE3      :1;                                       /* Slew Rate Control Enable for Port A Bit 3 */
    byte PTASE4      :1;                                       /* Slew Rate Control Enable for Port A Bit 4 */
    byte PTASE5      :1;                                       /* Slew Rate Control Enable for Port A Bit 5 */
    byte PTASE6      :1;                                       /* Slew Rate Control Enable for Port A Bit 6 */
    byte PTASE7      :1;                                       /* Slew Rate Control Enable for Port A Bit 7 */
  } Bits;
} PTASESTR;
extern volatile PTASESTR _PTASE @0x00001841;
#define PTASE                           _PTASE.Byte
#define PTASE_PTASE0                    _PTASE.Bits.PTASE0
#define PTASE_PTASE1                    _PTASE.Bits.PTASE1
#define PTASE_PTASE2                    _PTASE.Bits.PTASE2
#define PTASE_PTASE3                    _PTASE.Bits.PTASE3
#define PTASE_PTASE4                    _PTASE.Bits.PTASE4
#define PTASE_PTASE5                    _PTASE.Bits.PTASE5
#define PTASE_PTASE6                    _PTASE.Bits.PTASE6
#define PTASE_PTASE7                    _PTASE.Bits.PTASE7

#define PTASE_PTASE0_MASK               1
#define PTASE_PTASE1_MASK               2
#define PTASE_PTASE2_MASK               4
#define PTASE_PTASE3_MASK               8
#define PTASE_PTASE4_MASK               16
#define PTASE_PTASE5_MASK               32
#define PTASE_PTASE6_MASK               64
#define PTASE_PTASE7_MASK               128


/*** PTADS - Output Drive Strength Selection for Port A; 0x00001842 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADS0      :1;                                       /* Output Drive Strength Selection for Port A Bit 0 */
    byte PTADS1      :1;                                       /* Output Drive Strength Selection for Port A Bit 1 */
    byte PTADS2      :1;                                       /* Output Drive Strength Selection for Port A Bit 2 */
    byte PTADS3      :1;                                       /* Output Drive Strength Selection for Port A Bit 3 */
    byte PTADS4      :1;                                       /* Output Drive Strength Selection for Port A Bit 4 */
    byte PTADS5      :1;                                       /* Output Drive Strength Selection for Port A Bit 5 */
    byte PTADS6      :1;                                       /* Output Drive Strength Selection for Port A Bit 6 */
    byte PTADS7      :1;                                       /* Output Drive Strength Selection for Port A Bit 7 */
  } Bits;
} PTADSSTR;
extern volatile PTADSSTR _PTADS @0x00001842;
#define PTADS                           _PTADS.Byte
#define PTADS_PTADS0                    _PTADS.Bits.PTADS0
#define PTADS_PTADS1                    _PTADS.Bits.PTADS1
#define PTADS_PTADS2                    _PTADS.Bits.PTADS2
#define PTADS_PTADS3                    _PTADS.Bits.PTADS3
#define PTADS_PTADS4                    _PTADS.Bits.PTADS4
#define PTADS_PTADS5                    _PTADS.Bits.PTADS5
#define PTADS_PTADS6                    _PTADS.Bits.PTADS6
#define PTADS_PTADS7                    _PTADS.Bits.PTADS7

#define PTADS_PTADS0_MASK               1
#define PTADS_PTADS1_MASK               2
#define PTADS_PTADS2_MASK               4
#define PTADS_PTADS3_MASK               8
#define PTADS_PTADS4_MASK               16
#define PTADS_PTADS5_MASK               32
#define PTADS_PTADS6_MASK               64
#define PTADS_PTADS7_MASK               128


/*** PTBPE - Pullup Enable for Port B; 0x00001844 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBPE0      :1;                                       /* Pullup Enable for Port B Bit 0 */
    byte PTBPE1      :1;                                       /* Pullup Enable for Port B Bit 1 */
    byte PTBPE2      :1;                                       /* Pullup Enable for Port B Bit 2 */
    byte PTBPE3      :1;                                       /* Pullup Enable for Port B Bit 3 */
    byte PTBPE4      :1;                                       /* Pullup Enable for Port B Bit 4 */
    byte PTBPE5      :1;                                       /* Pullup Enable for Port B Bit 5 */
    byte PTBPE6      :1;                                       /* Pullup Enable for Port B Bit 6 */
    byte PTBPE7      :1;                                       /* Pullup Enable for Port B Bit 7 */
  } Bits;
} PTBPESTR;
extern volatile PTBPESTR _PTBPE @0x00001844;
#define PTBPE                           _PTBPE.Byte
#define PTBPE_PTBPE0                    _PTBPE.Bits.PTBPE0
#define PTBPE_PTBPE1                    _PTBPE.Bits.PTBPE1
#define PTBPE_PTBPE2                    _PTBPE.Bits.PTBPE2
#define PTBPE_PTBPE3                    _PTBPE.Bits.PTBPE3
#define PTBPE_PTBPE4                    _PTBPE.Bits.PTBPE4
#define PTBPE_PTBPE5                    _PTBPE.Bits.PTBPE5
#define PTBPE_PTBPE6                    _PTBPE.Bits.PTBPE6
#define PTBPE_PTBPE7                    _PTBPE.Bits.PTBPE7

#define PTBPE_PTBPE0_MASK               1
#define PTBPE_PTBPE1_MASK               2
#define PTBPE_PTBPE2_MASK               4
#define PTBPE_PTBPE3_MASK               8
#define PTBPE_PTBPE4_MASK               16
#define PTBPE_PTBPE5_MASK               32
#define PTBPE_PTBPE6_MASK               64
#define PTBPE_PTBPE7_MASK               128


/*** PTBSE - Slew Rate Control Enable for Port B; 0x00001845 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBSE0      :1;                                       /* Slew Rate Control Enable for Port B Bit 0 */
    byte PTBSE1      :1;                                       /* Slew Rate Control Enable for Port B Bit 1 */
    byte PTBSE2      :1;                                       /* Slew Rate Control Enable for Port B Bit 2 */
    byte PTBSE3      :1;                                       /* Slew Rate Control Enable for Port B Bit 3 */
    byte PTBSE4      :1;                                       /* Slew Rate Control Enable for Port B Bit 4 */
    byte PTBSE5      :1;                                       /* Slew Rate Control Enable for Port B Bit 5 */
    byte PTBSE6      :1;                                       /* Slew Rate Control Enable for Port B Bit 6 */
    byte PTBSE7      :1;                                       /* Slew Rate Control Enable for Port B Bit 7 */
  } Bits;
} PTBSESTR;
extern volatile PTBSESTR _PTBSE @0x00001845;
#define PTBSE                           _PTBSE.Byte
#define PTBSE_PTBSE0                    _PTBSE.Bits.PTBSE0
#define PTBSE_PTBSE1                    _PTBSE.Bits.PTBSE1
#define PTBSE_PTBSE2                    _PTBSE.Bits.PTBSE2
#define PTBSE_PTBSE3                    _PTBSE.Bits.PTBSE3
#define PTBSE_PTBSE4                    _PTBSE.Bits.PTBSE4
#define PTBSE_PTBSE5                    _PTBSE.Bits.PTBSE5
#define PTBSE_PTBSE6                    _PTBSE.Bits.PTBSE6
#define PTBSE_PTBSE7                    _PTBSE.Bits.PTBSE7

#define PTBSE_PTBSE0_MASK               1
#define PTBSE_PTBSE1_MASK               2
#define PTBSE_PTBSE2_MASK               4
#define PTBSE_PTBSE3_MASK               8
#define PTBSE_PTBSE4_MASK               16
#define PTBSE_PTBSE5_MASK               32
#define PTBSE_PTBSE6_MASK               64
#define PTBSE_PTBSE7_MASK               128


/*** PTBDS - Output Drive Strength Selection for Port B; 0x00001846 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDS0      :1;                                       /* Output Drive Strength Selection for Port B Bit 0 */
    byte PTBDS1      :1;                                       /* Output Drive Strength Selection for Port B Bit 1 */
    byte PTBDS2      :1;                                       /* Output Drive Strength Selection for Port B Bit 2 */
    byte PTBDS3      :1;                                       /* Output Drive Strength Selection for Port B Bit 3 */
    byte PTBDS4      :1;                                       /* Output Drive Strength Selection for Port B Bit 4 */
    byte PTBDS5      :1;                                       /* Output Drive Strength Selection for Port B Bit 5 */
    byte PTBDS6      :1;                                       /* Output Drive Strength Selection for Port B Bit 6 */
    byte PTBDS7      :1;                                       /* Output Drive Strength Selection for Port B Bit 7 */
  } Bits;
} PTBDSSTR;
extern volatile PTBDSSTR _PTBDS @0x00001846;
#define PTBDS                           _PTBDS.Byte
#define PTBDS_PTBDS0                    _PTBDS.Bits.PTBDS0
#define PTBDS_PTBDS1                    _PTBDS.Bits.PTBDS1
#define PTBDS_PTBDS2                    _PTBDS.Bits.PTBDS2
#define PTBDS_PTBDS3                    _PTBDS.Bits.PTBDS3
#define PTBDS_PTBDS4                    _PTBDS.Bits.PTBDS4
#define PTBDS_PTBDS5                    _PTBDS.Bits.PTBDS5
#define PTBDS_PTBDS6                    _PTBDS.Bits.PTBDS6
#define PTBDS_PTBDS7                    _PTBDS.Bits.PTBDS7

#define PTBDS_PTBDS0_MASK               1
#define PTBDS_PTBDS1_MASK               2
#define PTBDS_PTBDS2_MASK               4
#define PTBDS_PTBDS3_MASK               8
#define PTBDS_PTBDS4_MASK               16
#define PTBDS_PTBDS5_MASK               32
#define PTBDS_PTBDS6_MASK               64
#define PTBDS_PTBDS7_MASK               128


/*** PTCPE - Pullup Enable for Port C; 0x00001848 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCPE0      :1;                                       /* Pullup Enable for Port C Bit 0 */
    byte PTCPE1      :1;                                       /* Pullup Enable for Port C Bit 1 */
    byte PTCPE2      :1;                                       /* Pullup Enable for Port C Bit 2 */
    byte PTCPE3      :1;                                       /* Pullup Enable for Port C Bit 3 */
    byte PTCPE4      :1;                                       /* Pullup Enable for Port C Bit 4 */
    byte PTCPE5      :1;                                       /* Pullup Enable for Port C Bit 5 */
    byte PTCPE6      :1;                                       /* Pullup Enable for Port C Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTCPE :7;
    byte         :1;
  } MergedBits;
} PTCPESTR;
extern volatile PTCPESTR _PTCPE @0x00001848;
#define PTCPE                           _PTCPE.Byte
#define PTCPE_PTCPE0                    _PTCPE.Bits.PTCPE0
#define PTCPE_PTCPE1                    _PTCPE.Bits.PTCPE1
#define PTCPE_PTCPE2                    _PTCPE.Bits.PTCPE2
#define PTCPE_PTCPE3                    _PTCPE.Bits.PTCPE3
#define PTCPE_PTCPE4                    _PTCPE.Bits.PTCPE4
#define PTCPE_PTCPE5                    _PTCPE.Bits.PTCPE5
#define PTCPE_PTCPE6                    _PTCPE.Bits.PTCPE6
#define PTCPE_PTCPE                     _PTCPE.MergedBits.grpPTCPE

#define PTCPE_PTCPE0_MASK               1
#define PTCPE_PTCPE1_MASK               2
#define PTCPE_PTCPE2_MASK               4
#define PTCPE_PTCPE3_MASK               8
#define PTCPE_PTCPE4_MASK               16
#define PTCPE_PTCPE5_MASK               32
#define PTCPE_PTCPE6_MASK               64
#define PTCPE_PTCPE_MASK                127
#define PTCPE_PTCPE_BITNUM              0


/*** PTCSE - Slew Rate Control Enable for Port C; 0x00001849 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCSE0      :1;                                       /* Slew Rate Control Enable for Port C Bit 0 */
    byte PTCSE1      :1;                                       /* Slew Rate Control Enable for Port C Bit 1 */
    byte PTCSE2      :1;                                       /* Slew Rate Control Enable for Port C Bit 2 */
    byte PTCSE3      :1;                                       /* Slew Rate Control Enable for Port C Bit 3 */
    byte PTCSE4      :1;                                       /* Slew Rate Control Enable for Port C Bit 4 */
    byte PTCSE5      :1;                                       /* Slew Rate Control Enable for Port C Bit 5 */
    byte PTCSE6      :1;                                       /* Slew Rate Control Enable for Port C Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTCSE :7;
    byte         :1;
  } MergedBits;
} PTCSESTR;
extern volatile PTCSESTR _PTCSE @0x00001849;
#define PTCSE                           _PTCSE.Byte
#define PTCSE_PTCSE0                    _PTCSE.Bits.PTCSE0
#define PTCSE_PTCSE1                    _PTCSE.Bits.PTCSE1
#define PTCSE_PTCSE2                    _PTCSE.Bits.PTCSE2
#define PTCSE_PTCSE3                    _PTCSE.Bits.PTCSE3
#define PTCSE_PTCSE4                    _PTCSE.Bits.PTCSE4
#define PTCSE_PTCSE5                    _PTCSE.Bits.PTCSE5
#define PTCSE_PTCSE6                    _PTCSE.Bits.PTCSE6
#define PTCSE_PTCSE                     _PTCSE.MergedBits.grpPTCSE

#define PTCSE_PTCSE0_MASK               1
#define PTCSE_PTCSE1_MASK               2
#define PTCSE_PTCSE2_MASK               4
#define PTCSE_PTCSE3_MASK               8
#define PTCSE_PTCSE4_MASK               16
#define PTCSE_PTCSE5_MASK               32
#define PTCSE_PTCSE6_MASK               64
#define PTCSE_PTCSE_MASK                127
#define PTCSE_PTCSE_BITNUM              0


/*** PTCDS - Output Drive Strength Selection for Port C; 0x0000184A ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDS0      :1;                                       /* Output Drive Strength Selection for Port C Bit 0 */
    byte PTCDS1      :1;                                       /* Output Drive Strength Selection for Port C Bit 1 */
    byte PTCDS2      :1;                                       /* Output Drive Strength Selection for Port C Bit 2 */
    byte PTCDS3      :1;                                       /* Output Drive Strength Selection for Port C Bit 3 */
    byte PTCDS4      :1;                                       /* Output Drive Strength Selection for Port C Bit 4 */
    byte PTCDS5      :1;                                       /* Output Drive Strength Selection for Port C Bit 5 */
    byte PTCDS6      :1;                                       /* Output Drive Strength Selection for Port C Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTCDS :7;
    byte         :1;
  } MergedBits;
} PTCDSSTR;
extern volatile PTCDSSTR _PTCDS @0x0000184A;
#define PTCDS                           _PTCDS.Byte
#define PTCDS_PTCDS0                    _PTCDS.Bits.PTCDS0
#define PTCDS_PTCDS1                    _PTCDS.Bits.PTCDS1
#define PTCDS_PTCDS2                    _PTCDS.Bits.PTCDS2
#define PTCDS_PTCDS3                    _PTCDS.Bits.PTCDS3
#define PTCDS_PTCDS4                    _PTCDS.Bits.PTCDS4
#define PTCDS_PTCDS5                    _PTCDS.Bits.PTCDS5
#define PTCDS_PTCDS6                    _PTCDS.Bits.PTCDS6
#define PTCDS_PTCDS                     _PTCDS.MergedBits.grpPTCDS

#define PTCDS_PTCDS0_MASK               1
#define PTCDS_PTCDS1_MASK               2
#define PTCDS_PTCDS2_MASK               4
#define PTCDS_PTCDS3_MASK               8
#define PTCDS_PTCDS4_MASK               16
#define PTCDS_PTCDS5_MASK               32
#define PTCDS_PTCDS6_MASK               64
#define PTCDS_PTCDS_MASK                127
#define PTCDS_PTCDS_BITNUM              0


/*** PTDPE - Pullup Enable for Port D; 0x0000184C ***/
typedef union {
  byte Byte;
  struct {
    byte PTDPE0      :1;                                       /* Pullup Enable for Port D Bit 0 */
    byte PTDPE1      :1;                                       /* Pullup Enable for Port D Bit 1 */
    byte PTDPE2      :1;                                       /* Pullup Enable for Port D Bit 2 */
    byte PTDPE3      :1;                                       /* Pullup Enable for Port D Bit 3 */
    byte PTDPE4      :1;                                       /* Pullup Enable for Port D Bit 4 */
    byte PTDPE5      :1;                                       /* Pullup Enable for Port D Bit 5 */
    byte PTDPE6      :1;                                       /* Pullup Enable for Port D Bit 6 */
    byte PTDPE7      :1;                                       /* Pullup Enable for Port D Bit 7 */
  } Bits;
} PTDPESTR;
extern volatile PTDPESTR _PTDPE @0x0000184C;
#define PTDPE                           _PTDPE.Byte
#define PTDPE_PTDPE0                    _PTDPE.Bits.PTDPE0
#define PTDPE_PTDPE1                    _PTDPE.Bits.PTDPE1
#define PTDPE_PTDPE2                    _PTDPE.Bits.PTDPE2
#define PTDPE_PTDPE3                    _PTDPE.Bits.PTDPE3
#define PTDPE_PTDPE4                    _PTDPE.Bits.PTDPE4
#define PTDPE_PTDPE5                    _PTDPE.Bits.PTDPE5
#define PTDPE_PTDPE6                    _PTDPE.Bits.PTDPE6
#define PTDPE_PTDPE7                    _PTDPE.Bits.PTDPE7

#define PTDPE_PTDPE0_MASK               1
#define PTDPE_PTDPE1_MASK               2
#define PTDPE_PTDPE2_MASK               4
#define PTDPE_PTDPE3_MASK               8
#define PTDPE_PTDPE4_MASK               16
#define PTDPE_PTDPE5_MASK               32
#define PTDPE_PTDPE6_MASK               64
#define PTDPE_PTDPE7_MASK               128


/*** PTDSE - Slew Rate Control Enable for Port D; 0x0000184D ***/
typedef union {
  byte Byte;
  struct {
    byte PTDSE0      :1;                                       /* Slew Rate Control Enable for Port D Bit 0 */
    byte PTDSE1      :1;                                       /* Slew Rate Control Enable for Port D Bit 1 */
    byte PTDSE2      :1;                                       /* Slew Rate Control Enable for Port D Bit 2 */
    byte PTDSE3      :1;                                       /* Slew Rate Control Enable for Port D Bit 3 */
    byte PTDSE4      :1;                                       /* Slew Rate Control Enable for Port D Bit 4 */
    byte PTDSE5      :1;                                       /* Slew Rate Control Enable for Port D Bit 5 */
    byte PTDSE6      :1;                                       /* Slew Rate Control Enable for Port D Bit 6 */
    byte PTDSE7      :1;                                       /* Slew Rate Control Enable for Port D Bit 7 */
  } Bits;
} PTDSESTR;
extern volatile PTDSESTR _PTDSE @0x0000184D;
#define PTDSE                           _PTDSE.Byte
#define PTDSE_PTDSE0                    _PTDSE.Bits.PTDSE0
#define PTDSE_PTDSE1                    _PTDSE.Bits.PTDSE1
#define PTDSE_PTDSE2                    _PTDSE.Bits.PTDSE2
#define PTDSE_PTDSE3                    _PTDSE.Bits.PTDSE3
#define PTDSE_PTDSE4                    _PTDSE.Bits.PTDSE4
#define PTDSE_PTDSE5                    _PTDSE.Bits.PTDSE5
#define PTDSE_PTDSE6                    _PTDSE.Bits.PTDSE6
#define PTDSE_PTDSE7                    _PTDSE.Bits.PTDSE7

#define PTDSE_PTDSE0_MASK               1
#define PTDSE_PTDSE1_MASK               2
#define PTDSE_PTDSE2_MASK               4
#define PTDSE_PTDSE3_MASK               8
#define PTDSE_PTDSE4_MASK               16
#define PTDSE_PTDSE5_MASK               32
#define PTDSE_PTDSE6_MASK               64
#define PTDSE_PTDSE7_MASK               128


/*** PTDDS - Output Drive Strength Selection for Port D; 0x0000184E ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDS0      :1;                                       /* Output Drive Strength Selection for Port D Bit 0 */
    byte PTDDS1      :1;                                       /* Output Drive Strength Selection for Port D Bit 1 */
    byte PTDDS2      :1;                                       /* Output Drive Strength Selection for Port D Bit 2 */
    byte PTDDS3      :1;                                       /* Output Drive Strength Selection for Port D Bit 3 */
    byte PTDDS4      :1;                                       /* Output Drive Strength Selection for Port D Bit 4 */
    byte PTDDS5      :1;                                       /* Output Drive Strength Selection for Port D Bit 5 */
    byte PTDDS6      :1;                                       /* Output Drive Strength Selection for Port D Bit 6 */
    byte PTDDS7      :1;                                       /* Output Drive Strength Selection for Port D Bit 7 */
  } Bits;
} PTDDSSTR;
extern volatile PTDDSSTR _PTDDS @0x0000184E;
#define PTDDS                           _PTDDS.Byte
#define PTDDS_PTDDS0                    _PTDDS.Bits.PTDDS0
#define PTDDS_PTDDS1                    _PTDDS.Bits.PTDDS1
#define PTDDS_PTDDS2                    _PTDDS.Bits.PTDDS2
#define PTDDS_PTDDS3                    _PTDDS.Bits.PTDDS3
#define PTDDS_PTDDS4                    _PTDDS.Bits.PTDDS4
#define PTDDS_PTDDS5                    _PTDDS.Bits.PTDDS5
#define PTDDS_PTDDS6                    _PTDDS.Bits.PTDDS6
#define PTDDS_PTDDS7                    _PTDDS.Bits.PTDDS7

#define PTDDS_PTDDS0_MASK               1
#define PTDDS_PTDDS1_MASK               2
#define PTDDS_PTDDS2_MASK               4
#define PTDDS_PTDDS3_MASK               8
#define PTDDS_PTDDS4_MASK               16
#define PTDDS_PTDDS5_MASK               32
#define PTDDS_PTDDS6_MASK               64
#define PTDDS_PTDDS7_MASK               128


/*** PTEPE - Pullup Enable for Port E; 0x00001850 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEPE0      :1;                                       /* Pullup Enable for Port E Bit 0 */
    byte PTEPE1      :1;                                       /* Pullup Enable for Port E Bit 1 */
    byte PTEPE2      :1;                                       /* Pullup Enable for Port E Bit 2 */
    byte PTEPE3      :1;                                       /* Pullup Enable for Port E Bit 3 */
    byte PTEPE4      :1;                                       /* Pullup Enable for Port E Bit 4 */
    byte PTEPE5      :1;                                       /* Pullup Enable for Port E Bit 5 */
    byte PTEPE6      :1;                                       /* Pullup Enable for Port E Bit 6 */
    byte PTEPE7      :1;                                       /* Pullup Enable for Port E Bit 7 */
  } Bits;
} PTEPESTR;
extern volatile PTEPESTR _PTEPE @0x00001850;
#define PTEPE                           _PTEPE.Byte
#define PTEPE_PTEPE0                    _PTEPE.Bits.PTEPE0
#define PTEPE_PTEPE1                    _PTEPE.Bits.PTEPE1
#define PTEPE_PTEPE2                    _PTEPE.Bits.PTEPE2
#define PTEPE_PTEPE3                    _PTEPE.Bits.PTEPE3
#define PTEPE_PTEPE4                    _PTEPE.Bits.PTEPE4
#define PTEPE_PTEPE5                    _PTEPE.Bits.PTEPE5
#define PTEPE_PTEPE6                    _PTEPE.Bits.PTEPE6
#define PTEPE_PTEPE7                    _PTEPE.Bits.PTEPE7

#define PTEPE_PTEPE0_MASK               1
#define PTEPE_PTEPE1_MASK               2
#define PTEPE_PTEPE2_MASK               4
#define PTEPE_PTEPE3_MASK               8
#define PTEPE_PTEPE4_MASK               16
#define PTEPE_PTEPE5_MASK               32
#define PTEPE_PTEPE6_MASK               64
#define PTEPE_PTEPE7_MASK               128


/*** PTESE - Slew Rate Control Enable for Port E; 0x00001851 ***/
typedef union {
  byte Byte;
  struct {
    byte PTESE0      :1;                                       /* Slew Rate Control Enable for Port E Bit 0 */
    byte PTESE1      :1;                                       /* Slew Rate Control Enable for Port E Bit 1 */
    byte PTESE2      :1;                                       /* Slew Rate Control Enable for Port E Bit 2 */
    byte PTESE3      :1;                                       /* Slew Rate Control Enable for Port E Bit 3 */
    byte PTESE4      :1;                                       /* Slew Rate Control Enable for Port E Bit 4 */
    byte PTESE5      :1;                                       /* Slew Rate Control Enable for Port E Bit 5 */
    byte PTESE6      :1;                                       /* Slew Rate Control Enable for Port E Bit 6 */
    byte PTESE7      :1;                                       /* Slew Rate Control Enable for Port E Bit 7 */
  } Bits;
} PTESESTR;
extern volatile PTESESTR _PTESE @0x00001851;
#define PTESE                           _PTESE.Byte
#define PTESE_PTESE0                    _PTESE.Bits.PTESE0
#define PTESE_PTESE1                    _PTESE.Bits.PTESE1
#define PTESE_PTESE2                    _PTESE.Bits.PTESE2
#define PTESE_PTESE3                    _PTESE.Bits.PTESE3
#define PTESE_PTESE4                    _PTESE.Bits.PTESE4
#define PTESE_PTESE5                    _PTESE.Bits.PTESE5
#define PTESE_PTESE6                    _PTESE.Bits.PTESE6
#define PTESE_PTESE7                    _PTESE.Bits.PTESE7

#define PTESE_PTESE0_MASK               1
#define PTESE_PTESE1_MASK               2
#define PTESE_PTESE2_MASK               4
#define PTESE_PTESE3_MASK               8
#define PTESE_PTESE4_MASK               16
#define PTESE_PTESE5_MASK               32
#define PTESE_PTESE6_MASK               64
#define PTESE_PTESE7_MASK               128


/*** PTEDS - Output Drive Strength Selection for Port E; 0x00001852 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDS0      :1;                                       /* Output Drive Strength Selection for Port E Bit 0 */
    byte PTEDS1      :1;                                       /* Output Drive Strength Selection for Port E Bit 1 */
    byte PTEDS2      :1;                                       /* Output Drive Strength Selection for Port E Bit 2 */
    byte PTEDS3      :1;                                       /* Output Drive Strength Selection for Port E Bit 3 */
    byte PTEDS4      :1;                                       /* Output Drive Strength Selection for Port E Bit 4 */
    byte PTEDS5      :1;                                       /* Output Drive Strength Selection for Port E Bit 5 */
    byte PTEDS6      :1;                                       /* Output Drive Strength Selection for Port E Bit 6 */
    byte PTEDS7      :1;                                       /* Output Drive Strength Selection for Port E Bit 7 */
  } Bits;
} PTEDSSTR;
extern volatile PTEDSSTR _PTEDS @0x00001852;
#define PTEDS                           _PTEDS.Byte
#define PTEDS_PTEDS0                    _PTEDS.Bits.PTEDS0
#define PTEDS_PTEDS1                    _PTEDS.Bits.PTEDS1
#define PTEDS_PTEDS2                    _PTEDS.Bits.PTEDS2
#define PTEDS_PTEDS3                    _PTEDS.Bits.PTEDS3
#define PTEDS_PTEDS4                    _PTEDS.Bits.PTEDS4
#define PTEDS_PTEDS5                    _PTEDS.Bits.PTEDS5
#define PTEDS_PTEDS6                    _PTEDS.Bits.PTEDS6
#define PTEDS_PTEDS7                    _PTEDS.Bits.PTEDS7

#define PTEDS_PTEDS0_MASK               1
#define PTEDS_PTEDS1_MASK               2
#define PTEDS_PTEDS2_MASK               4
#define PTEDS_PTEDS3_MASK               8
#define PTEDS_PTEDS4_MASK               16
#define PTEDS_PTEDS5_MASK               32
#define PTEDS_PTEDS6_MASK               64
#define PTEDS_PTEDS7_MASK               128


/*** PTFPE - Pullup Enable for Port F; 0x00001854 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFPE0      :1;                                       /* Pullup Enable for Port F Bit 0 */
    byte PTFPE1      :1;                                       /* Pullup Enable for Port F Bit 1 */
    byte PTFPE2      :1;                                       /* Pullup Enable for Port F Bit 2 */
    byte PTFPE3      :1;                                       /* Pullup Enable for Port F Bit 3 */
    byte PTFPE4      :1;                                       /* Pullup Enable for Port F Bit 4 */
    byte PTFPE5      :1;                                       /* Pullup Enable for Port F Bit 5 */
    byte PTFPE6      :1;                                       /* Pullup Enable for Port F Bit 6 */
    byte PTFPE7      :1;                                       /* Pullup Enable for Port F Bit 7 */
  } Bits;
} PTFPESTR;
extern volatile PTFPESTR _PTFPE @0x00001854;
#define PTFPE                           _PTFPE.Byte
#define PTFPE_PTFPE0                    _PTFPE.Bits.PTFPE0
#define PTFPE_PTFPE1                    _PTFPE.Bits.PTFPE1
#define PTFPE_PTFPE2                    _PTFPE.Bits.PTFPE2
#define PTFPE_PTFPE3                    _PTFPE.Bits.PTFPE3
#define PTFPE_PTFPE4                    _PTFPE.Bits.PTFPE4
#define PTFPE_PTFPE5                    _PTFPE.Bits.PTFPE5
#define PTFPE_PTFPE6                    _PTFPE.Bits.PTFPE6
#define PTFPE_PTFPE7                    _PTFPE.Bits.PTFPE7

#define PTFPE_PTFPE0_MASK               1
#define PTFPE_PTFPE1_MASK               2
#define PTFPE_PTFPE2_MASK               4
#define PTFPE_PTFPE3_MASK               8
#define PTFPE_PTFPE4_MASK               16
#define PTFPE_PTFPE5_MASK               32
#define PTFPE_PTFPE6_MASK               64
#define PTFPE_PTFPE7_MASK               128


/*** PTFSE - Slew Rate Control Enable for Port F; 0x00001855 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFSE0      :1;                                       /* Slew Rate Control Enable for Port F Bit 0 */
    byte PTFSE1      :1;                                       /* Slew Rate Control Enable for Port F Bit 1 */
    byte PTFSE2      :1;                                       /* Slew Rate Control Enable for Port F Bit 2 */
    byte PTFSE3      :1;                                       /* Slew Rate Control Enable for Port F Bit 3 */
    byte PTFSE4      :1;                                       /* Slew Rate Control Enable for Port F Bit 4 */
    byte PTFSE5      :1;                                       /* Slew Rate Control Enable for Port F Bit 5 */
    byte PTFSE6      :1;                                       /* Slew Rate Control Enable for Port F Bit 6 */
    byte PTFSE7      :1;                                       /* Slew Rate Control Enable for Port F Bit 7 */
  } Bits;
} PTFSESTR;
extern volatile PTFSESTR _PTFSE @0x00001855;
#define PTFSE                           _PTFSE.Byte
#define PTFSE_PTFSE0                    _PTFSE.Bits.PTFSE0
#define PTFSE_PTFSE1                    _PTFSE.Bits.PTFSE1
#define PTFSE_PTFSE2                    _PTFSE.Bits.PTFSE2
#define PTFSE_PTFSE3                    _PTFSE.Bits.PTFSE3
#define PTFSE_PTFSE4                    _PTFSE.Bits.PTFSE4
#define PTFSE_PTFSE5                    _PTFSE.Bits.PTFSE5
#define PTFSE_PTFSE6                    _PTFSE.Bits.PTFSE6
#define PTFSE_PTFSE7                    _PTFSE.Bits.PTFSE7

#define PTFSE_PTFSE0_MASK               1
#define PTFSE_PTFSE1_MASK               2
#define PTFSE_PTFSE2_MASK               4
#define PTFSE_PTFSE3_MASK               8
#define PTFSE_PTFSE4_MASK               16
#define PTFSE_PTFSE5_MASK               32
#define PTFSE_PTFSE6_MASK               64
#define PTFSE_PTFSE7_MASK               128


/*** PTFDS - Output Drive Strength Selection for Port F; 0x00001856 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDS0      :1;                                       /* Output Drive Strength Selection for Port F Bit 0 */
    byte PTFDS1      :1;                                       /* Output Drive Strength Selection for Port F Bit 1 */
    byte PTFDS2      :1;                                       /* Output Drive Strength Selection for Port F Bit 2 */
    byte PTFDS3      :1;                                       /* Output Drive Strength Selection for Port F Bit 3 */
    byte PTFDS4      :1;                                       /* Output Drive Strength Selection for Port F Bit 4 */
    byte PTFDS5      :1;                                       /* Output Drive Strength Selection for Port F Bit 5 */
    byte PTFDS6      :1;                                       /* Output Drive Strength Selection for Port F Bit 6 */
    byte PTFDS7      :1;                                       /* Output Drive Strength Selection for Port F Bit 7 */
  } Bits;
} PTFDSSTR;
extern volatile PTFDSSTR _PTFDS @0x00001856;
#define PTFDS                           _PTFDS.Byte
#define PTFDS_PTFDS0                    _PTFDS.Bits.PTFDS0
#define PTFDS_PTFDS1                    _PTFDS.Bits.PTFDS1
#define PTFDS_PTFDS2                    _PTFDS.Bits.PTFDS2
#define PTFDS_PTFDS3                    _PTFDS.Bits.PTFDS3
#define PTFDS_PTFDS4                    _PTFDS.Bits.PTFDS4
#define PTFDS_PTFDS5                    _PTFDS.Bits.PTFDS5
#define PTFDS_PTFDS6                    _PTFDS.Bits.PTFDS6
#define PTFDS_PTFDS7                    _PTFDS.Bits.PTFDS7

#define PTFDS_PTFDS0_MASK               1
#define PTFDS_PTFDS1_MASK               2
#define PTFDS_PTFDS2_MASK               4
#define PTFDS_PTFDS3_MASK               8
#define PTFDS_PTFDS4_MASK               16
#define PTFDS_PTFDS5_MASK               32
#define PTFDS_PTFDS6_MASK               64
#define PTFDS_PTFDS7_MASK               128


/*** PTGPE - Pullup Enable for Port G; 0x00001858 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGPE0      :1;                                       /* Pullup Enable for Port G Bit 0 */
    byte PTGPE1      :1;                                       /* Pullup Enable for Port G Bit 1 */
    byte PTGPE2      :1;                                       /* Pullup Enable for Port G Bit 2 */
    byte PTGPE3      :1;                                       /* Pullup Enable for Port G Bit 3 */
    byte PTGPE4      :1;                                       /* Pullup Enable for Port G Bit 4 */
    byte PTGPE5      :1;                                       /* Pullup Enable for Port G Bit 5 */
    byte PTGPE6      :1;                                       /* Pullup Enable for Port G Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTGPE :7;
    byte         :1;
  } MergedBits;
} PTGPESTR;
extern volatile PTGPESTR _PTGPE @0x00001858;
#define PTGPE                           _PTGPE.Byte
#define PTGPE_PTGPE0                    _PTGPE.Bits.PTGPE0
#define PTGPE_PTGPE1                    _PTGPE.Bits.PTGPE1
#define PTGPE_PTGPE2                    _PTGPE.Bits.PTGPE2
#define PTGPE_PTGPE3                    _PTGPE.Bits.PTGPE3
#define PTGPE_PTGPE4                    _PTGPE.Bits.PTGPE4
#define PTGPE_PTGPE5                    _PTGPE.Bits.PTGPE5
#define PTGPE_PTGPE6                    _PTGPE.Bits.PTGPE6
#define PTGPE_PTGPE                     _PTGPE.MergedBits.grpPTGPE

#define PTGPE_PTGPE0_MASK               1
#define PTGPE_PTGPE1_MASK               2
#define PTGPE_PTGPE2_MASK               4
#define PTGPE_PTGPE3_MASK               8
#define PTGPE_PTGPE4_MASK               16
#define PTGPE_PTGPE5_MASK               32
#define PTGPE_PTGPE6_MASK               64
#define PTGPE_PTGPE_MASK                127
#define PTGPE_PTGPE_BITNUM              0


/*** PTGSE - Slew Rate Control Enable for Port G; 0x00001859 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGSE0      :1;                                       /* Slew Rate Control Enable for Port G Bit 0 */
    byte PTGSE1      :1;                                       /* Slew Rate Control Enable for Port G Bit 1 */
    byte PTGSE2      :1;                                       /* Slew Rate Control Enable for Port G Bit 2 */
    byte PTGSE3      :1;                                       /* Slew Rate Control Enable for Port G Bit 3 */
    byte PTGSE4      :1;                                       /* Slew Rate Control Enable for Port G Bit 4 */
    byte PTGSE5      :1;                                       /* Slew Rate Control Enable for Port G Bit 5 */
    byte PTGSE6      :1;                                       /* Slew Rate Control Enable for Port G Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTGSE :7;
    byte         :1;
  } MergedBits;
} PTGSESTR;
extern volatile PTGSESTR _PTGSE @0x00001859;
#define PTGSE                           _PTGSE.Byte
#define PTGSE_PTGSE0                    _PTGSE.Bits.PTGSE0
#define PTGSE_PTGSE1                    _PTGSE.Bits.PTGSE1
#define PTGSE_PTGSE2                    _PTGSE.Bits.PTGSE2
#define PTGSE_PTGSE3                    _PTGSE.Bits.PTGSE3
#define PTGSE_PTGSE4                    _PTGSE.Bits.PTGSE4
#define PTGSE_PTGSE5                    _PTGSE.Bits.PTGSE5
#define PTGSE_PTGSE6                    _PTGSE.Bits.PTGSE6
#define PTGSE_PTGSE                     _PTGSE.MergedBits.grpPTGSE

#define PTGSE_PTGSE0_MASK               1
#define PTGSE_PTGSE1_MASK               2
#define PTGSE_PTGSE2_MASK               4
#define PTGSE_PTGSE3_MASK               8
#define PTGSE_PTGSE4_MASK               16
#define PTGSE_PTGSE5_MASK               32
#define PTGSE_PTGSE6_MASK               64
#define PTGSE_PTGSE_MASK                127
#define PTGSE_PTGSE_BITNUM              0


/*** PTGDS - Output Drive Strength Selection for Port G; 0x0000185A ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDS0      :1;                                       /* Output Drive Strength Selection for Port G Bit 0 */
    byte PTGDS1      :1;                                       /* Output Drive Strength Selection for Port G Bit 1 */
    byte PTGDS2      :1;                                       /* Output Drive Strength Selection for Port G Bit 2 */
    byte PTGDS3      :1;                                       /* Output Drive Strength Selection for Port G Bit 3 */
    byte PTGDS4      :1;                                       /* Output Drive Strength Selection for Port G Bit 4 */
    byte PTGDS5      :1;                                       /* Output Drive Strength Selection for Port G Bit 5 */
    byte PTGDS6      :1;                                       /* Output Drive Strength Selection for Port G Bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpPTGDS :7;
    byte         :1;
  } MergedBits;
} PTGDSSTR;
extern volatile PTGDSSTR _PTGDS @0x0000185A;
#define PTGDS                           _PTGDS.Byte
#define PTGDS_PTGDS0                    _PTGDS.Bits.PTGDS0
#define PTGDS_PTGDS1                    _PTGDS.Bits.PTGDS1
#define PTGDS_PTGDS2                    _PTGDS.Bits.PTGDS2
#define PTGDS_PTGDS3                    _PTGDS.Bits.PTGDS3
#define PTGDS_PTGDS4                    _PTGDS.Bits.PTGDS4
#define PTGDS_PTGDS5                    _PTGDS.Bits.PTGDS5
#define PTGDS_PTGDS6                    _PTGDS.Bits.PTGDS6
#define PTGDS_PTGDS                     _PTGDS.MergedBits.grpPTGDS

#define PTGDS_PTGDS0_MASK               1
#define PTGDS_PTGDS1_MASK               2
#define PTGDS_PTGDS2_MASK               4
#define PTGDS_PTGDS3_MASK               8
#define PTGDS_PTGDS4_MASK               16
#define PTGDS_PTGDS5_MASK               32
#define PTGDS_PTGDS6_MASK               64
#define PTGDS_PTGDS_MASK                127
#define PTGDS_PTGDS_BITNUM              0


/*** NVBACKKEY0 - Backdoor Comparison Key 0; 0x0000FFB0 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY0STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY0_INIT @0x0000FFB0 = <NVBACKKEY0_INITVAL>; */
#define _NVBACKKEY0 (*(const NVBACKKEY0STR * __far)0x0000FFB0)
#define NVBACKKEY0                      _NVBACKKEY0.Byte
#define NVBACKKEY0_KEY0                 _NVBACKKEY0.Bits.KEY0
#define NVBACKKEY0_KEY1                 _NVBACKKEY0.Bits.KEY1
#define NVBACKKEY0_KEY2                 _NVBACKKEY0.Bits.KEY2
#define NVBACKKEY0_KEY3                 _NVBACKKEY0.Bits.KEY3
#define NVBACKKEY0_KEY4                 _NVBACKKEY0.Bits.KEY4
#define NVBACKKEY0_KEY5                 _NVBACKKEY0.Bits.KEY5
#define NVBACKKEY0_KEY6                 _NVBACKKEY0.Bits.KEY6
#define NVBACKKEY0_KEY7                 _NVBACKKEY0.Bits.KEY7
/* NVBACKKEY_ARR: Access 8 NVBACKKEYx registers in an array */
#define NVBACKKEY_ARR                   ((volatile byte * __far) &NVBACKKEY0)

#define NVBACKKEY0_KEY0_MASK            1
#define NVBACKKEY0_KEY1_MASK            2
#define NVBACKKEY0_KEY2_MASK            4
#define NVBACKKEY0_KEY3_MASK            8
#define NVBACKKEY0_KEY4_MASK            16
#define NVBACKKEY0_KEY5_MASK            32
#define NVBACKKEY0_KEY6_MASK            64
#define NVBACKKEY0_KEY7_MASK            128


/*** NVBACKKEY1 - Backdoor Comparison Key 1; 0x0000FFB1 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY1STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY1_INIT @0x0000FFB1 = <NVBACKKEY1_INITVAL>; */
#define _NVBACKKEY1 (*(const NVBACKKEY1STR * __far)0x0000FFB1)
#define NVBACKKEY1                      _NVBACKKEY1.Byte
#define NVBACKKEY1_KEY0                 _NVBACKKEY1.Bits.KEY0
#define NVBACKKEY1_KEY1                 _NVBACKKEY1.Bits.KEY1
#define NVBACKKEY1_KEY2                 _NVBACKKEY1.Bits.KEY2
#define NVBACKKEY1_KEY3                 _NVBACKKEY1.Bits.KEY3
#define NVBACKKEY1_KEY4                 _NVBACKKEY1.Bits.KEY4
#define NVBACKKEY1_KEY5                 _NVBACKKEY1.Bits.KEY5
#define NVBACKKEY1_KEY6                 _NVBACKKEY1.Bits.KEY6
#define NVBACKKEY1_KEY7                 _NVBACKKEY1.Bits.KEY7

#define NVBACKKEY1_KEY0_MASK            1
#define NVBACKKEY1_KEY1_MASK            2
#define NVBACKKEY1_KEY2_MASK            4
#define NVBACKKEY1_KEY3_MASK            8
#define NVBACKKEY1_KEY4_MASK            16
#define NVBACKKEY1_KEY5_MASK            32
#define NVBACKKEY1_KEY6_MASK            64
#define NVBACKKEY1_KEY7_MASK            128


/*** NVBACKKEY2 - Backdoor Comparison Key 2; 0x0000FFB2 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY2STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY2_INIT @0x0000FFB2 = <NVBACKKEY2_INITVAL>; */
#define _NVBACKKEY2 (*(const NVBACKKEY2STR * __far)0x0000FFB2)
#define NVBACKKEY2                      _NVBACKKEY2.Byte
#define NVBACKKEY2_KEY0                 _NVBACKKEY2.Bits.KEY0
#define NVBACKKEY2_KEY1                 _NVBACKKEY2.Bits.KEY1
#define NVBACKKEY2_KEY2                 _NVBACKKEY2.Bits.KEY2
#define NVBACKKEY2_KEY3                 _NVBACKKEY2.Bits.KEY3
#define NVBACKKEY2_KEY4                 _NVBACKKEY2.Bits.KEY4
#define NVBACKKEY2_KEY5                 _NVBACKKEY2.Bits.KEY5
#define NVBACKKEY2_KEY6                 _NVBACKKEY2.Bits.KEY6
#define NVBACKKEY2_KEY7                 _NVBACKKEY2.Bits.KEY7

#define NVBACKKEY2_KEY0_MASK            1
#define NVBACKKEY2_KEY1_MASK            2
#define NVBACKKEY2_KEY2_MASK            4
#define NVBACKKEY2_KEY3_MASK            8
#define NVBACKKEY2_KEY4_MASK            16
#define NVBACKKEY2_KEY5_MASK            32
#define NVBACKKEY2_KEY6_MASK            64
#define NVBACKKEY2_KEY7_MASK            128


/*** NVBACKKEY3 - Backdoor Comparison Key 3; 0x0000FFB3 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY3STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY3_INIT @0x0000FFB3 = <NVBACKKEY3_INITVAL>; */
#define _NVBACKKEY3 (*(const NVBACKKEY3STR * __far)0x0000FFB3)
#define NVBACKKEY3                      _NVBACKKEY3.Byte
#define NVBACKKEY3_KEY0                 _NVBACKKEY3.Bits.KEY0
#define NVBACKKEY3_KEY1                 _NVBACKKEY3.Bits.KEY1
#define NVBACKKEY3_KEY2                 _NVBACKKEY3.Bits.KEY2
#define NVBACKKEY3_KEY3                 _NVBACKKEY3.Bits.KEY3
#define NVBACKKEY3_KEY4                 _NVBACKKEY3.Bits.KEY4
#define NVBACKKEY3_KEY5                 _NVBACKKEY3.Bits.KEY5
#define NVBACKKEY3_KEY6                 _NVBACKKEY3.Bits.KEY6
#define NVBACKKEY3_KEY7                 _NVBACKKEY3.Bits.KEY7

#define NVBACKKEY3_KEY0_MASK            1
#define NVBACKKEY3_KEY1_MASK            2
#define NVBACKKEY3_KEY2_MASK            4
#define NVBACKKEY3_KEY3_MASK            8
#define NVBACKKEY3_KEY4_MASK            16
#define NVBACKKEY3_KEY5_MASK            32
#define NVBACKKEY3_KEY6_MASK            64
#define NVBACKKEY3_KEY7_MASK            128


/*** NVBACKKEY4 - Backdoor Comparison Key 4; 0x0000FFB4 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY4STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY4_INIT @0x0000FFB4 = <NVBACKKEY4_INITVAL>; */
#define _NVBACKKEY4 (*(const NVBACKKEY4STR * __far)0x0000FFB4)
#define NVBACKKEY4                      _NVBACKKEY4.Byte
#define NVBACKKEY4_KEY0                 _NVBACKKEY4.Bits.KEY0
#define NVBACKKEY4_KEY1                 _NVBACKKEY4.Bits.KEY1
#define NVBACKKEY4_KEY2                 _NVBACKKEY4.Bits.KEY2
#define NVBACKKEY4_KEY3                 _NVBACKKEY4.Bits.KEY3
#define NVBACKKEY4_KEY4                 _NVBACKKEY4.Bits.KEY4
#define NVBACKKEY4_KEY5                 _NVBACKKEY4.Bits.KEY5
#define NVBACKKEY4_KEY6                 _NVBACKKEY4.Bits.KEY6
#define NVBACKKEY4_KEY7                 _NVBACKKEY4.Bits.KEY7

#define NVBACKKEY4_KEY0_MASK            1
#define NVBACKKEY4_KEY1_MASK            2
#define NVBACKKEY4_KEY2_MASK            4
#define NVBACKKEY4_KEY3_MASK            8
#define NVBACKKEY4_KEY4_MASK            16
#define NVBACKKEY4_KEY5_MASK            32
#define NVBACKKEY4_KEY6_MASK            64
#define NVBACKKEY4_KEY7_MASK            128


/*** NVBACKKEY5 - Backdoor Comparison Key 5; 0x0000FFB5 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY5STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY5_INIT @0x0000FFB5 = <NVBACKKEY5_INITVAL>; */
#define _NVBACKKEY5 (*(const NVBACKKEY5STR * __far)0x0000FFB5)
#define NVBACKKEY5                      _NVBACKKEY5.Byte
#define NVBACKKEY5_KEY0                 _NVBACKKEY5.Bits.KEY0
#define NVBACKKEY5_KEY1                 _NVBACKKEY5.Bits.KEY1
#define NVBACKKEY5_KEY2                 _NVBACKKEY5.Bits.KEY2
#define NVBACKKEY5_KEY3                 _NVBACKKEY5.Bits.KEY3
#define NVBACKKEY5_KEY4                 _NVBACKKEY5.Bits.KEY4
#define NVBACKKEY5_KEY5                 _NVBACKKEY5.Bits.KEY5
#define NVBACKKEY5_KEY6                 _NVBACKKEY5.Bits.KEY6
#define NVBACKKEY5_KEY7                 _NVBACKKEY5.Bits.KEY7

#define NVBACKKEY5_KEY0_MASK            1
#define NVBACKKEY5_KEY1_MASK            2
#define NVBACKKEY5_KEY2_MASK            4
#define NVBACKKEY5_KEY3_MASK            8
#define NVBACKKEY5_KEY4_MASK            16
#define NVBACKKEY5_KEY5_MASK            32
#define NVBACKKEY5_KEY6_MASK            64
#define NVBACKKEY5_KEY7_MASK            128


/*** NVBACKKEY6 - Backdoor Comparison Key 6; 0x0000FFB6 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY6STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY6_INIT @0x0000FFB6 = <NVBACKKEY6_INITVAL>; */
#define _NVBACKKEY6 (*(const NVBACKKEY6STR * __far)0x0000FFB6)
#define NVBACKKEY6                      _NVBACKKEY6.Byte
#define NVBACKKEY6_KEY0                 _NVBACKKEY6.Bits.KEY0
#define NVBACKKEY6_KEY1                 _NVBACKKEY6.Bits.KEY1
#define NVBACKKEY6_KEY2                 _NVBACKKEY6.Bits.KEY2
#define NVBACKKEY6_KEY3                 _NVBACKKEY6.Bits.KEY3
#define NVBACKKEY6_KEY4                 _NVBACKKEY6.Bits.KEY4
#define NVBACKKEY6_KEY5                 _NVBACKKEY6.Bits.KEY5
#define NVBACKKEY6_KEY6                 _NVBACKKEY6.Bits.KEY6
#define NVBACKKEY6_KEY7                 _NVBACKKEY6.Bits.KEY7

#define NVBACKKEY6_KEY0_MASK            1
#define NVBACKKEY6_KEY1_MASK            2
#define NVBACKKEY6_KEY2_MASK            4
#define NVBACKKEY6_KEY3_MASK            8
#define NVBACKKEY6_KEY4_MASK            16
#define NVBACKKEY6_KEY5_MASK            32
#define NVBACKKEY6_KEY6_MASK            64
#define NVBACKKEY6_KEY7_MASK            128


/*** NVBACKKEY7 - Backdoor Comparison Key 7; 0x0000FFB7 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key bits, bit 7 */
  } Bits;
} NVBACKKEY7STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY7_INIT @0x0000FFB7 = <NVBACKKEY7_INITVAL>; */
#define _NVBACKKEY7 (*(const NVBACKKEY7STR * __far)0x0000FFB7)
#define NVBACKKEY7                      _NVBACKKEY7.Byte
#define NVBACKKEY7_KEY0                 _NVBACKKEY7.Bits.KEY0
#define NVBACKKEY7_KEY1                 _NVBACKKEY7.Bits.KEY1
#define NVBACKKEY7_KEY2                 _NVBACKKEY7.Bits.KEY2
#define NVBACKKEY7_KEY3                 _NVBACKKEY7.Bits.KEY3
#define NVBACKKEY7_KEY4                 _NVBACKKEY7.Bits.KEY4
#define NVBACKKEY7_KEY5                 _NVBACKKEY7.Bits.KEY5
#define NVBACKKEY7_KEY6                 _NVBACKKEY7.Bits.KEY6
#define NVBACKKEY7_KEY7                 _NVBACKKEY7.Bits.KEY7

#define NVBACKKEY7_KEY0_MASK            1
#define NVBACKKEY7_KEY1_MASK            2
#define NVBACKKEY7_KEY2_MASK            4
#define NVBACKKEY7_KEY3_MASK            8
#define NVBACKKEY7_KEY4_MASK            16
#define NVBACKKEY7_KEY5_MASK            32
#define NVBACKKEY7_KEY6_MASK            64
#define NVBACKKEY7_KEY7_MASK            128


/*** NVPROT - Nonvolatile FLASH Protection Register; 0x0000FFBD ***/
typedef union {
  byte Byte;
  struct {
    byte FPDIS       :1;                                       /* FLASH Protection Disable */
    byte FPS1        :1;                                       /* FLASH Protect Select Bit 1 */
    byte FPS2        :1;                                       /* FLASH Protect Select Bit 2 */
    byte FPS3        :1;                                       /* FLASH Protect Select Bit 3 */
    byte FPS4        :1;                                       /* FLASH Protect Select Bit 4 */
    byte FPS5        :1;                                       /* FLASH Protect Select Bit 5 */
    byte FPS6        :1;                                       /* FLASH Protect Select Bit 6 */
    byte FPS7        :1;                                       /* FLASH Protect Select Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS_1 :7;
  } MergedBits;
} NVPROTSTR;
/* Tip for register initialization in the user code:  const byte NVPROT_INIT @0x0000FFBD = <NVPROT_INITVAL>; */
#define _NVPROT (*(const NVPROTSTR * __far)0x0000FFBD)
#define NVPROT                          _NVPROT.Byte
#define NVPROT_FPDIS                    _NVPROT.Bits.FPDIS
#define NVPROT_FPS1                     _NVPROT.Bits.FPS1
#define NVPROT_FPS2                     _NVPROT.Bits.FPS2
#define NVPROT_FPS3                     _NVPROT.Bits.FPS3
#define NVPROT_FPS4                     _NVPROT.Bits.FPS4
#define NVPROT_FPS5                     _NVPROT.Bits.FPS5
#define NVPROT_FPS6                     _NVPROT.Bits.FPS6
#define NVPROT_FPS7                     _NVPROT.Bits.FPS7
#define NVPROT_FPS_1                    _NVPROT.MergedBits.grpFPS_1
#define NVPROT_FPS                      NVPROT_FPS_1

#define NVPROT_FPDIS_MASK               1
#define NVPROT_FPS1_MASK                2
#define NVPROT_FPS2_MASK                4
#define NVPROT_FPS3_MASK                8
#define NVPROT_FPS4_MASK                16
#define NVPROT_FPS5_MASK                32
#define NVPROT_FPS6_MASK                64
#define NVPROT_FPS7_MASK                128
#define NVPROT_FPS_1_MASK               254
#define NVPROT_FPS_1_BITNUM             1


/*** NVOPT - Nonvolatile FLASH Options Register; 0x0000FFBF ***/
typedef union {
  byte Byte;
  struct {
    byte SEC00       :1;                                       /* Security State Code Bit 0 */
    byte SEC01       :1;                                       /* Security State Code Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte FNORED      :1;                                       /* Vector Redirection Disable */
    byte KEYEN       :1;                                       /* Backdoor Key Mechanism Enable */
  } Bits;
  struct {
    byte grpSEC0 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} NVOPTSTR;
/* Tip for register initialization in the user code:  const byte NVOPT_INIT @0x0000FFBF = <NVOPT_INITVAL>; */
#define _NVOPT (*(const NVOPTSTR * __far)0x0000FFBF)
#define NVOPT                           _NVOPT.Byte
#define NVOPT_SEC00                     _NVOPT.Bits.SEC00
#define NVOPT_SEC01                     _NVOPT.Bits.SEC01
#define NVOPT_FNORED                    _NVOPT.Bits.FNORED
#define NVOPT_KEYEN                     _NVOPT.Bits.KEYEN
#define NVOPT_SEC0                      _NVOPT.MergedBits.grpSEC0

#define NVOPT_SEC00_MASK                1
#define NVOPT_SEC01_MASK                2
#define NVOPT_FNORED_MASK               64
#define NVOPT_KEYEN_MASK                128
#define NVOPT_SEC0_MASK                 3
#define NVOPT_SEC0_BITNUM               0



/* Flash commands */
#define mBlank                          0x05
#define mByteProg                       0x20
#define mBurstProg                      0x25
#define mMassErase                      0x41
#define mPageErase                      0x40


/***********************************************/
/**   D E P R E C I A T E D   S Y M B O L S   **/
/***********************************************/
/* -----------------------------------------------------------
Exceptions in bit names of timer status and control registers
due to backward compatibility with previous releases */
#define TPM1C0SC_ELSxA    _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELSxB    _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MSxA     _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MSxB     _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CHxIE    _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CHxF     _TPM1C0SC.Bits.CH0F

#define TPM1C1SC_ELSxA    _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELSxB    _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MSxA     _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MSxB     _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CHxIE    _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CHxF     _TPM1C1SC.Bits.CH1F

#define TPM1C2SC_ELSxA    _TPM1C2SC.Bits.ELS2A
#define TPM1C2SC_ELSxB    _TPM1C2SC.Bits.ELS2B
#define TPM1C2SC_MSxA     _TPM1C2SC.Bits.MS2A
#define TPM1C2SC_MSxB     _TPM1C2SC.Bits.MS2B
#define TPM1C2SC_CHxIE    _TPM1C2SC.Bits.CH2IE
#define TPM1C2SC_CHxF     _TPM1C2SC.Bits.CH2F

#define TPM1C3SC_ELSxA    _TPM1C3SC.Bits.ELS3A
#define TPM1C3SC_ELSxB    _TPM1C3SC.Bits.ELS3B
#define TPM1C3SC_MSxA     _TPM1C3SC.Bits.MS3A
#define TPM1C3SC_MSxB     _TPM1C3SC.Bits.MS3B
#define TPM1C3SC_CHxIE    _TPM1C3SC.Bits.CH3IE
#define TPM1C3SC_CHxF     _TPM1C3SC.Bits.CH3F

#define TPM1C4SC_ELSxA    _TPM1C4SC.Bits.ELS4A
#define TPM1C4SC_ELSxB    _TPM1C4SC.Bits.ELS4B
#define TPM1C4SC_MSxA     _TPM1C4SC.Bits.MS4A
#define TPM1C4SC_MSxB     _TPM1C4SC.Bits.MS4B
#define TPM1C4SC_CHxIE    _TPM1C4SC.Bits.CH4IE
#define TPM1C4SC_CHxF     _TPM1C4SC.Bits.CH4F

#define TPM1C5SC_ELSxA    _TPM1C5SC.Bits.ELS5A
#define TPM1C5SC_ELSxB    _TPM1C5SC.Bits.ELS5B
#define TPM1C5SC_MSxA     _TPM1C5SC.Bits.MS5A
#define TPM1C5SC_MSxB     _TPM1C5SC.Bits.MS5B
#define TPM1C5SC_CHxIE    _TPM1C5SC.Bits.CH5IE
#define TPM1C5SC_CHxF     _TPM1C5SC.Bits.CH5F

#define TPM2C0SC_ELSxA    _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELSxB    _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MSxA     _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MSxB     _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CHxIE    _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CHxF     _TPM2C0SC.Bits.CH0F

#define TPM2C1SC_ELSxA    _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELSxB    _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MSxA     _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MSxB     _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CHxIE    _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CHxF     _TPM2C1SC.Bits.CH1F
/* --------------------------------------------------------------------------- */
/* The following symbols were removed, because they were invalid or irrelevant */
/* --------------------------------------------------------------------------- */
/*
 * Follows changes from the database 2.87.149 version */
#define IIC1A_ADDR0                      This_symb_has_been_depreciated
#define IIC1A_ADDR0_BITNUM               This_symb_has_been_depreciated
#define IIC1A_ADDR0_MASK                 This_symb_has_been_depreciated
#define NVPROT_FPS0                      This_symb_has_been_depreciated
#define NVPROT_FPS0_BITNUM               This_symb_has_been_depreciated
#define NVPROT_FPS0_MASK                 This_symb_has_been_depreciated
#define AD1SC1                           ADC1SC1
#define _AD1SC1                          _ADC1SC1
#define AD1SC1_ADCH0                     ADC1SC1_ADCH0
#define AD1SC1_ADCH0_MASK                ADC1SC1_ADCH0_MASK
#define AD1SC1_ADCH1                     ADC1SC1_ADCH1
#define AD1SC1_ADCH1_MASK                ADC1SC1_ADCH1_MASK
#define AD1SC1_ADCH2                     ADC1SC1_ADCH2
#define AD1SC1_ADCH2_MASK                ADC1SC1_ADCH2_MASK
#define AD1SC1_ADCH3                     ADC1SC1_ADCH3
#define AD1SC1_ADCH3_MASK                ADC1SC1_ADCH3_MASK
#define AD1SC1_ADCH4                     ADC1SC1_ADCH4
#define AD1SC1_ADCH4_MASK                ADC1SC1_ADCH4_MASK
#define AD1SC1_ADCO                      ADC1SC1_ADCO
#define AD1SC1_ADCO_MASK                 ADC1SC1_ADCO_MASK
#define AD1SC1_AIEN                      ADC1SC1_AIEN
#define AD1SC1_AIEN_MASK                 ADC1SC1_AIEN_MASK
#define AD1SC1_COCO                      ADC1SC1_COCO
#define AD1SC1_COCO_MASK                 ADC1SC1_COCO_MASK
#define AD1SC2                           ADC1SC2
#define _AD1SC2                          _ADC1SC2
#define AD1SC2_ACFGT                     ADC1SC2_ACFGT
#define AD1SC2_ACFGT_MASK                ADC1SC2_ACFGT_MASK
#define AD1SC2_ACFE                      ADC1SC2_ACFE
#define AD1SC2_ACFE_MASK                 ADC1SC2_ACFE_MASK
#define AD1SC2_ADTRG                     ADC1SC2_ADTRG
#define AD1SC2_ADTRG_MASK                ADC1SC2_ADTRG_MASK
#define AD1SC2_ADACT                     ADC1SC2_ADACT
#define AD1SC2_ADACT_MASK                ADC1SC2_ADACT_MASK
#define AD1RH                            ADC1RH
#define AD1RH_ADR8                       ADC1RH_ADR8
#define AD1RH_ADR8_MASK                  ADC1RH_ADR8_MASK
#define AD1RH_ADR9                       ADC1RH_ADR9
#define AD1RH_ADR9_MASK                  ADC1RH_ADR9_MASK
#define AD1R                             ADC1R
#define _AD1R                            _ADC1R
#define AD1RL                            ADC1RL
#define AD1RL_ADR0                       ADC1RL_ADR0
#define AD1RL_ADR0_MASK                  ADC1RL_ADR0_MASK
#define AD1RL_ADR1                       ADC1RL_ADR1
#define AD1RL_ADR1_MASK                  ADC1RL_ADR1_MASK
#define AD1RL_ADR2                       ADC1RL_ADR2
#define AD1RL_ADR2_MASK                  ADC1RL_ADR2_MASK
#define AD1RL_ADR3                       ADC1RL_ADR3
#define AD1RL_ADR3_MASK                  ADC1RL_ADR3_MASK
#define AD1RL_ADR4                       ADC1RL_ADR4
#define AD1RL_ADR4_MASK                  ADC1RL_ADR4_MASK
#define AD1RL_ADR5                       ADC1RL_ADR5
#define AD1RL_ADR5_MASK                  ADC1RL_ADR5_MASK
#define AD1RL_ADR6                       ADC1RL_ADR6
#define AD1RL_ADR6_MASK                  ADC1RL_ADR6_MASK
#define AD1RL_ADR7                       ADC1RL_ADR7
#define AD1RL_ADR7_MASK                  ADC1RL_ADR7_MASK
#define AD1CVH                           ADC1CVH
#define AD1CVH_ADCV8                     ADC1CVH_ADCV8
#define AD1CVH_ADCV8_MASK                ADC1CVH_ADCV8_MASK
#define AD1CVH_ADCV9                     ADC1CVH_ADCV9
#define AD1CVH_ADCV9_MASK                ADC1CVH_ADCV9_MASK
#define AD1CV                            ADC1CV
#define _AD1CV                           _ADC1CV
#define AD1CVL                           ADC1CVL
#define AD1CVL_ADCV0                     ADC1CVL_ADCV0
#define AD1CVL_ADCV0_MASK                ADC1CVL_ADCV0_MASK
#define AD1CVL_ADCV1                     ADC1CVL_ADCV1
#define AD1CVL_ADCV1_MASK                ADC1CVL_ADCV1_MASK
#define AD1CVL_ADCV2                     ADC1CVL_ADCV2
#define AD1CVL_ADCV2_MASK                ADC1CVL_ADCV2_MASK
#define AD1CVL_ADCV3                     ADC1CVL_ADCV3
#define AD1CVL_ADCV3_MASK                ADC1CVL_ADCV3_MASK
#define AD1CVL_ADCV4                     ADC1CVL_ADCV4
#define AD1CVL_ADCV4_MASK                ADC1CVL_ADCV4_MASK
#define AD1CVL_ADCV5                     ADC1CVL_ADCV5
#define AD1CVL_ADCV5_MASK                ADC1CVL_ADCV5_MASK
#define AD1CVL_ADCV6                     ADC1CVL_ADCV6
#define AD1CVL_ADCV6_MASK                ADC1CVL_ADCV6_MASK
#define AD1CVL_ADCV7                     ADC1CVL_ADCV7
#define AD1CVL_ADCV7_MASK                ADC1CVL_ADCV7_MASK
#define AD1CFG                           ADC1CFG
#define _AD1CFG                          _ADC1CFG
#define AD1CFG_ADICLK0                   ADC1CFG_ADICLK0
#define AD1CFG_ADICLK0_MASK              ADC1CFG_ADICLK0_MASK
#define AD1CFG_ADICLK1                   ADC1CFG_ADICLK1
#define AD1CFG_ADICLK1_MASK              ADC1CFG_ADICLK1_MASK
#define AD1CFG_MODE0                     ADC1CFG_MODE0
#define AD1CFG_MODE0_MASK                ADC1CFG_MODE0_MASK
#define AD1CFG_MODE1                     ADC1CFG_MODE1
#define AD1CFG_MODE1_MASK                ADC1CFG_MODE1_MASK
#define AD1CFG_ADLSMP                    ADC1CFG_ADLSMP
#define AD1CFG_ADLSMP_MASK               ADC1CFG_ADLSMP_MASK
#define AD1CFG_ADIV0                     ADC1CFG_ADIV0
#define AD1CFG_ADIV0_MASK                ADC1CFG_ADIV0_MASK
#define AD1CFG_ADIV1                     ADC1CFG_ADIV1
#define AD1CFG_ADIV1_MASK                ADC1CFG_ADIV1_MASK
#define AD1CFG_ADLPC                     ADC1CFG_ADLPC
#define AD1CFG_ADLPC_MASK                ADC1CFG_ADLPC_MASK
#define AD1CFG_ADICLK                    ADC1CFG_ADICLK
#define AD1CFG_ADICLK_BITNUM             ADC1CFG_ADICLK_BITNUM
#define AD1CFG_ADICLK_MASK               ADC1CFG_ADICLK_MASK
#define AD1CFG_ADIV                      ADC1CFG_ADIV
#define AD1CFG_ADIV_BITNUM               ADC1CFG_ADIV_BITNUM
#define AD1CFG_ADIV_MASK                 ADC1CFG_ADIV_MASK
#define AD1CFG_MODE                      ADC1CFG_MODE
#define AD1CFG_MODE_BITNUM               ADC1CFG_MODE_BITNUM
#define AD1CFG_MODE_MASK                 ADC1CFG_MODE_MASK
#define AD1CVH_ADCV                      ADC1CVH_ADCV
#define AD1CVH_ADCV_8                    ADC1CVH_ADCV_8
#define AD1CVH_ADCV_8_BITNUM             ADC1CVH_ADCV_8_BITNUM
#define AD1CVH_ADCV_8_MASK               ADC1CVH_ADCV_8_MASK
#define AD1RH_ADR                        ADC1RH_ADR
#define AD1RH_ADR_8                      ADC1RH_ADR_8
#define AD1RH_ADR_8_BITNUM               ADC1RH_ADR_8_BITNUM
#define AD1RH_ADR_8_MASK                 ADC1RH_ADR_8_MASK
#define AD1SC1_ADCH                      ADC1SC1_ADCH
#define AD1SC1_ADCH_BITNUM               ADC1SC1_ADCH_BITNUM
#define AD1SC1_ADCH_MASK                 ADC1SC1_ADCH_MASK
#define IIC1A_ADDR_BITNUM                IIC1A_ADDR_1_BITNUM
#define IIC1A_ADDR_MASK                  IIC1A_ADDR_1_MASK
#define NVPROT_FPS_BITNUM                This_symb_has_been_depreciated
#define NVPROT_FPS_MASK                  This_symb_has_been_depreciated

/*
 * Follows changes from the database 2.87.179 version */
#define KBIPE                            KBI1PE
#define KBIPE_KBIPE0                     KBI1PE_KBIPE0
#define KBIPE_KBIPE0_MASK                KBI1PE_KBIPE0_MASK
#define KBIPE_KBIPE1                     KBI1PE_KBIPE1
#define KBIPE_KBIPE1_MASK                KBI1PE_KBIPE1_MASK
#define KBIPE_KBIPE2                     KBI1PE_KBIPE2
#define KBIPE_KBIPE2_MASK                KBI1PE_KBIPE2_MASK
#define KBIPE_KBIPE3                     KBI1PE_KBIPE3
#define KBIPE_KBIPE3_MASK                KBI1PE_KBIPE3_MASK
#define KBIPE_KBIPE4                     KBI1PE_KBIPE4
#define KBIPE_KBIPE4_MASK                KBI1PE_KBIPE4_MASK
#define KBIPE_KBIPE5                     KBI1PE_KBIPE5
#define KBIPE_KBIPE5_MASK                KBI1PE_KBIPE5_MASK
#define KBIPE_KBIPE6                     KBI1PE_KBIPE6
#define KBIPE_KBIPE6_MASK                KBI1PE_KBIPE6_MASK
#define KBIPE_KBIPE7                     KBI1PE_KBIPE7
#define KBIPE_KBIPE7_MASK                KBI1PE_KBIPE7_MASK
#define KBISC                            KBI1SC
#define KBISC_KBIMOD                     KBI1SC_KBIMOD
#define KBISC_KBIMOD_MASK                KBI1SC_KBIMOD_MASK
#define KBISC_KBIE                       KBI1SC_KBIE
#define KBISC_KBIE_MASK                  KBI1SC_KBIE_MASK
#define KBISC_KBACK                      KBI1SC_KBACK
#define KBISC_KBACK_MASK                 KBI1SC_KBACK_MASK
#define KBISC_KBF                        KBI1SC_KBF
#define KBISC_KBF_MASK                   KBI1SC_KBF_MASK
#define KBISC_KBEDG4                     KBI1SC_KBEDG4
#define KBISC_KBEDG4_MASK                KBI1SC_KBEDG4_MASK
#define KBISC_KBEDG5                     KBI1SC_KBEDG5
#define KBISC_KBEDG5_MASK                KBI1SC_KBEDG5_MASK
#define KBISC_KBEDG6                     KBI1SC_KBEDG6
#define KBISC_KBEDG6_MASK                KBI1SC_KBEDG6_MASK
#define KBISC_KBEDG7                     KBI1SC_KBEDG7
#define KBISC_KBEDG7_MASK                KBI1SC_KBEDG7_MASK
#define KBISC_KBEDG_4                    KBI1SC_KBEDG_4
#define KBISC_KBEDG_4_BITNUM             KBI1SC_KBEDG_4_BITNUM
#define KBISC_KBEDG_4_MASK               KBI1SC_KBEDG_4_MASK
#define KBISC_KBEDG                      KBI1SC_KBEDG
#endif
