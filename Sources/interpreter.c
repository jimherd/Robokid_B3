//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// interpreter.c : execute sequence of robot command
// =======
//
// Description
//      Robot commands are executed using a simple stack machine.
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd            3/10/09      initial design
//----------------------------------------------------------------------------

#include "global.h"

#define    STACK_SIZE        8         // number of 16-bit elements oon the stack
#define    NOS_VARIABLES    16

//
// stack to hold data for the robot commands
//
union {
    uint16_t item_16[STACK_SIZE];
    uint8_t  item_8[STACK_SIZE*2];
} stack;
//
// stack machine registers
//
uint8_t    stack_ptr = 0;       // stack pointer
uint16_t   sequence_ptr = 0;    // program counter
//
// storage for variables
//
uint16_t vars[NOS_VARIABLES];

//
// parameters relevant to the currently executing program
//
uint8_t   sequence_left_speed, sequence_right_speed, sequence_left_direction, sequence_right_direction;
uint16_t  sequence_time, sequence_distance;


    
//----------------------------------------------------------------------------
// init_for_program_execution : initialise the system ready to execute a sequence
// ==========================
//
// Description
//      Set all relevant variables to theit init state.
// Parameters
//      None
// Globals      
//      stack, vars,stack_ptr,sequence_ptr 
//
void init_for_sequence_execution(void) 
{
int i;
  
    stack_ptr = 0;
    sequence_ptr = 0;
    sequence_left_speed = 0;
    sequence_right_speed= 0;
    sequence_time = 0;
    sequence_distance = 0;
    
    for (i=0 ; i<NOS_VARIABLES ; i++) {
        vars[i] = 0;
    }

    for (i=0 ; i<STACK_SIZE ; i++) {
        stack.item_16[i] = 0;
    }
}

//----------------------------------------------------------------------------
// cmd_push_L8 : push an 8-bit value onto the stack
// ===========
//
// Description
//      Pushes an 8-bit value into the low byte of the current empty element
//      on the stack.
// Parameters
//      value   : 8-bit value to be stored on the stack
// Globals      
//      stack : stack structure in RAM
// Notes
//      On entry, stack pointer points to the empty top of the stack
//
void cmd_push_L8(uint8_t value) 
{  
    stack.item_16[stack_ptr] = 0;
    stack.item_8[(stack_ptr *2) + 1] = value;
    stack_ptr++;    
}

//----------------------------------------------------------------------------
// cmd_push_H8 : push an 8-bit value onto the stack
// ===========
//
// Description
//      Pushes an 8-bit value into the high byte of the last element
//      on the stack.
// Parameters
//      value   : 8-bit value to be stored on the stack
// Globals      
//      stack : stack structure in RAM
// Notes
//      On entry, stack pointer points to the empty top of the stack but value
//      is stored in the previous stack element.
//      Important :: only use AFTER a push_L8 call.
//
void cmd_push_H8(uint8_t value) 
{  

    stack.item_8[(stack_ptr * 2) -2] = value;  
}

//----------------------------------------------------------------------------
// cmd_push_16 : push an 16-bit value onto the stack
// ===========
//
// Description
//      Pushes an 16-bit value into the top of the stack.
// Parameters
//      value   : 16-bit value to be stored on the stack
// Globals      
//      stack : stack structure in RAM
// Notes
//      On entry, stack pointer points to the empty top of the stack
//
void cmd_push_16(uint16_t value) 
{  

    stack.item_16[stack_ptr] = value;
    stack_ptr++;    
}

//----------------------------------------------------------------------------
// cmd_pop_8 : pop an 8-bit value from the low byte of the stack
// =========
//
// Description
//      pops an 8-bit value from the stack.
// Parameters
//      None
// Results
//      returns an 8-bit value
// Globals      
//      stack : stack structure in RAM
//
uint8_t cmd_pop_8(void) 
{  
    stack_ptr--;    
    return (stack.item_8[stack_ptr * 2]);
}

//----------------------------------------------------------------------------
// cmd_pop_16 : pop an 16-bit value from the stack
// ==========
//
// Description
//      pops an 8-bit value from the stack.
// Parameters
//      None
// Results
//      returns a 16-bit value
// Globals      
//      stack : stack structure in RAM
//
uint16_t cmd_pop_16(void) 
{  
    stack_ptr--;    
    return (stack.item_16[stack_ptr]);
}

