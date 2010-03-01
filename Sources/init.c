//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
//  init.c : initialise the chip subsystems
//  ======
//
// Common initialization of the write once registers
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd            3/08/2008    
//----------------------------------------------------------------------------
 
#include "global.h"

//----------------------------------------------------------------------------
//  Init_mcu : initialise the chip subsystems
//  ========
//
// Parameters
//      None
//
// Notes
//      *****

void Init_mcu(void){ 
                                   
    Init_System_Options(); 
    Init_System_Power_Management(); 
    Init_MCLK();                                 
    Init_Clock();
    Init_RTI();
    Init_Dig_IO();
    Init_sci();
    Init_adc();
    Init_pwm();
    Init_IRQ();
    Init_KBI();
    Init_flashio();
}

//----------------------------------------------------------------------------
// Init_Clock : configure chip clock subsystem
// ==========
//
// Parameters
//      None
//
// Notes
//      Set to 40MHz using internal oscillator.
//
//      ICGC1: HGO=0,RANGE=1,REFS=0,CLKS1=0,CLKS0=1,OSCSTEN=1,LOCD=1      ICGC1 = 0x4E; 
//      ICGC2: LOLRE=1,MFD2=1,MFD1=1,MFD0=1,LOCRE=0,RFD2=0,RFD1=0,RFD0=0  ICGC2 = 0xF0;  
//
void Init_Clock(void) 
{                           
    setReg8(ICGC1, (LP_OSC | HF_RANGE | REFS_OTHER | REFS_OTHER | CLKS_FLL_INTREF | OSC_EN_OFF_STATE | LOSS_OF_CLOCK_DIS));                          
	setReg8(ICGC2, (LOSS_OF_LOCK_RESET | FLL_MULT_FACT_18 | LOSS_OF_CLOCK_INT | FREQ_DIV_1));                           
//
//
//  
    ICGTRM = *(unsigned char*far)0xFFBE; /* Initialize ICGTRM register from a non volatile memory */
    while(!ICGS1_LOCK)
        ;                  /* Wait */    
}

//----------------------------------------------------------------------------
// Init_System_Options : configure chip SOPT register
// ===================
//
// Parameters
//      None
//
// Notes
//      SOPT: COPE=0,COPT=1,STOPE=0       SOPT = 0x53; 
//
void Init_System_Options(void) 
{
    setReg8(SOPT, (WATCHDOG_DIS | WATCHDOG_TIMEOUT_LONG | STOP_MODE_DIS | SOPT_BASE));
}

//----------------------------------------------------------------------------
// Init_System_Power_Management : configure power management registers
// ============================
//
// Parameters
//      None
//
// Notes
//      SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=0,BGBE=0    SPMSC1 = 0x18
//      SPMSC2: LVWF=0,LVWACK=0,LVDV=0,LVWV=0,PPDF=0,PPDACK=0,PPDC=0     SPMSC2 = 0x00
//
void Init_System_Power_Management(void) 
{
    setReg8(SPMSC1, (LOW_VOLT_DETECT_RESET_EN | LOW_VOLT_DETECT_STOP_EN));                                      
    setReg8(SPMSC2, 0x00); 
}
 
//----------------------------------------------------------------------------
// Init_MCLK : configure signal MCLK
// =========
//
// Parameters
//      None
//
// Notes
//      SMCLK: MPE=0,MCSEL=0
//
void Init_MCLK(void) 
{
    clrReg8Bits(SMCLK, 0x17);
}

//----------------------------------------------------------------------------
// Init_RTI : configure real-time interrupt subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      Set to use 1kHz internal source to gine 8mS RTI interrupt
//
void Init_RTI(void) {

    setReg8(SRTISC, (RTI_CLK_SEL_1KHZ | RTI_INT_EN | RTI_DEL8MS));       
}

//----------------------------------------------------------------------------
// Init_Dig_IO : configure digital I/O lines
// ===========
//
// Parameters
//      None
//
// Notes
//      the bit patterns for the initialisation are in file "pindef,h"
//
void Init_Dig_IO(void) 
{
//
// set data direction registers
//
    setReg8(PTADD, PORTA_DIR);
    setReg8(PTCDD, PORTC_DIR);
    setReg8(PTEDD, PORTE_DIR);
    setReg8(PTFDD, PORTF_DIR);  
    setReg8(PTGDD, PORTG_DIR);
//
// set pull-up registers
//
    setReg8(PTAPE, PORTA_PULLUP);
    setReg8(PTCPE, PORTC_PULLUP);
    setReg8(PTEPE, PORTE_PULLUP);
    setReg8(PTFPE, PORTF_PULLUP);  
    setReg8(PTGPE, PORTG_PULLUP);
//
// set slewrate control registers
//
    setReg8(PTASE, PORTA_SLEWRATE);
    setReg8(PTBSE, PORTB_SLEWRATE);
    setReg8(PTCSE, PORTC_SLEWRATE);
    setReg8(PTDSE, PORTD_SLEWRATE);
    setReg8(PTESE, PORTE_SLEWRATE);
    setReg8(PTFSE, PORTF_SLEWRATE);  
    setReg8(PTGSE, PORTG_SLEWRATE);
//
// set output drive control registers
//
    setReg8(PTADS, PORTA_OUT_DRIVE);
    setReg8(PTBDS, PORTB_OUT_DRIVE);
    setReg8(PTCDS, PORTC_OUT_DRIVE);
    setReg8(PTDDS, PORTD_OUT_DRIVE);
    setReg8(PTEDS, PORTE_OUT_DRIVE);
    setReg8(PTFDS, PORTF_OUT_DRIVE);  
    setReg8(PTGDS, PORTG_OUT_DRIVE);
//
// initialise outputs
// 
    setReg8(PTAD, PORTA_INIT);
    setReg8(PTCD, PORTC_INIT);
    setReg8(PTED, PORTE_INIT);
    setReg8(PTFD, PORTF_INIT);  
    setReg8(PTGD, PORTG_INIT);       
}

