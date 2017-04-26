#ifndef MAIN_H
#define MAIN_H
/** Includes *****************************************************************/
#include <Arduboy2.h>

/** Constants and Macros *****************************************************/
#define FRAME_RATE 10
#define BUTTON_REPEAT_FRAMES (60 * FRAME_RATE)
#define DIRECTION_REPEAT_FRAMES (FRAME_RATE)
#define SPD_PS2PF(X) (((X)+(FRAME_RATE/2))/(FRAME_RATE))


enum Event
{
  EVT_NONE=0,
  EVT_UP,
  EVT_DN,
  EVT_LT,
  EVT_RT,
  EVT_A,
  EVT_B,
  NUM_Events
};

typedef uint8_t Status;
#define STATUS_OK 0

/** Type Definitions *********************************************************/
typedef Status (*DisplayState)(Event evt);

/** Function Prototypes ******************************************************/
void initTaskModel( DisplayState startState );
Status goNextState( DisplayState nextState );
void runTasks(void);

/** Data *********************************************************************/
extern Arduboy2 arduboy;
extern DisplayState displayState;
extern DisplayState oldState;
extern int stateCount;


#endif //MAIN_H
