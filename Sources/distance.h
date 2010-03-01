//----------------------------------------------------------------------------
// distance.h
// =====
//
//----------------------------------------------------------------------------
//
#ifndef __distance_H
#define __distance_H

uint8_t run_distance_mode(void);
uint8_t run_distance_mode_0(void);
uint8_t run_distance_mode_1(void);
uint8_t run_distance_mode_2(void);
uint8_t move_distance(uint16_t encoder_counts, motor_t unit, int8_t l_speed, int8_t r_speed);


#endif /* __distance_H */