//----------------------------------------------------------------------------
// interpreter.h
// =============
//
//----------------------------------------------------------------------------
//
#ifndef __interpreter_H
#define __interpreter_H

//----------------------------------------------------------------------------
// definition of a robot command
//

typedef enum {CMD_FORWARD = 10, CMD_BACKWARD, CMD_SPIN_LEFT, CMD_SPIN_RIGHT, CMD_STOP } cmd_t;

#define   FIRST_CMD     CMD_FORWARD
#define   LAST_CMD      CMD_SPIN_RIGHT


//----------------------------------------------------------------------------
// set of robot commands 
//

typedef enum { PUSH_16, PUSH_L8, PUSH_H8, POP_8, POP_16, SET_PARAMETER, 
       COMPUTE, GOTO, EXECUTE, DEC_AND_SKIP, TEST_AND_SKIP, READ_CHAN, EXIT, DELAY,
} instruction_t;

enum { SPEED, DISTANCE, TIME, };
enum { ADD, };
enum { MOVE_TIME, MOVE_DISTANCE, START, STOP };
enum { EQ, LT, GT };
enum { NO, YES };
    
//
// instruction modifiers
//
#define   NO_MOD       0
#define   IMMEDIATE    0
#define   REGISTER     1
#define   STACK        2

#define   ABSOLUTE           0
#define   RELATIVE_PLUS      1
#define   RELATIVE_MINUS     2

#define   NO_DATA      0

//
// definition of variable addresses
//
enum {V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15 };  // var_names;

//----------------------------------------------------------------------------
// set of sequence commands 
//
//typedef enum {SETSPEED, FINISH, START, STOP, WAIT, JUMP, SETVAR, LOAD_RAND, 
//              DECSKIP, CALC, TESTSKIP
//} COMMAND;

//----------------------------------------------------------------------------
// prototypes
//
void init_for_sequence_execution(void);
void cmd_push_L8(uint8_t value);
void cmd_push_H8(uint8_t value);
void cmd_push_16(uint16_t value);
uint8_t cmd_pop_8(void);
uint16_t cmd_pop_16(void);
void run_sequence(uint16_t  sequence[]);
void store_instruction(uint16_t sequence[], 
                          uint8_t inst_ptr, 
                          instruction_t inst, 
                          uint8_t modifier, 
                          uint8_t data);
void decode_command(uint16_t command); 

#endif /* __interpreter_H */