//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// sound.c : routines to play sounds
// =======
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd    12/02/09      iitial design
//----------------------------------------------------------------------------

#include "global.h"

sound_file_t     sound_file;

//----------------------------------------------------------------------------
// table of constants for frequency generation
//
#pragma INTO_ROM
const uint16_t tone_codes[12] = {
    C_COUNT,        // 16960 FREQ_C
    18051,          // (C_COUNT*FREQ_C)/FREQ_CS,
    17007,          // (C_COUNT*FREQ_C)/FREQ_D,
    16077,          // (C_COUNT*FREQ_C)/FREQ_DS,
    15152,          // (C_COUNT*FREQ_C)/FREQ_E,
    14327,          // (C_COUNT*FREQ_C)/FREQ_F,
    13514,          // (C_COUNT*FREQ_C)/FREQ_FS,
    13089,          // (C_COUNT*FREQ_C)/FREQ_G,
    12048,          // (C_COUNT*FREQ_C)/FREQ_GS,
    11364,          // (C_COUNT*FREQ_C)/FREQ_A,
    10989,          // (C_COUNT*FREQ_C)/FREQ_AS,
    10331,          // (C_COUNT*FREQ_C)/FREQ_B            
};

#pragma INTO_ROM
sound_file_t  no_sound = { 
    0,
    0,0
};

//----------------------------------------------------------------------------
// sound_init : initialise the sound system
// ==========
//
// Description
//      Ensures that the sound file data structure is disabled
//
void sound_init(void) 
{
    sound_file.mode = SOUND_DISABLE;
    note_pt = 0;
    note_duration = 0;        
}

//----------------------------------------------------------------------------
// play_tune : enamble system to play a sequence of notes
// =========
//
// Parameters
//      *sound_file_pt : pointer to a sound file
//
// Notes
//
void play_tune(const sound_file_t  *sound_file_pt) {

uint8_t   i, nos_notes;

    nos_notes = sound_file_pt->note_count;
    sound_file.note_count = nos_notes;
    for (i=0 ; i < nos_notes ; i++) {
        sound_file.note[i][0] = sound_file_pt->note[i][0];
        sound_file.note[i][1] = sound_file_pt->note[i][1];
    }
    sound_file.mode = SOUND_ENABLE;

}

//----------------------------------------------------------------------------
// stop_tune : stop current sound sequence 
// =========
//
// Parameters
//      none
//
// Notes
//
void stop_tune(void) {

    setReg16(TPM2C0V, 0);
    sound_file.mode = SOUND_DISABLE;
}

//----------------------------------------------------------------------------
// set_tone : Play a note for a defined duration
// ========
//
// Parameters
//      note        : NOTE_C, NOTE_CS, NOTE_D,  etc
//      octave      : 1, 2, or 3
//      duration    : in units of mS
//
// Notes
//      Tone generation uses Timer unit 2.
//
void set_tone(uint8_t note, uint16_t duration) {

    setReg16(TPM2MOD, tone_codes[note]);      // set period
    setReg16(TPM2C0V, (tone_codes[note]/2));
    DelayMs(duration);
    setReg16(TPM2C0V, 0);
}

//----------------------------------------------------------------------------
// tone_on : start tone playing
// =======
//
// Parameters
//      note        : NOTE_C, NOTE_CS, NOTE_D,  etc
//
// Notes
//      Tone generation uses Timer unit 2.
//
void tone_on(uint8_t note) {

    setReg16(TPM2MOD, tone_codes[note]);      // set period
    setReg16(TPM2C0V, (tone_codes[note]/2));
}

//----------------------------------------------------------------------------
// tone_off : stop tone playing
// ========
//
// Parameters
//      note        : NOTE_C, NOTE_CS, NOTE_D,  etc
//
// Notes
//      Tone generation uses Timer unit 2.
//
void tone_off(void) {

    setReg16(TPM2C0V, 0);
}

//----------------------------------------------------------------------------
// beep : Play a series of notes
// ====
//
// Parameters
//      note        : NOTE_C, NOTE_CS, NOTE_D,  etc
//      count       : number of beeps required
//

void beep(uint8_t note, uint8_t count) {

uint8_t   i;

    if (count == 0) {
        return;
    }
    for (i = 0 ; i < count ; i++){
        set_tone(note, 200);
        DelayMs(100);
    }
    return;
}
