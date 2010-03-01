//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// experiment.c : vehicle test code
// ============
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           07/09/2008      file of test code functions
//                       
//----------------------------------------------------------------------------

#include "global.h"

#pragma  MESSAGE DISABLE C1420

extern volatile  uint8_t    flash_test;


//----------------------------------------------------------------------------
// run_experiment_mode : run some experimental code
// ===================
//
// Notes
//      Series of experiments to test various aspects of the workings of the
//      vehicle.
//          0. Output system version to serial port and cycle seven segment and LED displays
//          1. run robot forward/backward continuously
//          2. Read battery voltage and output to serial port
//          3. read all a/d voltages and output to serial port
//          4. vary motor speed
//          5. check wheel sensors and output to serial port
//          6. test flash erase/write
//          7. Read line sensors and output to serial port
//          8. serial port echo test ('e' to exit)
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_experiment_mode(void) {

uint8_t       experiment;

    experiment = FIRST_EXPERIMENT_MODE;
    E_MODE_LEDS;
    show_dual_chars('E', '0', (A_TO_FLASH | 10)); 

//
// main loop
//       
    FOREVER {
//
//  check and act on the switches
//
        if (switch_D == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_D);
            experiment++;
            if (experiment > LAST_EXPERIMENT_MODE) {
                experiment = FIRST_FOLLOW_MODE;
            }
            show_dual_chars('E', ('0'+ experiment), (A_TO_FLASH | 10));
        }
        if (switch_C == PRESSED) {            //  back to main 
            WAIT_SWITCH_RELEASED(switch_C);   
            return 0;
        }        
        if (switch_A == PRESSED) {              
            set_LED(LED_A, FLASH_ON); 
            set_LED(LED_D, FLASH_ON);
            WAIT_SWITCH_RELEASED(switch_A); 
        } else {
            continue;
        }
//
// run an experiment
// 
        show_dual_chars('E', ('0'+ experiment), 0);       
        switch (experiment) {
            case CYCLE_DISPLAYS :        // Experiment 0 : Output system version and cycle seven segment and LED displays
                experiment_0(1);
                break;
            case 1 :        // Experiment 1 : run robot forward/backward continuously
                experiment_1(100);                 
                break;
            case 2 :        // Experiment 2 : read battery voltage
                experiment_2(1);
                break;
            case 3 :        // Experiment 3 : read all a/d voltages
                experiment_3(100);
                break;
            case 4 :        // Experiment 4 : vary motor speed
                experiment_4(1);
                break;
            case 5 :        // Experiment 5 : check wheel sensors
                experiment_5(1);
                break;
            case 6 :        // Experiment 6 : test flash erase/write
                experiment_6();
                break;
            case 7 :        // Experiment 7 : read line sensors
                experiment_7(100);
                break;
            case 8 :        // Experiment 8 : serial port echo test ('e' to exit)
                experiment_8();
                break;   
            case 9 :        // Experiment 9 : read switches
                experiment_9(1);
                break;                                                                                                       
             default :
                break;
        }
        show_dual_chars('E', ('0'+ experiment), 0); 
        E_MODE_LEDS;      
    }      // end of FOREVER loop
}


