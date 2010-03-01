//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// pindef.h   : definition of used pins
// ========
//
// Chip     MC9S08AW60    64-pins
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008
//                    13/08/08     Added pin list (1->64) + set of spare pins
//----------------------------------------------------------------------------
//
// Pin names

#define BATTERY_VOLTS_PIN   PTB0_AD1P0          // [34][analogue]
#define BUMP_SENSOR_C_PIN   PTD1_AD1P9          // [43][analogue]
#define BUMP_SENSOR_L_PIN   PTD0_AD1P8          // [42][analogue]
#define BUMP_SENSOR_R_PIN   PTD2_KBI1P5_AD1P10  // [46][analogue]
#define BUZZER_PIN          PTF4_TPM2CH0        // [ 8][Output]
#define LED_A_OUT           PTGD_PTGD3          // [48][Output]     PTG3_KBI1P3      
#define LED_B_OUT           PTGD_PTGD2          // [25][Output]     PTG2_KBI1P2
#define LED_C_OUT           PTGD_PTGD1          // [24][Output]     PTG1_KBI1P1
#define LED_D_OUT           PTGD_PTGD0          // [23][Output]     PTG0_KBI1P0   
#define LINE_SENSE_L_PIN    PTB6_AD1P6          // [40][analogue]         
#define LINE_SENSE_R_PIN    PTB7_AD1P7          // [41][analogue]
#define M1_IN1_PIN          PTF0_TPM1CH2        // [ 4][Output]
#define M1_IN2_PIN          PTF1_TPM1CH3        // [ 5][Output]
#define M2_IN1_PIN          PTE2_TPM1CH0        // [15][Output]
#define M2_IN2_PIN          PTE3_TPM1CH1        // [16][Output]  
#define PAD_SW_L_PIN        PTB4_AD1P4          // [38][analogue]
#define PAD_SW_R_PIN        PTB5_AD1P5          // [39][analogue]
#define POT_1_IN_PIN        PTB3_AD1P3          // [37][analogue]
#define POT_2_IN_PIN        PTB2_AD1P2          // [36][analogue]
#define POT_3_IN_PIN        PTB1_AD1P1          // [35][analogue]
#define DISP7SEG_G          PTAD_PTAD0          // [26][Output]     PTA0
#define DISP7SEG_F          PTAD_PTAD1          // [27][Output]     PTA1
#define DISP7SEG_A          PTAD_PTAD2          // [28][Output]     PTA2
#define DISP7SEG_B          PTAD_PTAD3          // [29][Output]     PTA3
#define DISP7SEG_E          PTAD_PTAD4          // [30][Output]     PTA4
#define DISP7SEG_D          PTAD_PTAD5          // [31][Output]     PTA5
#define DISP7SEG_C          PTAD_PTAD6          // [32][Output]     PTA6
#define DISP7SEG_DP         PTAD_PTAD7          // [33][Output]     PTA7 
#define SWITCH1             PTC2_MCLK           // [62][Input]
#define SWITCH2             PTC3_TxD2           // [63][Input]
#define SWITCH3             PTC4                // [ 1][Input]
#define SWITCH4             PTC5_RxD2           // [64][Input] 
#define WHEEL_SENSE_L_PIN   PTD3_KBI1P6_AD1P11  // [47][analogue]
#define WHEEL_SENSE_R_PIN   PTD4_TPM2CLK_AD1P12 // [50][analogue]
#define SEG_A_CTRL          PTCD_PTCD6          // [ 9][Output]     PTC6
#define SEG_B_CTRL          PTFD_PTFD7          // [10][Output]     PTF7
#define REAR_SENSE          PTDD_PTD5           // [51][Analogue]   PTD5/AD1P13

