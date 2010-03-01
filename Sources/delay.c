
#include "global.h"

//***********************************************************************
//** Function:      delay_10us
//** 
//** Description:   10uS loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_10us(){
  char n;
  for (n=0;n<14;n++) {
    asm("nop");
    asm("nop");
  }
}

//***********************************************************************
//** Function:      delay_100us
//** 
//** Description:   100uS loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_100us(){
  char n;
  for (n=0;n<141;n++) {
    asm("nop");
    asm("nop");
  }
}

//----------------------------------------------------------------------------
// delay_1ms : Delay one milliseconds
// =========
//
// Parameters
//      none
//
// Notes
//      Uses delay_100us routine
// 
void delay_1ms(void){
  char n;
  for (n=0;n<10;n++) {
    delay_100us();
  }
}

//----------------------------------------------------------------------------
// DelayMs : Delay a number of milliseconds
// =======
//
// Parameters
//      count : number of millisconds in the delay 0->65,000
//
// Notes
//      Function uses the supplied 'Delay100US' routine
//
void DelayMs(uint16_t count) 
{
uint16_t    i;

    if (count == 0) {
        return;
    }
    for (i = 0 ; i < count ; i++) {
        delay_1ms();                   //delay 1 millisecond
    }
    return;
}

//***********************************************************************
//** Function:      delay_1ms
//** 
//** Description:   250ms loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_250ms(){
  char n;
  for (n=0;n<250;n++) {
    delay_1ms();
  }
}



