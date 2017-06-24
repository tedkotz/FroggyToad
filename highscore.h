#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "main.h"

DisplayState checkScore( uint32_t newScore, DisplayState defaultState );

Status highScoreDisplay(Event evt);


void resetEEPROM( void );

void readHighScores( void );

#endif //HIGHSCORE_H
