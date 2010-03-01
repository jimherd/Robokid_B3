//----------------------------------------------------------------------------
// program.h
// ==========
//
//----------------------------------------------------------------------------
//
#ifndef __program_H
#define __program_H

uint8_t run_program_mode(void);
uint8_t run_program_mode_0(void);
uint8_t run_program_mode_1(void);
uint8_t run_program_mode_2(void);
uint8_t run_program_mode_3(void);
uint8_t scan_strips_push(void);
uint8_t scan_strips_drive(void);
uint8_t play_sequence(void);
uint8_t dump_strips(void);
uint8_t input_timed_sequence(void);
uint8_t input_distance_sequence(void);
void save_sequence(uint8_t flash_seq_no);
void load_sequence(uint8_t flash_seq_no);
void dump_sequence(void);


#endif /* __program_H */