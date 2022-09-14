/**
 * The starting point of execution. 
 * 
 * @author Ted Kotz
 * @version 0.1
 */

/** Includes *****************************************************************/
#include <Arduboy2.h>
#include "soundserver.h"
#include "resources.h"
#include "menu.h"
#include "main.h"
#include "highscore.h"
#include "froggy_toad.h"

/** Constants and Macros *****************************************************/
#define OBSTACLES_PER_ROW_POWER (2)
#define OBSTACLES_PER_ROW  (1<<OBSTACLES_PER_ROW_POWER)
#define NUM_VISIBLE_ROWS 7
#define FOOD_MULT (64)
#define MAX_FOOD (80*FOOD_MULT)
#define WARN_FOOD (MAX_FOOD/4)
#define MAX_DIFFICULTY 3

enum
{
  OBS_SIDEWALK,
  //Road Type
  OBS_CARLT,
  OBS_ROADSTERLT,
  OBS_TRUCKLT,
  OBS_TRACTORLT,
  OBS_CARRT,
  OBS_ROADSTERRT,
  OBS_TRUCKRT,
  OBS_TRACTORRT,
  //Water Type
  OBS_LILLYPAD,
  OBS_LOGLT,
  OBS_LOGRT,
  //OBS_TURTLE,
  //OBS_GATOR,
  //OBS_DUCK,
  NUM_OBSTACLE_TYPES
};
typedef uint8_t ObstacleType;

const ObstacleType OBS_FIRST_WATER_TYPE=OBS_LILLYPAD;


/** Type Definitions *********************************************************/
typedef struct {
  const byte* image;
  uint8_t imageSize;
  uint8_t minSpeed;
  uint8_t maxSpeed;
  uint8_t minSpacing;
  uint8_t maxSpacing;
} ObstacleInfo;

typedef struct
{
  int16_t obstacle16X;
  ObstacleType type;
  int8_t spd;
//  uint8_t obstacleCount;
//  uint8_t obstacleStart;
  int8_t obstacleXoffset;
} GameRowType;

typedef struct
{
  GameRowType row[8];
  const byte* playerImg;
  uint32_t score;
  uint16_t food;
  int16_t invincible;
  int8_t playerX;
  int8_t playerY;
  int8_t bottomRow;
} GameStateType;


/** Data *********************************************************************/
GameStateType gameState;
int8_t difficulty=1;

const ObstacleInfo obstacles[NUM_OBSTACLE_TYPES] PROGMEM = {
  /* OBS_SIDEWALK,   */ { NULL,           0,   0, 127,  0,  0 },
  /* OBS_CARLT,      */ { carImg,        10, (uint8_t)SPD_PS2PF(-480), (uint8_t)SPD_PS2PF( -60), 24, 64 },
  /* OBS_ROADSTERLT, */ { roadsterLtImg,  8, (uint8_t)SPD_PS2PF(-960), (uint8_t)SPD_PS2PF(-120), 36, 80 },
  /* OBS_TRUCKLT,    */ { truckLtImg,    24, (uint8_t)SPD_PS2PF(-480), (uint8_t)SPD_PS2PF( -60), 24, 64 },
  /* OBS_TRACTORLT,  */ { tractorLtImg,  10, (uint8_t)SPD_PS2PF(-480), (uint8_t)SPD_PS2PF( -60), 24, 64 },
  /* OBS_CARRT,      */ { carImg,        10, (uint8_t)SPD_PS2PF(  60), (uint8_t)SPD_PS2PF( 480), 24, 64 },
  /* OBS_ROADSTERRT, */ { roadsterRtImg,  8, (uint8_t)SPD_PS2PF( 120), (uint8_t)SPD_PS2PF( 960), 36, 80 },
  /* OBS_TRUCKRT,    */ { truckRtImg,    24, (uint8_t)SPD_PS2PF(  60), (uint8_t)SPD_PS2PF( 480), 24, 64 },
  /* OBS_TRACTORRT,  */ { tractorRtImg,  10, (uint8_t)SPD_PS2PF(  60), (uint8_t)SPD_PS2PF( 480), 24, 64 },
  /* OBS_LILLYPAD,   */ { lillypadImg,    7, (uint8_t)SPD_PS2PF(   0), (uint8_t)SPD_PS2PF(   0),  0,100 },
  /* OBS_LOGLT,      */ { logImg,        24, (uint8_t)SPD_PS2PF(-480), (uint8_t)SPD_PS2PF( -60), 16, 48 },
  /* OBS_LOGRT,      */ { logImg,        24, (uint8_t)SPD_PS2PF(  60), (uint8_t)SPD_PS2PF( 480), 16, 48 },
};


