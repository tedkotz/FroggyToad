#ifndef MENU_H
#define MENU_H

/** Includes *****************************************************************/
#include <Arduboy2.h>

/** Constants and Macros *****************************************************/
/** Type Definitions *********************************************************/
typedef int8_t (*MenuShow)(void);
typedef void (*MenuCallBack)(void);

typedef struct
{
  MenuShow show;
  MenuCallBack selected;
} MenuItem;

typedef struct
{
  int8_t selectedItem;
  int8_t size;
  const MenuItem* items;
} Menu;

/** Function Prototypes ******************************************************/
void onMenuClick( Menu* menu );
void onMenuUp( Menu* menu );
void onMenuDn( Menu* menu );
void displayMenu( const Menu* menu, int16_t x, int16_t y, Arduboy2* arduboy);
void initMenuState( Menu* menu, const MenuItem* list, int8_t size );

/** Data *********************************************************************/

#endif //MENU_H
