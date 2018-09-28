#ifndef MenuLibrary
#define MenuLibrary
#include "main.h"
#include "USBdriveLib.h"
#include "config.h"






#define MENU_LAYERS 10 //delete

  char *NumberToString(int number);

  void LCDUpdate(unsigned int phase, char character, int row, int colomn);

  unsigned int LCDUpdatePeriodsToGo(unsigned int phase);

  char* MenuOption(volatile int* pointer);
  char* MenuTitle(volatile int* pointer);



  //extern volatile struct menuNode * pcurrentMenuNode;

  void NodeInitialization();

  char* getMenuNodeName(volatile menuNode * pmenuNode);

  //char* getMenuNodeTitle( volatile menuNode * pmenuNode);

  void loadNewScreen(volatile menuNode * pmenuNode);

  void pressedDown();
  void pressedUp();
  void pressedOk();
  void pressedBack();

  char* getFlashDrivePieceName(node * pFlashDriveNode);

  void loadFlashDriveContent(node * pFlashDriveNode);

  void SwitchToEnglish();
  void SwitchToRussian();


#endif