const uint8_t nextRowChance[NUM_OBSTACLE_TYPES][NUM_OBSTACLE_TYPES] PROGMEM =
{
                        /*        +--------LT---------+   +--------RT---------+
                        /* SDWK,  CAR, RDSR, TRUK, TRCR,  CAR, RDSR, TRUK, TRCR, LILY, LLOG, RLOG */
  /* OBS_SIDEWALK,   */ {     0,    8,   16,   24,   32,   40,   48,   56,   64,   80,  112, 128  },
  /* OBS_CARLT,      */ {    32,   48,   64,   80,   96,  104,  112,  120,  128,    0,    0,   0  },
  /* OBS_ROADSTERLT, */ {    32,   48,   64,   80,   96,  104,  112,  120,  128,    0,    0,   0  },
  /* OBS_TRUCKLT,    */ {    32,   48,   64,   80,   96,  104,  112,  120,  128,    0,    0,   0  },
  /* OBS_TRACTORLT,  */ {    32,   48,   64,   80,   96,  104,  112,  120,  128,    0,    0,   0  },
  /* OBS_CARRT,      */ {    32,   40,   48,   56,   64,   80,   96,  112,  128,    0,    0,   0  },
  /* OBS_ROADSTERRT, */ {    32,   40,   48,   56,   64,   80,   96,  112,  128,    0,    0,   0  },
  /* OBS_TRUCKRT,    */ {    32,   40,   48,   56,   64,   80,   96,  112,  128,    0,    0,   0  },
  /* OBS_TRACTORRT,  */ {    32,   40,   48,   56,   64,   80,   96,  112,  128,    0,    0,   0  },
  /* OBS_LILLYPAD,   */ {    32,    0,    0,    0,    0,    0,    0,    0,    0,    0,   80, 128  },
  /* OBS_LOGLT,      */ {    32,    0,    0,    0,    0,    0,    0,    0,    0,   47,   56, 128  },
  /* OBS_LOGRT,      */ {    32,    0,    0,    0,    0,    0,    0,    0,    0,   47,  119, 128  },
};



