
#include "froggy_toad.h"

typedef struct
{
  uint32_t score;
  char name[4];
} ScoreSave;


ScoreSave highScores[5] = 
{
  {50, "FTD"},
  {25, "BST"},
  {15, "TCK"},
  {10, "TYR"},
  { 5, "ABC"},  
};

void setScore( ScoreSave* save, uint32_t score )
{
  
}

void checkScore( uint32_t newScore )
{
  if(newScore > highScores[4].score)
  {
    int8_t i=4;
    while( (i>0) && (newScore > highScores[i-1].score) )
    {
      highScores[i]=highScores[--i];
    }
    setScore( &highScores[i], newScore );
  }
}

Status InitialsDisplay(Event evt)
{
  
  return goNextState( menuScreen );
  return STATUS_OK;
}

Status highScoreDisplay(Event evt)
{
  Status goNextState( menuScreen );
  return STATUS_OK;
}

