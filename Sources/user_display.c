
/* MODULE user_display */

#include "global.h"

//----------------------------------------------------------------------------
//  global variables
//
uint8_t     LED_image, LED_state, display_image, swap_image, LED_flash_map, display_flash_mode, flash_count;

uint8_t     LED_store[6][2], LED_store_pt;

seven_seg_display_t    robot_display, temp_display;

//----------------------------------------------------------------------------
// set of common 7-segment patterns
//
#pragma INTO_ROM
const uint8_t char_to_7seg[128] = {
    CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,   // 0  ->7
    CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,   // 8  ->15
    CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,   // 16 ->23
    CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,   // 24 ->31
    CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,   // 32 ->39
    CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_SEGG,CHAR_PT ,CHAR_CLR,   // 40 ->47
    CHAR_0  ,CHAR_1  ,CHAR_2  ,CHAR_3  ,CHAR_4  ,CHAR_5  ,CHAR_6  ,CHAR_7  ,   // 48 ->55
    CHAR_8  ,CHAR_9  ,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,   // 56 ->63
    CHAR_CLR,CHAR_A  ,CHAR_b  ,CHAR_C  ,CHAR_d  ,CHAR_E  ,CHAR_F  ,CHAR_g  ,   // 64 ->71
    CHAR_H  ,CHAR_I  ,CHAR_J  ,CHAR_CLR,CHAR_L  ,CHAR_CLR,CHAR_N,  CHAR_O  ,   // 72 ->79
    CHAR_P  ,CHAR_CLR,CHAR_r  ,CHAR_S  ,CHAR_t  ,CHAR_U  ,CHAR_CLR,CHAR_CLR,   // 80 ->87
    CHAR_CLR,CHAR_y  ,CHAR_Z  ,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_SEGA,CHAR__  ,  // 88 ->95
    CHAR_CLR,CHAR_A  ,CHAR_b  ,CHAR_c  ,CHAR_d  ,CHAR_E  ,CHAR_F  ,CHAR_g  ,   // 96 ->103
    CHAR_h  ,CHAR_i  ,CHAR_j  ,CHAR_k  ,CHAR_l  ,CHAR_CLR,CHAR_n  ,CHAR_o  ,   // 104->111
    CHAR_P  ,CHAR_CLR,CHAR_r  ,CHAR_S  ,CHAR_t  ,CHAR_u  ,CHAR_CLR,CHAR_CLR,   // 112->119
    CHAR_CLR,CHAR_y  ,CHAR_Z  ,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR,CHAR_CLR    // 120->127
};



//----------------------------------------------------------------------------
// display_init : initialise the vehicle displays
// ============
//
void display_init(void) 
{
    SEG_A_CTRL = 0; SEG_B_CTRL = 1;
    set_flash_rate(FAST_FLASH_SPEED);
    display_flash_mode = FLASH_OFF;
    LED_flash_map = 0;
    LED_state = 0;
    LED_flash_map = 0b00000000;
//    display_char(CHAR_CLR, FLASH_OFF);
    clr_LED(LED_A);
    clr_LED(LED_B);
    clr_LED(LED_C);
    clr_LED(LED_D);
    LED_store_pt = 0;
    CLEAR_DISPLAY;        
}

//----------------------------------------------------------------------------
// load_display : copy a display structure to the active 7-segment dispay structure
// ============
//
// Parameters
//      display_struct : pointer to a 7-segment display structure
//
// Description
//      Copy an pre-prepared 7-segment display structure into the working display 
//      structure. Most likely, the pre-prepared structure will be held in ROM
//      space. 
//
void load_display(seven_seg_display_t   *display_struct) 
{
    memcpy(&robot_display, display_struct, sizeof(seven_seg_display_t));
}