//----------------------------------------------------------------------------
// decode_command : split a command into its parts
// ==============
//
// Description
//      split a 16-bit command into its three parts
//          - op-code, modifier, data
// Parameters
//      base_address : base address of command sequence
// Results
//      None
//
void decode_command(uint16_t command) 
{
    
    robot_command.op_code  = (uint8_t)((command >> 8) & 0x3F);
    robot_command.modifier = (uint8_t)((command >> 8) & 0xC0);
    robot_command.data     = (uint8_t)((command) & 0xFF);
}

//----------------------------------------------------------------------------
// run_sequence : run a sequence of robot commands
// ============
//
// Description
//      Execute a specified sequence of robot command.
// Parameters
//      program : array of instructions
// Results
//      None
//
void run_sequence(uint16_t  sequence[]) 
{
int8_t   r_speed, l_speed;
uint8_t  motor, ad_value, speed_tweak;
uint16_t time, target_time;

    init_for_sequence_execution();
//
// calculate speed tweak from reading from POT_1
//    
    ad_value = get_adc(POT_1);        
    speed_tweak = (ad_value >> 4) & 0x0F;
    left_motor_tweak = 0;
    right_motor_tweak = 0;
    if (speed_tweak > 8) {
        left_motor_tweak = speed_tweak - 8;
    }
    if (speed_tweak < 7) {
        right_motor_tweak = 7 - speed_tweak;
    }
//
// command execute loop
//    
    FOREVER {
        decode_command(sequence[sequence_ptr]);    
        switch (robot_command.op_code) {
            case PUSH_L8 :
                switch (robot_command.modifier) {
                    case IMMEDIATE :
                        cmd_push_L8((uint8_t)robot_command.data);
                        break;
                    case REGISTER :
                        cmd_push_L8((uint8_t)vars[robot_command.data]);
                        break;
                }
                break;
//
            case PUSH_H8 :
                switch (robot_command.modifier) {
                    case IMMEDIATE :
                        cmd_push_H8((uint8_t)robot_command.data);
                        break;
                    case REGISTER :
                        cmd_push_H8((uint8_t)vars[robot_command.data]);
                        break;
                }
                break;
//
            case PUSH_16 :                           // only available in REGISTER mode
                switch (robot_command.modifier) {
                    case IMMEDIATE :
                        cmd_push_L8((uint8_t)robot_command.data);
                        break;
                    case REGISTER :
                        cmd_push_16(vars[robot_command.data]);
                        break;
                }
                break;
//
            case POP_8 : 
                vars[robot_command.data] = cmd_pop_8();
                break;
//
            case POP_16 : 
                vars[robot_command.data] = cmd_pop_16();
                break;
//
            case SET_PARAMETER :
                switch (robot_command.data) {
                    case SPEED :
                        if (cmd_pop_16() == LEFT_MOTOR) {
                            sequence_left_direction = cmd_pop_16();
                            sequence_left_speed = cmd_pop_16() + left_motor_tweak;
                        } else {
                            sequence_right_direction = cmd_pop_16();
                            sequence_right_speed = cmd_pop_16() + right_motor_tweak; 
                        }   
                        break;
                    case DISTANCE :
                        sequence_distance = cmd_pop_16();
                        break;
                    case TIME :
                        sequence_time = cmd_pop_16();
                        break;
                }
                break;
//
            case COMPUTE :
                switch (robot_command.data) {
                    case ADD :
                        stack.item_16[stack_ptr-2] = stack.item_16[stack_ptr-1] + stack.item_16[stack_ptr-2];
                        stack_ptr--;
                        break;
                }
                break;
//
            case GOTO : 
                switch (robot_command.modifier) {
                    case ABSOLUTE :
                        sequence_ptr = ((uint8_t)robot_command.data);
                        break;
                    case RELATIVE_PLUS :
                        sequence_ptr = sequence_ptr + ((uint8_t)robot_command.data);
                        break;
                    case RELATIVE_MINUS :
                        sequence_ptr = sequence_ptr - ((uint8_t)robot_command.data);
                        break;
                }
                break;
//
            case DEC_AND_SKIP :
                vars[robot_command.data]--;
                if (vars[robot_command.data] == 0) {
                    sequence_ptr++;
                }
                break;
//
            case EXECUTE :
                switch (robot_command.data) {
                    case MOVE_TIME :
                        CLR_TIMER16;
                        set_motor(LEFT_MOTOR, sequence_left_direction, sequence_left_speed);
                        set_motor(RIGHT_MOTOR, sequence_right_direction, sequence_right_speed);
                        FOREVER {
                            GET_TIMER16(time);
                            if (time > sequence_time) {
                                vehicle_stop();
                                break;
                            }
                        }
                        break;
                    case MOVE_DISTANCE :
                        if (sequence_left_direction == MOTOR_BACKWARD) {
                            l_speed = -(int8_t)sequence_left_speed;
                        } else {
                            l_speed = (int8_t)sequence_left_speed;
                        }
                        if (sequence_right_direction == MOTOR_BACKWARD) {
                            r_speed = -(int8_t)sequence_right_speed;
                        } else {
                            r_speed = (int8_t)sequence_right_speed;
                        }
                        if (sequence_left_speed > sequence_right_direction) {
                            motor = LEFT_MOTOR; 
                        } else {
                            motor = RIGHT_MOTOR;
                        }
                        move_distance(sequence_distance, motor, l_speed, r_speed);
                        break;
                    case START :
                        set_motor(LEFT_MOTOR, sequence_left_direction, sequence_left_speed);
                        set_motor(RIGHT_MOTOR, sequence_right_direction, sequence_right_speed);
                        break;
                    case STOP :
                        vehicle_stop();
                        break;
                }
                break;
//
            case TEST_AND_SKIP :
                switch (robot_command.data) {
                    case EQ :
                        if (stack.item_16[stack_ptr-1] == stack.item_16[stack_ptr-2]){
                           sequence_ptr++;
                        }
                        break;
                    case GT :
                        if (stack.item_16[stack_ptr-1] > stack.item_16[stack_ptr-2]){
                            sequence_ptr++;
                        }
                        break;
                    case LT :
                        if (stack.item_16[stack_ptr-1] < stack.item_16[stack_ptr-2]){
                            sequence_ptr++;
                        }
                        break;
                }
                stack_ptr -= 2;      // clear two item from the stack
                break;
//
            case READ_CHAN :
                switch (robot_command.modifier) {
                    case IMMEDIATE :
                        cmd_push_L8(get_adc(robot_command.data));
                        break;
                    case STACK :
                        cmd_push_L8(get_adc(cmd_pop_8()));
                        break;
                }
                break;
//
            case DELAY :
                switch (robot_command.modifier) {
                    case IMMEDIATE :
                        target_time = (robot_command.data * 100)/8;
                        break;
                    case STACK :
                        target_time = cmd_pop_16();
                        break;
                }
                CLR_TIMER16;
                FOREVER {
                    GET_TIMER16(time);
                    if (time > target_time) {
                        break;
                    }
                }
                break;
//
            case EXIT :
                left_motor_tweak = 0;
                right_motor_tweak = 0;
                return;
                break;
//
            default :
                break;
        }
        sequence_ptr++;        // onto next instruction
    }
}

//----------------------------------------------------------------------------
// store_instruction : store a single robot instruction in a sequence array
// =================
//
// Description
//      Format a 16-bit robot instruction and put it in the next free location for
//      a sequence.
//
// Parameters
//      uint16_t        sequence[]  : sequence area (in RAM)
//      uint8_t         inst_ptr    : current pointer to next free location
//      instruction_t   inst        : instruction
//      uint8_t         modifier    : instruction modifier
//      uint8_t         data        : instruction data
//
// Returned data
//      None
//

void store_instruction(uint16_t sequence[], uint8_t inst_ptr, instruction_t inst, uint8_t modifier, uint8_t data) 
{
uint16_t temp16;

    temp16 = ((((inst)<<8)&0x3F00) | (((modifier)<<8)&0xC000) | (((data))&0x00FF));
    sequence[inst_ptr] = temp16;
    
    return;    
}
