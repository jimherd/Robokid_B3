//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// sys_defines.h : defines related to the processor
// =============
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd            1/08/2008    
//----------------------------------------------------------------------------

#ifndef __sys_defines_H
#define __sys_defines_H

//----------------------------------------------------------------------------
// Useful MACROS
//
#define     FOREVER     for (;;)
#define     HANG        for (;;)

#define     ENABLE_IRQ_INT      IRQSC_IRQIE = 1
#define     DISABLE_IRQ_INT     IRQSC_IRQIE = 0

#define     IRQ_ACK             IRQSC_IRQACK = 1
#define     KBI_ACK             KBI1SC_KBACK = 1

//----------------------------------------------------------------------------
// Memory definitions
//----------------------------------------------------------------------------
//
#define     PAGE_SIZE           512       // 512 bytes per page (0x200)

//----------------------------------------------------------------------------
// Chip configuration registers
//----------------------------------------------------------------------------
// constant definitions for SOPT register
//
#define     WATCHDOG_EN             0x80
#define     WATCHDOG_DIS            0x00

#define     WATCHDOG_TIMEOUT_LONG   0x40	
#define     WATCHDOG_TIMEOUT_SHORT  0x00

#define     STOP_MODE_EN            0x20
#define     STOP_MODE_DIS           0x00

#define     SOPT_BASE               0x13

//----------------------------------------------------------------------------
// Clock subsystem configuration registers
//----------------------------------------------------------------------------
// constant definitions for ICGC1 register
//
#define		LP_OSC					0x00
#define		HF_OSC					0x80

#define		LF_RANGE				0x00
#define		HF_RANGE				0x40

#define		REFS_OTHER				0x00
#define		REFS_CRYSTAL			0x20

#define		CLKS_SELFCLOCKED		0x00
#define		CLKS_FLL_INTREF			0x08
#define		CLKS_NOFLL_EXTRF		0x10
#define		CLKS_FLL_EXTREF			0x18

#define		OSC_DIS_OFF_STATE		0x00
#define		OSC_EN_OFF_STATE		0x04

#define		LOSS_OF_CLOCK_EN		0x00
#define		LOSS_OF_CLOCK_DIS		0x02 

//----------------------------------------------------------------------------
// constant definitions for ICGC2 register
//
#define		LOSS_OF_LOCK_INT		0x00
#define		LOSS_OF_LOCK_RESET		0x80

#define		FLL_MULT_FACT_4			0x00
#define		FLL_MULT_FACT_6			0x10
#define		FLL_MULT_FACT_8			0x20
#define		FLL_MULT_FACT_10		0x30
#define		FLL_MULT_FACT_12		0x40
#define		FLL_MULT_FACT_14		0x50
#define		FLL_MULT_FACT_16		0x60
#define		FLL_MULT_FACT_18		0x70

#define		LOSS_OF_CLOCK_INT		0x00
#define		LOSS_OF_CLOCK_RESET		0x08

#define		FREQ_DIV_1				0x00
#define		FREQ_DIV_2				0x01
#define		FREQ_DIV_4				0x02
#define		FREQ_DIV_8				0x03
#define		FREQ_DIV_16				0x04
#define		FREQ_DIV_32				0x05
#define		FREQ_DIV_64				0x06
#define		FREQ_DIV_128			0x07

//----------------------------------------------------------------------------
// Power management subsystem configuration registers
//----------------------------------------------------------------------------
// constant definitions for SPMSC1 register
//
#define		LOW_VOLT_DETECT_FLG         0x80
#define		LOW_VOLT_DETECT_ACK         0x40
#define		LOW_VOLT_INT_EN             0x20
#define		LOW_VOLT_DETECT_RESET_EN    0x10
#define		LOW_VOLT_DETECT_STOP_EN     0x08
#define		LOW_VOLT_DETECT_EN          0x04
#define		BANDGAP_BUFFER_EN           0x01

//----------------------------------------------------------------------------
// constant definitions for SPMSC2 register
//
#define		LOW_VOLT_WARN_FLG           0x80
#define		LOW_VOLT_WARN_ACK           0x40
#define		LOW_VOLT_DETECT_VOLT_SEL    0x20
#define		LOW_VOLT_WARN_VOLT_SEL      0x10
#define     PARTIAL_POWERDOWN_FLG       0x08
#define     PARTIAL_POWERDOWN_ACK       0x04
#define     PARTIAL_POWERDOWN_CTRL      0x01

//----------------------------------------------------------------------------
// Real time interrupt subsystem configuration registers
//----------------------------------------------------------------------------
// constant definitions for SRTISC register
//
#define		RTI_FLG             0x80
#define		RTI_ACK             0x40

#define		RTI_CLK_SEL_EXT     0x20
#define		RTI_CLK_SEL_1KHZ    0x00

#define		RTI_INT_EN          0x10
#define		RTI_INT_DIS         0x00

#define		RTI_DEL8MS          0x01
#define		RTI_DEL32MS         0x02
#define		RTI_DEL64MS         0x03
#define		RTI_DEL128MS        0x04
#define		RTI_DEL256MS        0x05
#define		RTI_DEL512MS        0x06
#define		RTI_DEL1024MS       0x07