//----------------------------------------------------------------------------
// Init_sci : configure serial I/O subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      Initialises the SCI port for RS232 communication
//      
void Init_sci(void)
{
    SCI1BD = (BUSCLK/16)/BAUD; 	//Set baud based on bus clock
    PTEDD_PTEDD0 = 1;			//Tx pin as output
    PTED_PTED0 = 1;
    SCI1C1 = 0x00;              //RS232 operation
    SCI1C2 = 0x00;
    SCI1C3 = 0x00;
}

//----------------------------------------------------------------------------
// Init_adc : configure analogue input subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      1. enable appropriate analogue input pins
//      2. software trigger, disable compare function
//      3. high speed, clock div 8, short sample, 8-bit conversion and 20MHz busclock input
//      4. disable interrupt, single convert mode, set disable channel input
//
void Init_adc(void)
{
    setReg8(APCTL1, PORTB_AD_CHAN_0_7);     // enable analogue input channels 0 to 7
    setReg8(APCTL2, PORTD_AD_CHAN_8_15);    // enable analogue input channels 8 to 13
    setReg8(APCTL3, 0x00);
//
    setReg8(ADC1SC2, (AD_CONV_TRIG_SOFT | AD_COMP_FUNC_DIS | AD_COMP_GT_DIS));                      // 0x00   
//
    setReg8(ADC1CFG, (AD_HS_EN | AD_CLK_DIV_8 | AD_SHORT_SAMPL | AD_CONV_8BIT | AD_CLK_BUSCLK));    // 0x03
//                                          
    setReg8(ADC1SC1, (AD_INT_DIS | AD_SING_CONV | AD_CHAN_DIS));                                    // 0x1F 
}

//----------------------------------------------------------------------------
// Init_pwm : configure PWM generation subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      
//
void Init_pwm(void){
//
// init of channel 1 : PWM signals for the two DC motors
//                      
    setReg8(TPM1SC, (TPM_NO_CLK));       // Stop and reset counter   0x00

    setReg16(TPM1MOD, PWM_COUNT);        // Period value setting 
    
    setReg16(TPM1C0V, 1000);
    setReg16(TPM1C1V, 1200);
    setReg16(TPM1C2V, 1400);
    setReg16(TPM1C3V, 1600);
    
    setReg8(TPM1C0SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM1C1SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM1C2SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM1C3SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
                   
    setReg8(TPM1SC, (TPM_OVFL_INT_DIS | TPM_EDGE_ALIGN | TPM_BUSCLK | TPM_PRESCAL_DIV1));   
//
// init of channel 2 : PWM signals for system buzzer
//   
    setReg8(TPM2SC, (TPM_NO_CLK));       // Stop and reset counter   0x00

    setReg16(TPM2MOD, C_COUNT);
    
    setReg16(TPM2C0V, 0);
    setReg16(TPM2C1V, 0);
    setReg8(TPM2C0SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM2C1SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
 
    setReg8(TPM2SC, (TPM_OVFL_INT_DIS | TPM_EDGE_ALIGN | TPM_BUSCLK | TPM_PRESCAL_DIV4));         
}

//----------------------------------------------------------------------------
// Init_IRQ : configure chip IRQ input interrupt subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      Set IRQ to give interrupt on a rising edge
//
void Init_IRQ(void) 
{
    setReg8(IRQSC, (IRQ_EDGE_MODE |IRQ_RISE_EDGE | IRQ_PIN_EN | IRQ_INT_EN));       
}

//----------------------------------------------------------------------------
// Init_KBI : configure chip keyboard interrupt subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      Set IRQ to give interrupt on a rising edge
//
void Init_KBI(void) 
{
    setReg8(KBI1SC, (KBI_FALL_EDGE_P6 | KBI_INT_EN | KBI_EDGE_MODE)); 
    KBI1PE_KBIPE6 = 1;         
}

//----------------------------------------------------------------------------
// Init_flashio : configure flash subsystem to allow erase/write commands
// ============
//
// Parameters
//      None
//
// Notes
//      Set parameters to give a flash clock of approx 200k from the busclk.
//
void Init_flashio(void) {  
    setReg8(FCDIV, (FC_PRESCALE_8 | FC_DIV_20MHZ_BUSCLK));
}                                                                  