/** Code *********************************************************************/

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
uint8_t hibit(uint32_t n) {
  uint8_t ret=0;

  while(n>>=1)
  {
    ret++;
  }

  return ret;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void displayRow( uint8_t baseY, GameRowType* row )
{
  int16_t x;
  if( row->type==OBS_SIDEWALK )
  {
    arduboy.drawFastHLine(0, baseY, 128, WHITE);
    arduboy.drawFastHLine(0, baseY+7, 128, WHITE);
    for(x= 15; x<120; x+=16)
    {
      arduboy.drawFastVLine(x,baseY+1, 6, WHITE);
      arduboy.drawPixel(x-1,baseY+8, WHITE);
    }
    if(row->spd < 48)
    {
      x=(row->spd & 0xF)* 8;
      arduboy.drawBitmap(x, baseY, bugImg, 7, 8, 1);
    }
    else if(row->spd < 64 )
    {
      x=(row->spd & 0xF) * 8;
      arduboy.drawBitmap(x, baseY, starImg, 7, 8, 1);
    }
     
    return;
  }
  else if( row->type < OBS_FIRST_WATER_TYPE )
  {
    // draw dashes
    for(x= -2; x<120; x+=17)
      arduboy.drawFastHLine(x,baseY+8, 7, WHITE);
  }
  else
  {
    // draw  ripples
    for(int16_t y=baseY-4;y<baseY+4;y+=4)
      for(x= (y & 4) ? 9 : 0; x<120; x+=18)
        arduboy.drawBitmap(x, y, rippleImg, 8, 5, 1);
  }
  // draw obstacles
  for( x=(row->obstacle16X/16); x<128; x += (row->obstacleXoffset))
  {
    ObstacleInfo obstacle;
    memcpy_P(&obstacle, &obstacles[row->type], sizeof(ObstacleInfo));
    arduboy.fillRect(x, baseY+1, obstacle.imageSize, 7, BLACK);
    arduboy.drawBitmap(x, baseY, obstacle.image, obstacle.imageSize, 8, 1);
  }
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
ObstacleType nextRowType( ObstacleType prevRow )
{
  uint8_t rowChance[NUM_OBSTACLE_TYPES];
  uint8_t roll=random(128);
  memcpy_P(rowChance, nextRowChance[prevRow], NUM_OBSTACLE_TYPES);
  ObstacleType i=0; 
  while(roll>=rowChance[i])
  {
    i++;
  }
  return i;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
bool detectRowCollision(GameRowType* rowPtr, int8_t obstacleX)
{
  ObstacleInfo obstacle;
  memcpy_P(&obstacle, &obstacles[rowPtr->type], sizeof(ObstacleInfo));
  if(((gameState.playerX-obstacleX)+7) % (rowPtr->obstacleXoffset) < (obstacle.imageSize + 7))
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void animateRow( GameRowType* rowPtr , bool containsPlayer )
{
  int16_t x16=rowPtr->obstacle16X+rowPtr->spd;
  int8_t x=x16/16;
  if(containsPlayer)
  {
    if(rowPtr->type==OBS_SIDEWALK)
    {
      if(rowPtr->spd<48)
      {
        int8_t powerUpX=(rowPtr->spd & 0x0F)*8;
        if(abs(gameState.playerX-powerUpX)<8)
        {
          gameState.food=MAX_FOOD;
          gameState.score+=5;
          requestSoundEffect(SFX_Pickup);
          rowPtr->spd=127;
        }
      }
      else if(rowPtr->spd<64)
      {
        int8_t powerUpX=(rowPtr->spd & 0x0F)*8;
        if(abs(gameState.playerX-powerUpX)<8)
        {
          gameState.food=MAX_FOOD;
          gameState.invincible=16*FRAME_RATE;
          requestMusic(DrunkenSailor);
          rowPtr->spd=127;
        }
      }
    }
    else if(rowPtr->type<OBS_FIRST_WATER_TYPE)
    {
      // Road Type
      if( (gameState.invincible<1) && detectRowCollision( rowPtr, x ) )
      {
        gameState.food=0;
      }
    }
    else
    {
      // Water Type
      if( !detectRowCollision( rowPtr, x ) )
      {
        gameState.food=0;
      }
      gameState.playerX+=(x-(rowPtr->obstacle16X/16));
    }
  }

  if(x < -(rowPtr->obstacleXoffset))
  {
    x16+=(rowPtr->obstacleXoffset*16);
  }
  else if(x > 0)
  {
    x16-=(rowPtr->obstacleXoffset*16);    
  }
  rowPtr->obstacle16X=x16;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void initRow( ObstacleType type,  GameRowType* rowPtr )
{
  ObstacleInfo obstacle;
  memcpy_P(&obstacle, &obstacles[type], sizeof(ObstacleInfo));
  rowPtr->type=type;
  rowPtr->spd=random(obstacle.minSpeed,obstacle.maxSpeed);
  rowPtr->obstacleXoffset=obstacle.imageSize+random(obstacle.minSpacing,obstacle.maxSpacing);   
  rowPtr->obstacle16X=16*(random(rowPtr->obstacleXoffset)-obstacle.imageSize);
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void initGameState()
{
  gameState.score=0;
  gameState.food=MAX_FOOD;
  gameState.playerX=56;
  gameState.playerY=48;
  gameState.playerImg=frogUpImg;
  gameState.bottomRow=0;
  gameState.invincible=0;
  gameState.row[0].type=OBS_SIDEWALK;
  gameState.row[0].spd=127;
  gameState.row[0].obstacle16X=0;
  gameState.row[0].obstacleXoffset=0;
  for(uint8_t i=1; i<NUM_VISIBLE_ROWS; ++i)
  {
    initRow( nextRowType(gameState.row[i-1].type), &gameState.row[i] );
  }
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void scrollScreen(void)
{
  uint8_t index=gameState.bottomRow;
  index = (index+1) & 0x07;
  initRow( nextRowType(gameState.row[(index+5) & 0x07].type), &gameState.row[(index+6) & 0x07] );
  gameState.bottomRow=index;
  gameState.score++;
}


/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
Status gameScreen(Event evt)
{
  switch(evt)
  {
    case EVT_A:
    case EVT_B:
     if( gameState.food > (gameState.score/4) ) 
     {
       requestSoundEffect(SFX_Bell);
     }
     else
     {
       gameState.food=0;
       
     }
     requestMusic(NULL);
     return goNextState(checkScore(gameState.score, menuScreen));
     break;

    case EVT_UP:
     if(gameState.playerY >= 32)
     {
       gameState.playerY-=8;
     }
     else
     {
       gameState.playerY=24;
       scrollScreen();
     }
     gameState.playerImg=frogUpImg;
     requestSoundEffect(SFX_Hit);
     break;
    
    case EVT_DN:
     if(gameState.playerY < (64-16))
     {
       gameState.playerY+=8;
     }
     else
     {
       gameState.playerY=(64-16);
     }
     gameState.playerImg=frogDnImg;
     requestSoundEffect(SFX_Hit);
     break;
    
    case EVT_LT:
     if(gameState.playerX >= 8)
     {
      gameState.playerX-=8;
     }
     else
     {
      gameState.playerX=0;
     }
     gameState.playerImg=frogLtImg;
     requestSoundEffect(SFX_Hit);
     break;
    
    case EVT_RT:
     if(gameState.playerX < (128-8))
     {
       gameState.playerX+=8;
     }
     else
     {
       gameState.playerX=128-8;
     }
     gameState.playerImg=frogRtImg;
     requestSoundEffect(SFX_Hit);
     break;

    default:
     // ignore unknown events
     break;    
  }
  arduboy.setCursor(8, 56);
  arduboy.print(gameState.score);
  arduboy.drawRect(40, 56, 88, 8, WHITE);
  uint8_t index=gameState.bottomRow;
  for(uint8_t i=0; i<NUM_VISIBLE_ROWS; ++i)
  {
    uint8_t rowY=48-(i << 3);
    animateRow( &gameState.row[index], (gameState.playerY==rowY) );
    displayRow( rowY, &gameState.row[index] );
    index = (index+1) & 0x07;
  }
  
  uint16_t foodConsumed=hibit(gameState.score)*SPD_PS2PF(30);

  if( gameState.food > foodConsumed ) 
  {
    if(gameState.invincible>0)
    {
      if(gameState.invincible==1)
      {
        requestMusic(LadiesOfSpain);     
      }
      gameState.invincible -= 1;
      gameState.food = MAX_FOOD;
    }
    else
    {
      gameState.food-=foodConsumed;
    }
    if(gameState.playerX < 0   ) gameState.playerX=0;
    if(gameState.playerX > 120 ) gameState.playerX=120;
    if(gameState.playerY < 24  ) gameState.playerY=24;
    if(gameState.playerY > 48  ) gameState.playerY=48;    
    arduboy.fillRect(gameState.playerX, gameState.playerY+1, 7, 7, BLACK);
    arduboy.drawBitmap(gameState.playerX, gameState.playerY, gameState.playerImg, 7, 7, WHITE);
    if( ((gameState.food > WARN_FOOD) && (gameState.invincible<1)) || ((stateCount & 0x7) < 4) )
      arduboy.fillRoundRect(42, 58, gameState.food/FOOD_MULT+4, 4, 2, WHITE);
  }
  else
  {
    arduboy.fillRect(34, 27, 60, 10, BLACK);
    arduboy.setCursor(36, 28);
    arduboy.print(F("Game Over"));
    gameState.food = 0;
    gameState.playerY = 48;
    stopMusicLoop();
  }
  return STATUS_OK;
}


/*** Start Section ******************************************************************************/


/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
Status startGame(Event evt)
{
  if(stateCount>1)
  {
    initGameState();
    return goNextState(gameScreen);
  }
  else
  {
    arduboy.fillRect(0, 0, 128, 64, WHITE);
    return STATUS_OK;
  }
}


/*** Menu Section *******************************************************************************/



/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showContinue( void )
{
  arduboy.print(F("Continue"));
  return 8;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showStart( void )
{
  arduboy.print(F("New Game"));
  return 8;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showSoundFX( void )
{
  arduboy.print(F("SFX: "));
  if( SoundOn ) 
  {
    arduboy.print(F("On"));
    return 7;
  }
  else
  {
    arduboy.print(F("Off"));    
    return 8;
  }
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showMusic( void )
{
  arduboy.print(F("Music: "));
  if( MusicOn ) 
  {
    arduboy.print(F("On"));
    return 9;
  }
  else
  {
    arduboy.print(F("Off"));    
    return 10;
  }
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showDifficulty( void )
{
  arduboy.print(F("Difficulty: "));
  arduboy.print(difficulty);
  return 13;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showBackground( void )
{
  arduboy.print(F("Background"));
  return 10;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
int8_t showHighScores( void )
{
  arduboy.print(F("High Scores"));
  return 11;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onContinue( void )
{
    arduboy.initRandomSeed();
    requestMusic(LadiesOfSpain);
    requestSoundEffect(SFX_Bell);
    goNextState(gameScreen);
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onStart( void )
{
    arduboy.initRandomSeed();
    requestMusic(LadiesOfSpain);
    goNextState(startGame);
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onSoundFX( void )
{
    requestSoundEffect(SFX_Bell);
    SoundOn=!SoundOn;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onMusic( void )
{
    requestSoundEffect(SFX_Bell);
    MusicOn=!MusicOn;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onDifficulty( void )
{
  difficulty++;
  if( difficulty > MAX_DIFFICULTY ) difficulty = 1;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onBackground( void )
{
    requestMusic(ScarboroughFair);
    goNextState(backstoryScreen);
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onHighScores( void )
{
    requestMusic(DrunkenSailor);
    stopMusicLoop();
    goNextState(highScoreDisplay);
}


MenuItem mainMenu[] =
{
  { showContinue,   onContinue },
  { showStart,      onStart },
  { showSoundFX,    onSoundFX },
  { showMusic,      onMusic },
//Bring back when difficulty setting does something  { showDifficulty, onDifficulty },
  { showBackground, onBackground },
  { showHighScores, onHighScores },
} ;
#define MAIN_MENU_SIZE (sizeof(mainMenu)/sizeof(MenuItem))


/*** Menu Section *******************************************************************************/

/**
 * Handles an event and passes it to the selcted menu.
 *
 * @param evt the event to process
 * @param menu the menu to update based on the event
 */
static void processMenuEvent( Event evt, Menu *menu )
{
  switch(evt)
  {
    case EVT_UP:
      requestSoundEffect(SFX_Beep);
      onMenuUp(menu);

    break;
    case EVT_DN:
      requestSoundEffect(SFX_Beep);
      onMenuDn(menu);

    break;
    case EVT_A:
    case EVT_B:
      onMenuClick(menu);
    break;

    default:
     // ignore unknown events
    break;
  }
}

/**
 * The display state to display and manage the menu
 *
 * @param evt The next event to process
 * @return STATUS_OK
 */
Status menuScreen(Event evt)
{
  static Menu menuState;
  requestMusic(NULL);
  if(stateCount<2)
  {
    if((gameState.food<1) ||(gameState.food> MAX_FOOD))
    {
      // remove continue from menu
      initMenuState(&menuState, mainMenu + 1, MAIN_MENU_SIZE - 1);
    }
    else
    {
      initMenuState(&menuState, mainMenu, MAIN_MENU_SIZE);      
    }
  }
  else if (stateCount > (30*FRAME_RATE))
  {
    if( random(2) )
    {
      requestMusic(DrunkenSailor);
      stopMusicLoop();
      return goNextState(highScoreDisplay);
    }
    else
    {
      requestMusic(ScarboroughFair);
      return goNextState(backstoryScreen);
    }
  }
  processMenuEvent( evt, &menuState );

  // show Menu Screen;
  arduboy.setTextSize(2);
  arduboy.print(F("FroggyToad\n"));
  arduboy.setTextSize(1);
  displayMenu( &menuState, 6, 40, &arduboy );
  return STATUS_OK;
}


/**
 * The display state to display and manage the menu
 *
 * @param evt The next event to process
 * @return STATUS_OK
 */
Status backstoryScreen(Event evt)
{
  switch(evt)
  {
    case EVT_UP:
      if(stateCount>=8)
      {
        stateCount-=8;
      }

    break;
    case EVT_DN:
      stateCount+=8;

    break;
    case EVT_A:
    case EVT_B:
      stopMusicLoop();
      return goNextState(menuScreen);
    break;
    
    default:
     // ignore unknown events
    break;
  }
  if (stateCount > ((56+12*8)*FRAME_RATE/4))
  {
    stopMusicLoop();
    return goNextState(menuScreen);
  }
  arduboy.setCursor(0, 56-((stateCount*4)/FRAME_RATE));
  arduboy.print(F("Toshi Toad is just\ntrying to make his\nway in life.\n\nRough waters and\nterrible traffic have\nmade him anxious.\n\nHelp Toshi find some\ntasty treats.\n\nKeep on your toes.\nGrab Power-Ups.\nAnd, most importantly\nSTAY FROGGY."));
  return STATUS_OK;
}

/**
 * Function/Method Description
 * put your setup code here, to run once:
 *
 * @param name description
 * @see header.h
 */
void setup() {
  arduboy.begin();
  initTaskModel(menuScreen);
  gameState.food=0;
  readHighScores();
}

/**
 * Function/Method Description
 * put your main code here, to run repeatedly:
 *
 * @param name description
 * @see header.h
 */
void loop() 
{
  runTasks();
}
