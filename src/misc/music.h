#ifndef MUSIC_H
#define MUSIC_H

#include <stdint.h>

void setBPM(uint8_t bpm);

void play_note(char* note, uint8_t value);

void play_pause(uint8_t value);

#endif
