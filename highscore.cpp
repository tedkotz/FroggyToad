#include "highscore.h"
#include "froggy_toad.h"

#include <EEPROM.h>

static const int BASE_EEPROM_ADDR=64;
static const int ENTRY_SIZE=7;
static const int NUM_SCORE_RECORDS=7;
static const int NUM_HIGH_SCORES = 5;

typedef struct
{
  uint32_t score;
  char name[4];
} ScoreSave;


ScoreSave highScores[NUM_HIGH_SCORES];

ScoreSave* overwriteScore;
DisplayState returnState;
int namePos;


void resetEEPROM( )
{
  int i,j;
  int addr= BASE_EEPROM_ADDR;
  for( i=0; i<NUM_SCORE_RECORDS; ++i )
  {
    for(j=0;j<4;++j)
    {
      EEPROM.write(addr++,0);
    }
    for(j=0;j<3;++j)
    {
      EEPROM.write(addr++,'A');
    }    
  }
}

void readScore( ScoreSave* save, int slot )
{
  uint8_t* dest=(uint8_t*)save;
  int source = BASE_EEPROM_ADDR+slot*ENTRY_SIZE;
  for( int i = 0; i<ENTRY_SIZE; ++i)
  {
    *dest++ = EEPROM.read(source + i);
  }
  // null terminate the string we didn't store
  *dest++ = 0;
}


void insertScore( ScoreSave* score )
{
    int8_t i=4;
    while( (i>0) && (score->score > highScores[i-1].score) )
    {
      --i;
      highScores[i+1]=highScores[i];
    }
    highScores[i]=*score;
}

void readHighScores( void )
{
  ScoreSave newScore;
  int i;
  for( i=1; i<NUM_HIGH_SCORES; ++i )
  {
    highScores[i].score=0;
  }
  // Just read the first score in
  readScore(&highScores[0], 0);

  // sort in the next values
  for( i=1; i<NUM_HIGH_SCORES; ++i )
  {
    readScore(&newScore, i);
    insertScore(&newScore);
  }

  for(; i<NUM_SCORE_RECORDS; ++i )
  {
    readScore(&newScore, i);
    if(newScore.score > highScores[4].score)
    {
      insertScore(&newScore);
    }
  }
}


void writeScore( const ScoreSave* save, int slot )
{
  const uint8_t* src=(const uint8_t*)save;
  int dst = BASE_EEPROM_ADDR+slot*ENTRY_SIZE;
  for( int i = 0; i<ENTRY_SIZE; ++i)
  {
    EEPROM.write(dst + i, *src++);
  }
  // don't store the null terminator
}

void lockInHighScore( void )
{
  uint32_t lowScore;
  ScoreSave tmpScore;
  int lowSlot=0;
  int i;
  readScore( &tmpScore, 0 );
  lowScore=tmpScore.score;
  
  //Find lowest score slot
  for(i=1; i<NUM_SCORE_RECORDS; ++i )
  {
    readScore( &tmpScore, i );
    if(tmpScore.score<lowScore)
    {
      lowScore=tmpScore.score;
      lowSlot=i;
    }
  }

  //overwrite score
  writeScore( overwriteScore, lowSlot );
}

Status initialsReadState(Event evt)
{
  const char MAX_DISP_CHAR=126;
  const char MIN_DISP_CHAR=32;  
  char c;
  switch(evt)
  {
    case EVT_A:
    case EVT_B:
    case EVT_RT:
     if( namePos < 2 ) 
     {
       ++namePos;
     }
     else
     {
        lockInHighScore();
        return goNextState(returnState);
     }
     break;

    case EVT_LT:
     if( namePos > 0 ) 
     {
       --namePos;
     }
     break;

    case EVT_UP:
     c=overwriteScore->name[namePos];
     if(c > MIN_DISP_CHAR)
     {
      --c;
     }
     else
     {
      c=MAX_DISP_CHAR;
     }
     overwriteScore->name[namePos]=c;
     break;
    
    case EVT_DN:
     c=overwriteScore->name[namePos];
     if(c < MAX_DISP_CHAR)
     {
      ++c;
     }
     else
     {
      c=MIN_DISP_CHAR;
     }
     overwriteScore->name[namePos]=c;
     break;
     
    default:
     // ignore unknown events
     break;
  }
  arduboy.setCursor(58, 32);
  arduboy.print(overwriteScore->name);
  arduboy.setCursor(58+namePos*6, 40);
  arduboy.print("^");
  
    
  return STATUS_OK;
}

Status highScoreDisplay(Event evt)
{
  if( (EVT_NONE!=evt) ||
      (stateCount > (30*FRAME_RATE))
    )
  {
    
    return goNextState(menuScreen);
  }
  else
  {
    for(int i=0; i<5; i++)
    {
      arduboy.setCursor((128-8*6)/2, 12+(i*8));
      arduboy.print(highScores[i].name);
      arduboy.print("  ");
      arduboy.print(highScores[i].score);
    }
    return STATUS_OK;
  }
}

DisplayState checkScore( uint32_t newScore, DisplayState defaultState )
{
  if(newScore > highScores[4].score)
  {
    int8_t i=4;
    while( (i>0) && (newScore > highScores[i-1].score) )
    {
      --i;
      highScores[i+1]=highScores[i];
    }
    overwriteScore=&highScores[i];
    overwriteScore->score=newScore;
    returnState=defaultState;
    namePos=0;
    for(i=0;i<3;++i)
    {
      overwriteScore->name[i]='A';
    }
    overwriteScore->name[3]='\0';
    return initialsReadState;
  }
  else
  {
    return defaultState;
  }
}
