#include "music.h"
#include <stdint.h>
#include "../peripherals/timer.h"
#include "../clock/clock.h"

uint16_t BPM; //Sets the one quarter value

void setBPM(uint8_t bpm){
    BPM = bpm;
}

void music_delay(uint32_t usec){
    uint32_t current = getUsecWorking();
    uint32_t ret = getUsecWorking();
    while((ret - current) < usec){
        ret = getUsecWorking();
    }
}

void play_note(char* note, uint8_t value){
    uint32_t note_freq;
    uint16_t power=1;
    for(int i = 0; i < (note[1] - '0'); i++){
        power*=2;
    }
    if(note[2] == '\0'){
        switch(note[0]){
            case 'A':
                note_freq = (power*27500)/1000;
                break;
            case 'B':
                note_freq = (power*30870)/1000;
                break;
            case 'C':
                note_freq = (power*16350)/1000;
                break;
            case 'D':
                note_freq = (power*18350)/1000;
                break;
            case 'E':
                note_freq = (power*20600)/1000;
                break;
            case 'F':
                note_freq = (power*21830)/1000;
                break;
            case 'G':
                note_freq = (power*24500)/1000;
                break;
        }
    }
    setPWM(note_freq);
    uint32_t quarter_usec_delay = (60*1000000/BPM); // The initial 1000000 is for accuracy reasons
    uint32_t delay = quarter_usec_delay*4/value;
    uint32_t note_play_time_usec = delay - 20000;
    music_delay(note_play_time_usec);
    setPWM(0);
    music_delay(delay - note_play_time_usec);
    TIM2_CR1 = 0;
}

void play_pause(uint8_t value){
    uint32_t quarter_usec_delay = (60*1000000/BPM); // The initial 1000000 is for accuracy reasons
    uint32_t delay = quarter_usec_delay*4/value;
    uint32_t pause_play_time_usec = delay;
    music_delay(pause_play_time_usec);
}
