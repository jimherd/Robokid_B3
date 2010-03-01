//----------------------------------------------------------------------------
// sound.h
// =======
//
//----------------------------------------------------------------------------
//
#ifndef __sound_H
#define __sound_H

//
// data stucture for a sound file
//    
typedef struct  {
    uint8_t   mode, note_count;
    uint8_t   note[64][2];
} sound_file_t;

enum {SOUND_DISABLE, SOUND_ENABLE};

void sound_init(void);
void play_tune(const sound_file_t  *sound_file_pt);
void stop_tune(void);
void set_tone(uint8_t note, uint16_t duration);
void tone_on(uint8_t note);
void tone_off(void);
void beep(uint8_t note, uint8_t count);


#endif /* __sound_H */