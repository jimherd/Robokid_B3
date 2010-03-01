/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        adc.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Analogue to Digital converter driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "global.h"

//***********************************************************************
//** Function:      get_adc
//** Description:   Gets analogue value for selected channel
//** Parameters:    char chan - Analogue channel to read
//** Returns:       char      - ADC value
//
// Notes
//      Protect from interrupts as an interrupt routine will
//      want to access the analogue channels.
//
//*********************************************************************** 
uint8_t get_adc(a2d_channels_t chan) 
{
uint8_t   adc_value;


    DISABLE_INTERRUPTS;

    ADC1SC1_ADCH = chan;
    while(!ADC1SC1_COCO)
        ;
    adc_value = ADC1RL;
    
    ENABLE_INTERRUPTS;
                   
    return adc_value;
    

}

//----------------------------------------------------------------------------
// interrupt_get_adc : read a/d converter from inside an interrupt routine
// =================
//
// Description
//      The normal 'get_adc' routine disables/enables the interrupt system
//      when it operates.  This is necessary since I want to do some a/d
//      conversions within an interrupt routine.  
//      
uint8_t interrupt_get_adc(a2d_channels_t chan) 
{
    ADC1SC1_ADCH = chan;
    while(!ADC1SC1_COCO)
        ;                   
    return ADC1RL;
}