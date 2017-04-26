/** Includes *****************************************************************/
#include "menu.h"

/** Constants and Macros *****************************************************/
/** Type Definitions *********************************************************/
/** Function Prototypes ******************************************************/
/** Data *********************************************************************/
/** Functions ****************************************************************/

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onMenuClick( Menu* menu )
{
  menu->items[menu->selectedItem].selected();
}  
  
/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onMenuUp( Menu* menu  )
{
  if( menu->selectedItem > 0 )
  {
    menu->selectedItem--;
  }
  else
  {
    menu->selectedItem=menu->size-1;
  }
  
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void onMenuDn( Menu* menu  )
{
  menu->selectedItem++;
  if( menu->selectedItem >=  menu->size )
  {
    menu->selectedItem=0;
  }
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void displayMenu( const Menu* menu , int16_t x, int16_t y, Arduboy2* arduboy)
{
  int8_t i;
  arduboy->setTextBackground(0);
  arduboy->setTextColor(1);
  if( menu->selectedItem < 1 )
  {
    i=(menu->size-1);
  }
  else
  {
    i=menu->selectedItem-1;
  }
  arduboy->setCursor(x, y);
  menu->items[i].show();
  y+=8;
  arduboy->setTextBackground(1);
  arduboy->setTextColor(0);
  arduboy->setCursor(x, y);
  menu->items[menu->selectedItem].show();
  y+=8;
  arduboy->setTextBackground(0);
  arduboy->setTextColor(1);
  arduboy->setCursor(x, y);
  i=menu->selectedItem+1;
  if( i >= menu->size )
  {
    i=0;
  }
  menu->items[i].show();
  y+=8;
}

/**
 * Function/Method Description
 *
 * @param name description
 * @see header.h
 * @return header.h
 */
void initMenuState( Menu* menu, const MenuItem *list, int8_t size )
{
  menu->selectedItem=0;
  menu->items=list;
  menu->size=size;
}