//----------------------------------------------------------------------------
// Analogue input subsystem configuration registers
//----------------------------------------------------------------------------
// constant definitions for ADC1SC1 register
//
#define     AD_INT_EN           0x40
#define     AD_INT_DIS          0x00

#define     AD_CONT_CONV        0x20
#define     AD_SING_CONV        0x00

#define     AD_CHAN_DIS         0x1F

//----------------------------------------------------------------------------
// constant definitions for ADC1SC2 register
//
#define     AD_CONV_TRIG_HARD   0x40
#define     AD_CONV_TRIG_SOFT   0x00

#define     AD_COMP_FUNC_EN     0x20
#define     AD_COMP_FUNC_DIS    0x00

#define     AD_COMP_LT_EN       0x10
#define     AD_COMP_GT_DIS      0x00

//----------------------------------------------------------------------------
// constant definitions for ADC1CFG register
//
#define     AD_LP_EN            0x80
#define     AD_HS_EN            0x00

#define     AD_CLK_DIV_1        0x00
#define     AD_CLK_DIV_2        0x20
#define     AD_CLK_DIV_4        0x40
#define     AD_CLK_DIV_8        0x60

#define     AD_LONG_SAMPL       0x10
#define     AD_SHORT_SAMPL      0x00

#define     AD_CONV_10BIT       0x08
#define     AD_CONV_8BIT        0x00

#define     AD_CLK_BUSCLK       0x00
#define     AD_CLK_BUSCLK_DIV2  0x01
#define     AD_CLK_ICGERCLK     0x02     // clock from ICG clock subsystem
#define     AD_CLK_ASYNCCLK     0x03

//----------------------------------------------------------------------------
// PWM/timer subsystem configuration registers
//----------------------------------------------------------------------------
// constant definitions for TPMxSC register
//
#define     TPM_OVFL_INT_EN     0x40
#define     TPM_OVFL_INT_DIS    0x00

#define     TPM_CENTR_ALIGN     0x20
#define     TPM_EDGE_ALIGN      0x00

#define     TPM_NO_CLK          0x00
#define     TPM_BUSCLK          0x08
#define     TPM_XCLK            0x10
#define     TPM_EXT_CLK         0x18

#define     TPM_PRESCAL_DIV1    0x00
#define     TPM_PRESCAL_DIV2    0x01
#define     TPM_PRESCAL_DIV4    0x02
#define     TPM_PRESCAL_DIV8    0x03
#define     TPM_PRESCAL_DIV16   0x04
#define     TPM_PRESCAL_DIV32   0x05
#define     TPM_PRESCAL_DIV64   0x06
#define     TPM_PRESCAL_DIV128  0x07

//----------------------------------------------------------------------------
// constant definitions for TPMxCnSC register
//
#define     TPM_INT_EN          0x40
#define     TPM_INT_DIS         0x00

#define     PWM_EDGE_ALIGNED    0x20
#define     PWM_ACT_HIGH_PULSE  0x08 

//----------------------------------------------------------------------------
// constant definitions for IRQSC register
//
#define     IRQ_RISE_EDGE       0x20
#define     IRQ_FALL_EDGE       0x00

#define     IRQ_PIN_EN          0x10
#define     IRQ_PIN_DIS         0x00

#define     IRQ_INT_EN          0x02
#define     IRQ_INT_DIS         0x00

#define     IRQ_EDGE_LEVEL_MODE 0x01
#define     IRQ_EDGE_MODE       0x00

//----------------------------------------------------------------------------
// constant definitions for KBI1SC register
//
#define     KBI_FALL_EDGE_P7    0x00
#define     KBI_RISE_EDGE_P7    0x80
#define     KBI_FALL_EDGE_P6    0x00
#define     KBI_RISE_EDGE_P6    0x40
#define     KBI_FALL_EDGE_P5    0x00
#define     KBI_RISE_EDGE_P5    0x20
#define     KBI_FALL_EDGE_P4    0x00
#define     KBI_RISE_EDGE_P4    0x10

#define     KBI_INT_EN          0x02
#define     KBI_INT_DIS         0x00

#define     KBI_EDGE_LEVEL_MODE 0x01
#define     KBI_EDGE_MODE       0x00

//----------------------------------------------------------------------------
// constant definitions for FCDIV register
//
#define     FC_PRESCALE_8         0x40
#define     FC_PRESCALE_0         0x00

#define     FC_DIV_20MHZ_BUSCLK     12

//----------------------------------------------------------------------------
// constant definitions for FCMD register
//
#define     FC_CMD_BLANK_CHECK      0x05
#define     FC_CMD_BYTE_PROG        0x20
#define     FC_CMD_BURST_BYTE_PROG  0x25
#define     FC_CMD_PAGE_ERASE       0x40
#define     FC_CMD_MASS_ERASE       0x41

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
// Function prototypes
//
void init_mcu(void);

#endif /* __sys_defines_H */

