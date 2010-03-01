//----------------------------------------------------------------------------
//
//                  Robokid
//
//----------------------------------------------------------------------------
// user_display.h    header file 
// ==============
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008    
//----------------------------------------------------------------------------

#ifndef __user_display_H
#define __user_display_H

#include "global.h"


/* MODULE user_display */

#define     FLASH_ON    0x00
#define     FLASH_OFF   0xFF

#define     FAST_FLASH_SPEED    60
#define     SLOW_FLASH_SPEED   120

#define     A_TO_FLASH    0x40
#define     B_TO_FLASH    0x80

#define     CLEAR_DISPLAY     load_display(&zero_display);
//
// display modes for dual 7-segment display
//
enum {
    SEVEN_SEG_A, SEVEN_SEG_B, SEVEN_SEG_AB
};

//
// name indices into 'seven_segment_codes' table.
//
enum {
    SEG_0,SEG_1,SEG_2,SEG_3,SEG_4,SEG_5,SEG_6,SEG_7,SEG_8,SEG_9,
    SEG_A,SEG_C,SEG_E,SEG_F,SEG_H,SEG_I,SEG_L,SEG_O,SEG_P,SEG_S,SEG_U,SEG_Y
};
//
// name of each of the bars in the 7-segment display
//
enum {
    BAR_A, BAR_B, BAR_C, BAR_D, BAR_E, BAR_F, BAR_G, BAR_DP
};
//
// name for each of the 4 lLEDs
//
enum {
    LED_A, LED_B, LED_C, LED_D
};

//
// defnition of some useful seven segment codes
//
#define     CHAR_0          0b01111110        // 0         : [0] 
#define     CHAR_1          0b01001000        // 1         : [1] 
#define     CHAR_2          0b00111101        // 2         : [2]
#define     CHAR_3          0b01101101        // 3         : [3]
#define     CHAR_4          0b01001011        // 4         : [4]
#define     CHAR_5          0b01100111        // 5         : [5]
#define     CHAR_6          0b01110011        // 6
#define     CHAR_7          0b01001100        // 7
#define     CHAR_8          0b01111111        // 8
#define     CHAR_9          0b01001111        // 9
#define     CHAR_A          0b01011111        // A
#define     CHAR_b          0b01110011        // b
#define     CHAR_c          0b00110001        // c
#define     CHAR_C          0b00110110        // C
#define     CHAR_d          0b01111001        // d
#define     CHAR_E          0b00110111        // E
#define     CHAR_e          0b01101111        // E
#define     CHAR_F          0b00010111        // F
#define     CHAR_g          0b01101111        // g
#define     CHAR_h          0b01010011        // h
#define     CHAR_H          0b01011011        // H
#define     CHAR_I          0b01001000        // I
#define     CHAR_i          0b00010000        // i
#define     CHAR_j          0b01111000        // j
#define     CHAR_J          0b01101100        // J
#define     CHAR_k          0b10010011        // k
#define     CHAR_l          0b00010010        // l
#define     CHAR_L          0b00110010        // L
#define     CHAR_m          0b00101010        // m  ???
#define     CHAR_n          0b01010001        // n
#define     CHAR_N          0b01011110        // N
#define     CHAR_O          0b01111110        // O
#define     CHAR_o          0b01110001        // o
#define     CHAR_P          0b00011111        // P
#define     CHAR_Q          0b11111110        // Q
#define     CHAR_r          0b00010001        // r
#define     CHAR_S          0b01100111        // S
#define     CHAR_t          0b00110011        // t
#define     CHAR_u          0b01110000        // u
#define     CHAR_U          0b01111010        // U
#define     CHAR_V          0b01111010        // V
#define     CHAR_W          0b01010100        // W ????
#define     CHAR_X          0b01011011        // X
#define     CHAR_y          0b01001011        // Y 
#define     CHAR_Z          0b00111101        // Z
#define     CHAR__          0b00100000        // _
#define     CHAR_CLR        0b00000000        // clr       : [22]
#define     CHAR_SEGA       0b00000100        // segA      : [23] 
#define     CHAR_SEGB       0b00001000        // segB      : [24] 
#define     CHAR_SEGC       0b01000000        // segC      : [25] 
#define     CHAR_SEGD       0b00100000        // segD      : [26] 
#define     CHAR_SEGE       0b00010000        // segE      : [27]
#define     CHAR_SEGF       0b00000010        // segF      : [28] 
#define     CHAR_SEGG       0b00000001        // segG      : [29]
#define     CHAR_3BARS      0b00100101        // 3 bars    : [30]
#define     CHAR_PT         0b10000000        // .
//                            .cdebafg                                       

//
// data stucture for 2-character 7-segment display
//
typedef struct  {
    uint8_t   mode;      // SEVEN_SEG_A, SEVEN_SEG_B, SEVEN_SEG_AB
    uint8_t   char_count, char_ptr;
    uint8_t   shift_rate, shift_count;
    uint8_t   data_A[16], data_B[16];
} seven_seg_display_t;

//
// function prototypes
// 
void display_init(void);
void show_dual_chars(char B_char, char A_char, uint8_t mode);
void show_char(uint8_t segment_no, uint8_t char_code, uint8_t flash_mode); 
//void display_char(uint8_t  char_code, uint8_t flash_mode);
void display_string(char *string, uint8_t mode);
void load_display(seven_seg_display_t   *display_struct);
void set_seg_bar(uint8_t  bar_code, uint8_t flash_mode);
void clr_seg_bar(uint8_t  bar_code, uint8_t flash_mode);
void set_LED(uint8_t  LED_code, uint8_t flash_mode);
void clr_LED(uint8_t  LED_code);
void push_LED_display(void); 
void pop_LED_display(void); 
void clr_all_LEDs(void);
void set_flash_rate(uint8_t  rate);
void flash_LED(uint8_t  LED_code, uint8_t  count);
void display_number(uint8_t value, uint8_t flash_mode);

/* END user_display */

#endif /* __user_display_H */

