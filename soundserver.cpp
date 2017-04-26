/** Includes *****************************************************************/
#include "soundserver.h"
#include <ArduboyTones.h>


/** Constants and Macros *****************************************************/
#define FastForwardFudgeFactor 1

/** Type Definitions *********************************************************/

typedef struct 
{
  int32_t lastStart;
  int32_t lastDuration;
  const byte* seq;
  int16_t counter;
  int16_t lastFreq;
  int8_t flags; //  1-loop
  int8_t durationMagnitude;
  int8_t baseOctave;  
} SeqState ;

/** Function Prototypes ******************************************************/
bool soundOn(void);

/** Data *********************************************************************/
PROGMEM const unsigned int NoteFreqs [NUM_NOTES] = {
   33488, //C7
   35479, //C#7
   37589, //D7
   39824, //D#7
   42192, //E7
   44701, //F7
   47359, //F#7
   50175, //G7
   53159, //G#7
   56320, //A7
   59669, //A#7
   63217  //B7
};


static ArduboyTones sound(soundOn);
static SeqState SFX;
static SeqState music;
static bool musicFF=false;
bool SoundOn = true;
bool MusicOn = true;


/** Functions ****************************************************************/

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
bool soundOn() { return SoundOn; }


/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
void initSoundEngine() {
 SFX.seq=NULL;
 music.seq = NULL;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
void fastforwardSeq( SeqState* sstate )
{
    int32_t fastforward= millis()-sstate->lastStart;
    int16_t freq=sstate->lastFreq;
    int32_t duration=sstate->lastDuration;
    byte Packet = 0;
    fastforward += FastForwardFudgeFactor;
    while( (fastforward >= duration) &&
           (END_OF_SEQUENCE!=Packet)
           )
    {
      fastforward -= duration;
      Packet = pgm_read_byte(sstate->seq+(sstate->counter++));
      if (END_OF_SEQUENCE!=Packet)
      {
        int8_t note=Packet>>4;
        int8_t octave=(Packet>>3 & 0x01) + (sstate->baseOctave);
        duration= 1 << ((sstate->durationMagnitude) - ((Packet >> 1) & 0x03));
        if (Packet & 1) //Dotted => +50%
        {
          duration += (duration >>1);
        }
        if(note < NUM_NOTES)
        {
          freq=pgm_read_word( NoteFreqs+note ) >> ( 11 - octave);
        }
        else
        {
          freq=0;
        }
      }
    }
    
    if (END_OF_SEQUENCE!=Packet)
    {
      duration -= fastforward;
      sound.tone( freq, duration );
      sstate->lastStart=millis();
      sstate->lastFreq=freq;
      sstate->lastDuration=duration;
    }  
    else if((sstate->flags) & 1)
    {
      sstate->counter=1;
    }
    else
    {
      sstate->seq=NULL;
    }
}



/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
void playNextSeq( SeqState* sstate )
{
    int16_t freq=sstate->lastFreq;
    int32_t duration=sstate->lastDuration;
    byte Packet = pgm_read_byte(sstate->seq+(sstate->counter++));
    if (END_OF_SEQUENCE!=Packet)
    {
      int8_t note=Packet>>4;
      int8_t octave=(Packet>>3 & 0x01) + (sstate->baseOctave);
      duration= 1 << ((sstate->durationMagnitude) - ((Packet >> 1) & 0x03));
      if (Packet & 1) //Dotted => +50%
      {
        duration += (duration >>1);
      }
      if(note < NUM_NOTES)
      {
        freq=pgm_read_word( NoteFreqs+note ) >> ( 11 - octave);
      }
      else
      {
        freq=0;
      }
      sound.tone( freq, duration );
      sstate->lastStart=millis();
      sstate->lastFreq=freq;
      sstate->lastDuration=duration;
    }  
    else if((sstate->flags) & 1)
    {
      sstate->counter=1;
    }
    else
    {
      sstate->seq=NULL;
    }
}



/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
void SoundEngine() {
  if ( !SoundOn ) 
  {
    SFX.seq = NULL;
    return;
  }

  if(!sound.playing())
  {
    if ( SFX.seq ) 
    {
      playNextSeq(&SFX);
      /*if(-1==(SFX_Counter=playNextSeq(SFX,SFX_Counter)))
      {
        SFX=NULL;
      }*/
    }
  }

  if(!sound.playing() && 
     MusicOn &&  
     (music.seq != NULL)
    )
  {
    if ( musicFF )
    {
      musicFF=false;
      fastforwardSeq(&music);
    }
    else
    {
      playNextSeq(&music);
    }
  }
}



/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
static void parseHeader( SeqState * sstate, uint8_t header )
{
  sstate->baseOctave=(header>>5);
  sstate->durationMagnitude=(header&0x1F);
}



/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
void requestSoundEffect( const uint8_t* sfx)
{
    SFX.seq=sfx;
    parseHeader(&SFX, pgm_read_byte(sfx));
    SFX.counter=1;
    SFX.flags=0;
    SFX.lastStart=millis();
    sound.noTone();
    musicFF=true;
    
}



/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 */
void requestMusic( const uint8_t* seq)
{
    music.seq=seq;
    parseHeader(&music, pgm_read_byte(seq));
    music.counter=1;
    music.flags=1;
    music.lastStart=millis();
    musicFF=false;
}


/**
 * Stops playing the music after the current play thru ends
 *
 */
void stopMusicLoop()
{
    music.flags=0;  
}


/////////////////////////////////////////////////////////////////////////////////



