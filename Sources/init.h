//----------------------------------------------------------------------------
// init.h
// ======
//
//----------------------------------------------------------------------------
//
#ifndef __init_H
#define __init_H

//----------------------------------------------------------------------------
//
// Function prototypes
//
void Init_mcu(void);
void Init_System_Options(void);
void Init_System_Power_Management(void);
void Init_MCLK(void);
void Init_Clock(void);
void Init_RTI(void);
void Init_Dig_IO(void);
void Init_sci(void);
void Init_adc(void);
void Init_pwm(void);
void Init_IRQ(void);
void Init_KBI(void);
void Init_flashio(void); 

#endif /* __init_H */

