#ifndef SOUNDSERVER_H
#define SOUNDSERVER_H

/** Includes *****************************************************************/
#include <stdint.h>

/** Constants and Macros *****************************************************/
/**
 * Note tones
 */
enum NoteTone
{
  nC,
  nCs,
  nD,
  nDs,
  nE,
  nF,
  nFs,
  nG,
  nGs,
  nA,
  nAs,
  nB,
  NUM_NOTES,
  nDb=nCs,
  nEb=nDs,
  nGb=nFs,
  nAb=nGs,
  nBb=nAs,  
};

/** 
 *  Note Duration Fractions of reference
 */
enum NoteDurationFraction
{
  nd1,
  nd1_2,
  nd1_4,
  nd1_8,
};

#define DOT 1

/**
 * Macro helps with constructing sound sequences Header
 * 
 * Base Octave
 * Whole note duration as a power of 2 millisecs
 */
#define HEADER( Octave, DurationExponent ) ( Octave * 32 + DurationExponent)

/**
 * Macro helps with constructing sound sequence body bytes
 * 
 * Tone   0-11 (12)
 * Octave 0-1   (2)
 * Hold   0-3   (4)
 * Dotted 0-1   (2)
 * 
 */
#define NOTE( T, O, H, D) ( T * 16 + O * 8 + H * 2 + D)

#define END_OF_SEQUENCE 0xFF

/** Type Definitions *********************************************************/
/** Function Prototypes ******************************************************/
void initSoundEngine();
void SoundEngine();

void requestSoundEffect( const uint8_t* sfx);
void requestMusic( const uint8_t* seq);
void stopMusicLoop(void);


/** Data *********************************************************************/
extern bool SoundOn;
extern bool MusicOn;

#endif //SOUNDSERVER_H