//----------------------------------------------------------------------------
// show_dual_chars : output a two character to the 7-segment displays
// ===============
//
// Parameters
//      A_char : Character for B display
//      B_char : Character for A display
//      mode   : bits 0-5 : flash rate of display in units of 64mS
//               bit 6    : if a 1 then flash A character
//               bit 7    : if a 1 then flash B character
//
void show_dual_chars(char B_char, char A_char, uint8_t mode) 
{
    robot_display.char_count = 2;
    robot_display.data_A[0] = char_to_7seg[A_char];
    if ((mode & A_TO_FLASH) == A_TO_FLASH) {
        robot_display.data_A[1] = CHAR_CLR;
    } else {
        robot_display.data_A[1] = char_to_7seg[A_char];
    }
    robot_display.data_B[0] = char_to_7seg[B_char];
    if ((mode & B_TO_FLASH) == B_TO_FLASH) {
        robot_display.data_B[1] = CHAR_CLR;
    } else {
        robot_display.data_B[1] = char_to_7seg[B_char];
    }    
    robot_display.shift_rate = (mode & 0x3F) << 3;
    robot_display.char_ptr = 0;
    return;
}

//----------------------------------------------------------------------------
// show_char : output a single character to one of the 7-segment displays
// =========
//
// Parameters
//      segment_no : SEVEN_SEG_A or SEVEN_SEG_B
//      char_code  : seven segment code for character
//      flash_mode : request for character to flash
//
void show_char(uint8_t segment_no, uint8_t char_code, uint8_t flash_mode) 
{
    robot_display.char_count = 2;
    if (segment_no == SEVEN_SEG_A) {
        robot_display.data_A[0] = char_code;
        if (flash_mode == FLASH_ON) {
            robot_display.data_A[1] = CHAR_CLR;
        } else {
            robot_display.data_A[1] = char_code;
        }
    } else {
        robot_display.data_B[0] = char_code;
        if (flash_mode == FLASH_ON) {
            robot_display.data_B[1] = CHAR_CLR;
        } else {
            robot_display.data_B[1] = char_code;
        }
    }
    return;
}

//----------------------------------------------------------------------------
// display_char : output a single character to the 7-segment display
// ============
//
// Parameters
//      char_code  : binary code of available character
//      display_no : SEVEN_SEG_A or SEVEN_SEG_B
//
//void display_char(uint8_t  char_code, uint8_t display_no) 
//{
//    display_image = seven_segment_codes[char_code];
//    if (display_no == SEVEN_SEG_A) {
//        SEG_A_CTRL = 1; SEG_B_CTRL = 0;
//    } else {
//        SEG_A_CTRL = 0; SEG_B_CTRL = 1;
//    }
//    PTAD = display_image;
//}

//----------------------------------------------------------------------------
// display_string : output a string to the 7-segment display
// ==============
//
// Notes
//      Populate the scroll display data structure from a given ASCII string
// Parameters
//      string   : pointer to NULL terminated ASCII string 
//      mode     : scroll rate
//
void display_string(char *string, uint8_t mode)
{
uint8_t  chr_count;

    temp_display.mode = SEVEN_SEG_AB;
    temp_display.data_B[0] =  CHAR_CLR;
    for (chr_count = 0 ; (*string != '\0') ; string++) {
        temp_display.data_A[chr_count] = char_to_7seg[*string];
        chr_count++;
        temp_display.data_B[chr_count] = char_to_7seg[*string];
    }
    temp_display.data_A[chr_count] = CHAR_CLR;
    temp_display.char_count = chr_count + 1;
    temp_display.shift_rate = 80;
//
//  now copy temp to actual display data structure
//
    memcpy(&robot_display, &temp_display, sizeof(seven_seg_display_t));
}

