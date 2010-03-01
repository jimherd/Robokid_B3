//----------------------------------------------------------------------------
//
//                  Robokid
//
//----------------------------------------------------------------------------
//  pwm.c : routines to control PWM signals to motor H-Bridge chips
//  =====
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd            4/08/2008    
//----------------------------------------------------------------------------

#include "global.h"


//***********************************************************************
//** Function:      pwm0_duty
//** 
//** Description:   Sets switch value of given channel on TPM1
//**
//** Parameters:    char chan - PWM channel to change 
//**                int duty  - New switch value
//** Returns:       None
//***********************************************************************
void pwm0_duty(char chan, int duty){
  switch(chan){    
    case 0:  TPM1C0V = duty; break; 
    case 1:  TPM1C1V = duty; break; 
    case 2:  TPM1C2V = duty; break; 
    case 3:  TPM1C3V = duty; break; 
    default: break;
  }
}

//***********************************************************************
//** Function:      pwm1_duty
//** 
//** Description:   Sets switch value of given channel on TPM2
//**
//** Parameters:    char chan - PWM channel to change 
//**                int duty  - New switch value
//** Returns:       None
//***********************************************************************
void pwm1_duty(char chan, int duty){
  switch(chan){    
    case 0:  TPM2C0V = duty; break; 
    case 1:  TPM2C1V = duty; break; 
    default: break;
  }
}