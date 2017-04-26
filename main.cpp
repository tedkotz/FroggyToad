/** Includes *****************************************************************/
#include "main.h"
#include "soundserver.h"


/** Constants and Macros *****************************************************/
/** Type Definitions *********************************************************/
/** Function Prototypes ******************************************************/
/** Data *********************************************************************/
Arduboy2 arduboy;
DisplayState displayState;
DisplayState oldState;
int stateCount;

/** Functions ****************************************************************/

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
bool processInput(int& frameCount, uint8_t buttons, int repeatFrames)
{
  if(arduboy.pressed(buttons))
  {
    if(frameCount<1)
    {
      frameCount=1;
      return true;
    }
    else if(frameCount>=repeatFrames)
    {
      frameCount=0;
    }
    else
    {
      frameCount++;
    }
  }
  else
  {
    frameCount=0;
  }
  return false;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
Event getNextEvent()
{
  static int framesUP=0;
  static int framesDN=0;
  static int framesLT=0;
  static int framesRT=0;
  static int framesA=0;
  static int framesB=0;
  if(processInput(framesUP, UP_BUTTON,    DIRECTION_REPEAT_FRAMES)) return EVT_UP;
  if(processInput(framesDN, DOWN_BUTTON,  DIRECTION_REPEAT_FRAMES)) return EVT_DN;
  if(processInput(framesLT, LEFT_BUTTON,  DIRECTION_REPEAT_FRAMES)) return EVT_LT;
  if(processInput(framesRT, RIGHT_BUTTON, DIRECTION_REPEAT_FRAMES)) return EVT_RT;
  if(processInput(framesA, A_BUTTON, BUTTON_REPEAT_FRAMES)) return EVT_A;
  if(processInput(framesB, B_BUTTON, BUTTON_REPEAT_FRAMES)) return EVT_B;
  
  return EVT_NONE;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
Status runCurrentState(Event evt)
{
  if(displayState!=oldState)
  {
    oldState=displayState;
    stateCount=0;
  }
  else
  {
    stateCount++;
  }
  return displayState(evt);
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
Status goNextState( DisplayState nextState )
{
  displayState=nextState;
  return runCurrentState(EVT_NONE);
}

/**
 * Initializes the display statemachine to the first state
 * put your setup code here, to run once:
 *
 * @param startState first display state
 */
void initTaskModel( DisplayState startState )
{
  arduboy.setFrameRate(FRAME_RATE);
  displayState=startState;
  oldState=NULL;
  arduboy.setTextSize(1);
  initSoundEngine();  
  arduboy.clear();
}

/**
 * Run tasks
 *
 */
void runTasks()
{
  if(arduboy.nextFrame())
  {
    arduboy.clear();
    arduboy.setCursor(0, 0);
    if(STATUS_OK!=runCurrentState(getNextEvent()))
    {
      setup();
    }
    arduboy.display();
  }
  SoundEngine();  
}