//----------------------------------------------------------------------------
// set_seg_bar : set one of the bars in the 7-segment display
// ===========
//
// Parameters
//      bar_code : bar name - BAR_A ... BAR_G
//
// Notes
//      The display for VERSION B is the invert of VERSION A
//
void set_seg_bar(uint8_t  bar_code, uint8_t flash_mode) 
{
  #ifdef  VERSION_A
    switch(bar_code) {      
        case BAR_A :
            DISP7SEG_A = 0;
            display_image &= 0b11111011;
            break;
        case BAR_B :
            DISP7SEG_B = 0;
            display_image &= 0b11110111;
            break;           
        case BAR_C :
            DISP7SEG_C = 0;
            display_image &= 0b10111111;
            break;       
        case BAR_D :
            DISP7SEG_D = 0;
            display_image &= 0b11011111;
            break;       
        case BAR_E :
            DISP7SEG_E = 0;
            display_image &= 0b11101111;
            break;   
        case BAR_F :
            DISP7SEG_F = 0;
            display_image &= 0b11111101;
            break;   
        case BAR_G : 
            DISP7SEG_G = 0;
            display_image &= 0b11111110;
            break;
        case BAR_DP :
            DISP7SEG_DP = 0;
            display_image &= 0b10000000;
            break;              
        default :
            break;
        }
  #else
    switch(bar_code) {      
        case BAR_A :
            DISP7SEG_A = 0;
            display_image |= 0b00000100;
            break;
        case BAR_B :
            DISP7SEG_B = 0;
            display_image |= 0b00001000;
            break;           
        case BAR_C :
            DISP7SEG_C = 0;
            display_image |= 0b01000000;
            break;       
        case BAR_D :
            DISP7SEG_D = 0;
            display_image |= 0b00100000;
            break;       
        case BAR_E :
            DISP7SEG_E = 0;
            display_image |= 0b00010000;
            break;   
        case BAR_F :
            DISP7SEG_F = 0;
            display_image |= 0b00000010;
            break;   
        case BAR_G : 
            DISP7SEG_G = 0;
            display_image |= 0b00000001;
            break;
        case BAR_DP :
            DISP7SEG_DP = 0;
            display_image |= 0b10000000;
            break;              
        default :
            break;
        }      
    #endif
    display_flash_mode = flash_mode;
}

//----------------------------------------------------------------------------
// clr_seg_bar : clear one of the bars in the 7-segment display
// ===========
//
// Parameters
//      bar_code : bar name - BAR_A ... BAR_G
//
// Notes
//      Display is inverted
//
void clr_seg_bar(uint8_t  bar_code, uint8_t flash_mode) 
{
    switch(bar_code) {
        case BAR_A :
            DISP7SEG_A = 1;
            display_image |= 0b00000100;
            break;
        case BAR_B :
            DISP7SEG_B = 1;
            display_image |= 0b00001000;
            break;           
        case BAR_C :
            DISP7SEG_C = 1;
            display_image |= 0b01000000;
            break;       
        case BAR_D :
            DISP7SEG_D = 1;
            display_image |= 0b00100000;
            break;       
        case BAR_E :
            DISP7SEG_E = 1;
            display_image |= 0b00010000;
            break;   
        case BAR_F :
            DISP7SEG_F = 1;
            display_image |= 0b00000010;
            break;   
        case BAR_G :
            DISP7SEG_G = 1;
            display_image |= 0b00000001;
            break;
        case BAR_DP :
            DISP7SEG_DP = 1;
            display_image |= 0b10000000;
            break;        
        default :
            break;
        }
    display_flash_mode = flash_mode;
}

//----------------------------------------------------------------------------
// set_LED : set one of the four LED indicators
// =======
//
// Parameters
//      LED_code : LED1, LED2, LED3, LED4
//
void set_LED(uint8_t  LED_code, uint8_t flash_mode) 
{
    switch(LED_code) {
        case LED_A :
            LED_A_OUT = 1; // LED_A_SetVal();
            LED_image |= 0b00001000;
            LED_state |= 0b00001000;
            if (flash_mode == FLASH_ON) {
                LED_flash_map |= 0b00001000;
            }
            break;
        case LED_B :
            LED_B_OUT = 1; // LED_B_SetVal();
            LED_image |= 0b00000100;
            LED_state |= 0b00000100;
            if (flash_mode == FLASH_ON) {
                LED_flash_map |= 0b00000100;
            }
            break;
        case LED_C :
            LED_C_OUT = 1; // LED_C_SetVal();
            LED_image |= 0b00000010;
            LED_state |= 0b00000010;
            if (flash_mode == FLASH_ON) {
                LED_flash_map |= 0b00000010;
            }
            break;
        case LED_D :
            LED_D_OUT = 1; // LED_D_SetVal();
            LED_image |= 0b00000001;
            LED_state |= 0b00000001;
            if (flash_mode == FLASH_ON) {
                LED_flash_map |= 0b00000001;
            }
            break;
    }
}