//----------------------------------------------------------------------------
// experiment_0 : Output system version and cycle seven segment and LED displays
// ============
//
// Notes
//
uint8_t experiment_0(uint8_t count) {

uint8_t   i;

    for (i=0 ; i < count ; i++) {
//
// print version to serial port
//    
        #ifdef VERSION_A
            send_msg("Version A\r\n");
        #else
            send_msg("Version B\r\n");
        #endif
        
        DisableInterrupts;            // disable background display flash activity
//
// clear displays
//
        clr_LED(LED_A); WAIT_1SEC;
        clr_LED(LED_B); WAIT_1SEC;
        clr_LED(LED_C); WAIT_1SEC;
        clr_LED(LED_D); WAIT_1SEC;
        PTAD = 0x00;
        WAIT_1SEC;          
//
//  cycle bars of 7-segment display A
//         
        SEG_A_CTRL = 1; SEG_B_CTRL = 0;
        PTAD = 0x01; WAIT_1SEC;
        PTAD = 0x02; WAIT_1SEC;
        PTAD = 0x04; WAIT_1SEC;
        PTAD = 0x08; WAIT_1SEC;
        PTAD = 0x10; WAIT_1SEC;
        PTAD = 0x20; WAIT_1SEC;
        PTAD = 0x40; WAIT_1SEC;
        PTAD = 0x80; WAIT_1SEC;
//
//  cycle bars of 7-segment display B
//         
        SEG_A_CTRL = 0; SEG_B_CTRL = 1;
        PTAD = 0x01; WAIT_1SEC;
        PTAD = 0x02; WAIT_1SEC;
        PTAD = 0x04; WAIT_1SEC;
        PTAD = 0x08; WAIT_1SEC;
        PTAD = 0x10; WAIT_1SEC;
        PTAD = 0x20; WAIT_1SEC;
        PTAD = 0x40; WAIT_1SEC;
        PTAD = 0x80; WAIT_1SEC;
//
// turn-on LEDs in sequence
//         
        set_LED(LED_A, FLASH_OFF); WAIT_1SEC;
        set_LED(LED_B, FLASH_OFF); WAIT_1SEC;
        set_LED(LED_C, FLASH_OFF); WAIT_1SEC;
        set_LED(LED_D, FLASH_OFF); WAIT_1SEC;
//
// turn-off LEDs in sequence
//         
        clr_LED(LED_A); WAIT_1SEC;
        clr_LED(LED_B); WAIT_1SEC;
        clr_LED(LED_C); WAIT_1SEC;
        clr_LED(LED_D); WAIT_1SEC;                
                      
        EnableInterrupts;        // re-enable background display flash activity
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_1 : run robot forward/backward continuously
// ============
//
// Notes
//
uint8_t experiment_1(uint8_t count) {

uint8_t   i, j, ad_value;

    for(i=0 ; i<count ; i++){
        for(j=0 ; j<100 ; j++) {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, 75);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, 75);
            DelayMs(30000);
            ad_value = get_adc(BATTERY_VOLTS);   
            send_msg(bcd(ad_value, tempstring));
            send_msg(",");
            DelayMs(20000);                                                    
            set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
            set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
            DelayMs(10000);
            ad_value = get_adc(BATTERY_VOLTS);                    
            send_msg(bcd(ad_value, tempstring));
            send_msg(",\r\n");                                           
            set_motor(LEFT_MOTOR, MOTOR_BACKWARD, 50);
            set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, 50);
            DelayMs(30000);
            ad_value = get_adc(BATTERY_VOLTS);                     
            send_msg(bcd(ad_value, tempstring));
            send_msg(",");
            DelayMs(20000);                                                    
            set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
            set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
            DelayMs(10000);
            ad_value = get_adc(BATTERY_VOLTS);                     ;
            send_msg(bcd(ad_value, tempstring));
            send_msg(",\r\n");
        }   
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_2 : read battery voltage
// ============
//
// Notes
//
uint8_t experiment_2(uint8_t count) {

uint8_t   i, j, ad_value;

    for(i=0 ; i<count ; i++){
        for(j=0 ; j<100 ; j++) {
            ad_value = get_adc(BATTERY_VOLTS);             
            send_msg(bcd(ad_value, tempstring));
            send_msg(",\r\n");
            DelayMs(5000);
        }
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_3 : read all a/d voltages
// ============
//
// Notes
//
uint8_t experiment_3(uint8_t count) {

uint8_t   i, j, k, ad_value;

    for(i=0 ; i<count ; i++){
        for(j=0 ; j<100 ; j++) {
            for (k = BATTERY_VOLTS ; k <= REAR_SENSOR ; k++) {                    
                ad_value = get_adc(k);             
                send_msg(bcd(ad_value, tempstring));
                send_msg(",\r\n");
            }
            send_msg(",\r\n");
            DelayMs(5000);
        }
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_4 : vary motor speed
// ============
//
// Notes
//
uint8_t experiment_4(uint8_t count) {

uint8_t   i, j;

    for(i=0 ; i<count ; i++){
        for (j= 100 ; j>0 ; j -=10) {
            send_msg(bcd(j, tempstring));
            send_msg("% of full speed\r\n");
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, j);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, j);
            DelayMs(5000);
        }    
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_5 : check wheel sensors
// ============
//
// Notes
//
uint8_t experiment_5(uint8_t count) {

uint8_t   i, j;

    enable_wheel_count();
    for(i=0 ; i<count ; i++){
        for(j=0 ; j<100 ; j++) {
            left_wheel_count = 0;
            right_wheel_count = 0;
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, 60);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, 60);
            DelayMs(5000);
            set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
            set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
            DelayMs(1000);
            send_msg(bcd((uint8_t)(left_wheel_count), tempstring));
            send_msg(", ");
            send_msg(bcd((uint8_t)(right_wheel_count), tempstring));
            send_msg("\r\n");
            DelayMs(5000);
        }    
    }
    disable_wheel_count();
    return 0;
}

//----------------------------------------------------------------------------
// experiment_6 : test flash erase/write
// ============
//
// Notes
//
uint8_t experiment_6(void) {

//uint8_t   i;
//
//    for(i=0 ; i<count ; i++){
//        send_msg(bcd(flash_test, tempstring));
//        send_msg("\r\n");
//        if (flash_test == 0x55) {
//                send_msg("Flash loaded with 0x55\r\n");
//        } else { 
//            if (flash_test == FLASH_ERASE_STATE) {
//                send_msg("Flash location in erased state\r\n");
//                send_msg("Flash erase starting....");
//                FlashErasePage((uint16_t)&flash_test);
//                send_msg("Flash erase complete\r\n");
//                send_msg("Flash write starting....");
//                FlashProgramByte((uint16_t)&flash_test, 0x55);
//                send_msg("Flash write complete\r\n");
//            } else {
//                send_msg("Flash has odd value\r\n");
//            }
//        }
//        DelayMs(20000);         
//    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_7 : read line sensors
// ============
//
// Notes
//
uint8_t experiment_7(uint8_t count) {

uint8_t   i, j, ad_value;

    for(i=0 ; i<count ; i++){
        send_msg("Left sensor, Right_sensor");
        for(j=0 ; j<100 ; j++) {                    
            ad_value = get_adc(LINE_SENSOR_L);
            send_msg(bcd(ad_value, tempstring));
            ad_value = get_adc(LINE_SENSOR_R);
            send_msg(", ");
            send_msg(bcd(ad_value, tempstring));
            send_msg("\r\n");
            DelayMs(100); 
        }    
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_8 : serial port echo test ('e' to exit)
// ============
//
// Notes
//
uint8_t experiment_8(void) {

char   ch;

    FOREVER {
        ch = sci_rx_byte();
        if (ch == 'e'){
            break;    
        } else {
            sci_tx_byte(ch+1);
        }   
    }
    return 0;
}

//----------------------------------------------------------------------------
// experiment_9 : read switches
// ============
//
// Notes
//
uint8_t experiment_9(uint8_t count) {
                                                                 
uint8_t   i, j;

    send_msg("SWA, SWB, SWC, SWD, IR\r\n");
    for(i=0 ; i<count ; i++){
        for(j=0 ; j<30 ; j++){
            send_msg(bcd(switch_A, tempstring)); send_msg(", "); 
            send_msg(bcd(switch_B, tempstring)); send_msg(", "); 
            send_msg(bcd(switch_C, tempstring)); send_msg(", "); 
            send_msg(bcd(switch_D, tempstring)); send_msg(", ");
            send_msg(bcd(PTDD_PTDD7, tempstring)); send_msg("\r\n");   
            DelayMs(2000);
        }
    }
    return 0;
}