//----------------------------------------------------------------------------
// Pin listing
//
//  Pin  Name               Used     Feature         Description
//  ===  ====               ====     =======         ===========
//   1   PTC4                Y         PTC4          User switch C
//   2   IRQ                 Y         IRQ           right wheel sensor interrupt 
//   3   ~RESET              *
//   4   PTF0/TPM1CH2        Y         TPM1CH2       PWM channel for right motor
//   5   PTF1/TPM1CH3        Y         TPM1CH3       PWM channel for right motor
//   6   PTF2/TPM1CH4        -H
//   7   PTF3/TPM1CH5        -
//   8   PTF4/TPM2CH0        Y         PTF4          PWM for buzzer
//   9   PTC6                Y         PTC6          control of seven segment A
//  10   PTF7                Y         PTF7          control of seven segment B
//  11   PTF5/TPM2CH1        -H
//  12   PTF6                -H
//  13   PTE0/TxD1           Y         TxD1          serial port transmit
//  14   PTE1/RxD1           Y         RxD1          serial port receive
//  15   PTE2/TPM1CH0        Y         TPM1CH0       PWM channel for left motor
//  16   PTE3/TPM1CH1        Y         TPM1CH1       PWM channel for left motor
//  17   PTE4/~SS1           -H                      SPI system select
//  18   PTE5/MISO1          -H                      SPI input
//  19   PTE6/MOSI1          -H                      SPI output
//  20   PTE7/SPSCK          -H                      SPI clock
//  21   Vss                 *
//  22   Vdd                 *
//  23   PTG0/KBI1P0         Y         PTG0          LED D
//  24   PTG1/KBI1P1         Y         PTG1          LED C
//  25   PTG2/KBI1P2         Y         PTG2          LED B
//  26   PTA0                Y         PTA0          7-segment LED g
//  27   PTA1                Y         PTA0          7-segment LED f
//  28   PTA2                Y         PTA0          7-segment LED a
//  29   PTA3                Y         PTA0          7-segment LED b
//  30   PTA4                Y         PTA0          7-segment LED e
//  31   PTA5                Y         PTA0          7-segment LED d
//  32   PTA6                Y         PTA0          7-segment LED c
//  33   PTA7                Y         PTA0          7-segment LED dp
//  34   PTB0/AD1P0          Y         AD1P0         battery voltage
//  35   PTB1/AD1P1          Y         AD1P1         POT 1
//  36   PTB2/AD1P2          Y         AD1P2         POT 2
//  37   PTB3/AD1P3          Y         AD1P3         POT 3
//  38   PTB4/AD1P4          Y         AD1P4         joystick left switch
//  39   PTB5/AD1P5          Y         AD1P5         joystick right switch
//  40   PTB6/AD1P6          Y         AD1P6         left line sensor
//  41   PTB7/AD1P7          Y         AD1P7         right line sensor
//  42   PTD0/AD1P8          Y         AD1P8         front bump sensor 1
//  43   PTD1/AD1P9          Y         AD1P9         front bump sensor 2
//  44   Vddad               *
//  45   Vssad               *
//  46   PTD2/KBI1P5/AD1P10  Y         AD1P10        front bump sensor 3
//  47   PTD3/KBI1P6/AD1P11  Y         KBI1P6        interrupt for left wheel sensor
//  48   PTG3/KBI1P3         Y         PTG3          LED A
//  49   PTG4/KBI1P4         -                          
//  50   PTD4/TPM2CLK/AD1P12 Y         KBI1P4        interrupt for right wheel sensor
//  51   PTD5/AD1P13         Y         AD1P13        rear sensor
//  52   PTD6/TPM1CLK/AD1P14 -  
//  53   PTD7/KBI1P7/AD1P15  Y         PTD7          IR data channel input
//  54   Vrefh               *
//  55   Vrefl               *
//  56   BKGD/MS             *
//  57   PTG5/XTAL           -
//  58   PTG6/EXTAL          -
//  59   Vss                 *
//  60   PTC0/SCL1           -H        SCL1          I2C clock line
//  61   PTC1/SDA1           -H        SDA1          I2C data line
//  62   PTC2/MCLK           Y         PTC2          User switch A
//  63   PTC3/TxD2           Y         PTC3          User switch B
//  64   PTC5/RxD2           Y         PTC5          User switch D
//
//----------------------------------------------------------------------------
// Current spare lines
// ===================
//
//  1. PTF2/TPM1CH4        [ 6]   on header
//  2. PTF3/TPM1CH5        [ 7]
//  3. PTF5/TPM2CH1        [11]   on header
//  4. PTF6                [12]   on header
//  5. PTG4/KBI1P4         [50]   ** place on header ??
//  6. PTD6/TPM1CLK/AD1P14 [49]   ** place on header ??
//  7. PTG5/XTAL           [57]
//  8. PTG6/EXTAL          [58]
//
//----------------------------------------------------------------------------
// Extension header
// ================
//
//  Header pin    Chip pin     Chip function           Description
//  ==========    ========     =============           ===========
//
//       1           21             Vss
//       2           21             Vss
//       3           22             Vdd
//       4           11             PTF5/TPM2CH1
//       5            6             PTF2/TPM1CH4
//       6           12             PTF6
//       7           60             PTC0/SCL1          I2C clock
//       8           14             PTE1/RxD1          serial receive
//       9           61             PTC1/SDA1          I2C data
//      10           13             PTE0/TxD1          serial transmit
//      11           17             PTE4/~SS1          SPI select
//      12           20             PTE7/SPSCK         SPI clock
//      13           18             PTE5/MISO1         SPI data in
//      14           19             PTE6/MOSI1         SPI data out
//
//----------------------------------------------------------------------------
// Analogue channel listing
// ========================
//
//   Channel     Name               Pin      Description
//   =======     ====               ===      ===========
//      0      PTB0/AD1P0            34      Battery voltage
//      1      PTB1/AD1P1            35      POT 1
//      2      PTB2/AD1P2            36      POT 2
//      3      PTB3/AD1P3            37      POT 3
//      4      PTB4/AD1P4            38      joystick left switch
//      5      PTB5/AD1P5            39      joystick right switch
//      6      PTB6/AD1P6            40      left line sensor
//      7      PTB7/AD1P7            41      right line sensor
//      8      PTD0/AD1P8            42      front bump sensor 1
//      9      PTD1/AD1P9            43      front bump sensor 2
//     10      PTD2/KBI1P5/AD1P10    46      front bump sensor 3
//     11      PTD3/KBI1P6/AD1P11    47      (interrupt for left wheel sensor)
//     12      PTD4/TPM2CLK/AD1P12   50      (interrupt for right wheel sensor)
//     13      PTD5/AD1P13           51      rear sensor
//     14      PTD6/TPM1CLK/AD1P14   52      ----
//     15      PTD7/KBI1P7/AD1P15    53      (IR data channel input)
//
//----------------------------------------------------------------------------
// Pin assignment for each of the digitaL I/O ports
//
// PTDA   0     DISP7SEG_G          PTA0                // [26][Output]    
//        1     DISP7SEG_F          PTA1                // [27][Output]
//        2     DISP7SEG_A          PTA2                // [28][Output]
//        3     DISP7SEG_B          PTA3                // [29][Output]
//        4     DISP7SEG_E          PTA4                // [30][Output]
//        5     DISP7SEG_D          PTA5                // [31][Output]
//        6     DISP7SEG_C          PTA6                // [32][Output]
//        7     DISP7SEG_DP         PTA7                // [33][Output]
//
#define     PORTA_DIR       0b11111111 
#define     PORTA_PULLUP    0b00000000
#define     PORTA_SLEWRATE  0b00000000
#define     PORTA_OUT_DRIVE 0b11111111 
#define     PORTA_INIT      0b01010101 
//----------------------------------------------------------------------------
// PTDB   0     BATTERY_VOLTS       PTB0_AD1P0          // [34][analogue]
//        1     POT_3               PTB1_AD1P1          // [35][analogue]
//        2     POT_2               PTB2_AD1P2          // [36][analogue]
//        3     POT_1               PTB3_AD1P3          // [37][analogue]
//        4     PAD_SW_L            PTB4_AD1P4          // [38][analogue]
//        5     PAD_SW_R            PTB5_AD1P5          // [39][analogue]
//        6     LINE_SENSOR_L       PTB6_AD1P6          // [40][analogue]
//        7     LINE_SENSOR_R       PTB7_AD1P7          // [41][analogue]
//
#define     PORTB_DIR           0b00000000
#define     PORTB_PULLUP        0b00000000
#define     PORTB_SLEWRATE      0b00000000
#define     PORTB_OUT_DRIVE     0b11111111  
#define     PORTB_INIT          0b00000000 
#define     PORTB_AD_CHAN_0_7   0b11111111 
//----------------------------------------------------------------------------
// PTDC   0    
//        1
//        2     SWITCH_A            PTC2_MCLK           // [62][Input]
//        3     SWITCH_B            PTC3_TxD2           // [63][Input]
//        4     SWITCH_C            PTC4                // [ 1][Input]
//        5     SWITCH_D            PTC5_RxD2           // [64][Input] 
//        6     SEG_A_CTRL          PTC6                // [ 9][Output]
//
#define     PORTC_DIR       0b01000000
#define     PORTC_PULLUP    0b00111100
#define     PORTC_SLEWRATE  0b00000000
#define     PORTC_OUT_DRIVE 0b11111111   
#define     PORTC_INIT      0b00000000
//----------------------------------------------------------------------------
// PTDD   0     BUMP_SENSOR_L       PTD0_AD1P8          // [42][analogue]
//        1     BUMP_SENSOR_C       PTD1_AD1P9          // [43][analogue]
//        2     BUMP_SENSOR_R       PTD2_KBI1P5_AD1P10  // [46][analogue]
//        3     WHEEL_SENSOR_L      PTD3_KBI1P6_AD1P11  // [47][analogue]
//        4     
//        5     REAR_SENSOR         PTD5/AD1P13         // [51][Analogue]   
//        6
//        7     IR_DATA_IN          PTD7/KBI1P7/AD1P15  // [53][Input]
//
#define     PORTD_DIR           0b00000000
#define     PORTD_PULLUP        0b00000000
#define     PORTD_SLEWRATE      0b00000000
#define     PORTD_OUT_DRIVE     0b11111111 
#define     PORTD_INIT          0b00000000
#define     PORTD_AD_CHAN_8_15  0b00110111   
//----------------------------------------------------------------------------
// PTDE   0                         PTE0/TxD1           // [13][Serial Tx]
//        1                         PTE1/RxD1           // [14][Serial Rx]
//        2     M2_IN1              PTE2_TPM1CH0        // [15][Output]
//        3     M2_IN2              PTE3_TPM1CH1        // [16][Output]  
//        4
//        5
//        6
//        7
//
#define     PORTE_DIR       0b00001100
#define     PORTE_PULLUP    0b00000000
#define     PORTE_SLEWRATE  0b00000000
#define     PORTE_OUT_DRIVE 0b11111111 
#define     PORTE_INIT      0b00000000  
//----------------------------------------------------------------------------
// PTDF   0     M1_IN1              PTF0_TPM1CH2        // [ 4][Output]    
//        1     M1_IN2              PTF1_TPM1CH3        // [ 5][Output]
//        2
//        3
//        4     BUZZER              PTF4_TPM2CH0        // [ 8][Output]
//        5
//        6
//        7     SEG_B_CTRL          PTF7                // [10][Output]
//
#define     PORTF_DIR       0b10010011
#define     PORTF_PULLUP    0b00000000
#define     PORTF_SLEWRATE  0b00000000
#define     PORTF_OUT_DRIVE 0b11111111   
#define     PORTF_INIT      0b00000000
//----------------------------------------------------------------------------
// PTDG   0     LED_D_OUT           PTG0_KBI1P0         // [23][Output]     
//        1     LED_C_OUT           PTG1_KBI1P1         // [24][Output]
//        2     LED_B_OUT           PTG2_KBI1P2         // [25][Output]
//        3     LED_A_OUT           PTG3_KBI1P3         // [48][Output]
//        4     WHEEL_SENSOR_R      PTG4_KBI1P4         // [49][Input]
//        5
//        6 
//
#define     PORTG_DIR       0b00001111
#define     PORTG_PULLUP    0b00000000
#define     PORTG_SLEWRATE  0b00000000
#define     PORTG_OUT_DRIVE 0b11111111 
#define     PORTG_INIT      0b00000000  