//----------------------------------------------------------------------------
// clr_LED : clear one of the four LED indicators
// =======
//
// Parameters
//      LED_code : LED1, LED2, LED3, LED4
//
// Notes
//      Also clear associated flash bit 
//
void clr_LED(uint8_t  LED_code) 
{
    switch(LED_code) {
        case LED_A :
            LED_A_OUT = 0; // LED_A_ClrVal();
            LED_image &= 0b11110111;
            LED_state &= 0b11110111;
            LED_flash_map &= 0b11110111;
            break;
        case LED_B :
            LED_B_OUT = 0; // LED_B_ClrVal();
            LED_image &= 0b11111011;
            LED_state &= 0b11111011;
            LED_flash_map &= 0b11111011;
            break;
        case LED_C :
            LED_C_OUT = 0; // LED_C_ClrVal();
            LED_image &= 0b11111101;
            LED_state &= 0b11111101;
            LED_flash_map &= 0b11111101;
            break;
        case LED_D :
            LED_D_OUT = 0; // LED_D_ClrVal();
            LED_image &= 0b11111110;
            LED_state &= 0b11111110;
            LED_flash_map &= 0b11111110;
            break;
    }
}

//----------------------------------------------------------------------------
// push_LED_display : save current LED configuration
// ================
//
// Parameters
//      None
//
void push_LED_display(void) 
{
    LED_store[LED_store_pt][0] = LED_state;
    LED_store[LED_store_pt][1] = LED_flash_map;
    LED_store_pt++;
    clr_all_LEDs();
}

//----------------------------------------------------------------------------
// pop_LED_display : restore current LED configuration
// ================
//
// Parameters
//      None
//
void pop_LED_display(void) 
{
    LED_store_pt--;
    LED_state = LED_store[LED_store_pt][0];
    LED_flash_map = LED_store[LED_store_pt][1];
    LED_A_OUT = 0;
    LED_B_OUT = 0;
    LED_C_OUT = 0;
    LED_D_OUT = 0;
    if ((LED_state & 0b00001000) != 0){
        set_LED(LED_A, FLASH_OFF);
    }
    if ((LED_state & 0b00000100) != 0){
        set_LED(LED_B, FLASH_OFF);
    }    
    if ((LED_state & 0b00000010) != 0){
        set_LED(LED_C, FLASH_OFF);
    }    
    if ((LED_state & 0b00000001) != 0){
        set_LED(LED_D, FLASH_OFF);
    }    
}

//----------------------------------------------------------------------------
// clr_all_LEDs : clear one of the four LED indicators
// ============
//
// Parameters
//      none
//
// Notes
//      Also clear associated flash bits 
//
void clr_all_LEDs(void) 
{

    LED_A_OUT = 0;
    LED_B_OUT = 0;
    LED_C_OUT = 0;
    LED_D_OUT = 0;
    LED_image &= 0b11110000;
    LED_state = LED_image;
    LED_flash_map &= 0b11110000;    
}

//----------------------------------------------------------------------------
// set_flash_rate : set flash rate in units of 8mS 
// ==============
//
// Parameters
//      LED_code : LED1, LED2, LED3, LED4
//      count    : number of flashes
//
// Notes
//
void set_flash_rate(uint8_t  rate) 
{
    if (rate != 0) {
        flash_count = rate; 
    }
}

//----------------------------------------------------------------------------
// flash_LED : flash a specified LED a number of times
// =========
//
// Parameters
//      rate : SLOW_FLASH_RATE, FAST_FLASH_RATE, or 1->255
//
// Notes
//
void flash_LED(uint8_t  LED_code, uint8_t  count) 
{
int     i;

    for (i= 0 ; i<count ; i++) {
        set_LED(LED_code, FLASH_OFF);
        DelayMs(500);
        clr_LED(LED_code);
        DelayMs(500);
    }
}


//----------------------------------------------------------------------------
// display_number : show a 2 digit number on the seven segemnt display
// ==============
//
// Parameters
//      value : unsigned number to be displayed   0->99
//      flash_mode : flash information
//
// Notes
//
void display_number(uint8_t value, uint8_t flash_mode){

uint8_t   tens, units;

    tens = value / 10;
    units = value - (10 * tens);
    show_dual_chars((tens + '0'), (units + '0'), flash_mode);    
}


/* END user_display */
