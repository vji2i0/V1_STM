#include "MenuLibrary.h"
#include "main.h"
#include "global_variables.h"
#include "LCD.h"
#include <stdio.h>
#include "stm32f4xx_it.h"
#include "usb_host.h"
#include "USBdriveLib.h"
#include "fatfs.h"
#include <stdbool.h>
#include "Flash.h"

volatile _Bool longName = false;
volatile int currentOption=1;
volatile int maxTranslation=0;
volatile int startTranslation=1;



  char *NumberToString(int number)
  {
    static char snumber[6];
    if (number<10)
    {
      sprintf(snumber, "    %d", number);
    }else if (number<100){
      sprintf(snumber, "   %d", number);
    }else if (number<1000){
      sprintf(snumber, "  %d", number);
    }else if (number<10000){
      sprintf(snumber, " %d", number);
    }else if (number<100000){
      sprintf(snumber, "%d", number);
    }
    return snumber;
  }


  void LCDUpdate(unsigned int phase, char character, int row, int colomn)
  {
    switch (phase)
    {
      case 1:
      {
        LCDSetToWrite();
        LCDSetCommandMode();
        break;
      }
      case 2:
      {
        LCDEnableOn();
        break;
      }
      case 3:
      {
        LCDSetCursorPosition(row, colomn);
        break;
      }
      case 4:
      {
        LCDEnableOff();
        break;
      }
      case 5:
      {
        LCDSetToWrite();
        LCDSetCharacterMode();
        break;
      }
      case 6:
      {
        LCDEnableOn();
        break;
      }
      case 7:
      {
        LCDSetACharacter(character);
        break;
      }
      case 8:
      {
        LCDEnableOff();
        break;
      }
    }
  }

  unsigned int LCDUpdatePeriodsToGo(unsigned int phase)
  {
    volatile int j=0;
    switch (phase)
    {
      case 1:
      {
        j=0;
        break;
      }
      case 2:
      {
        j=0;
        break;
      }
      case 3:
      {
        j=0;
        break;
      }
      case 4:
      {
        j=9;
        break;
      }
      case 5:
      {
        j=0;
        break;
      }
      case 6:
      {
        j=0;
        break;
      }
      case 7:
      {
        j=0;
        break;
      }
      case 8:
      {
        j=9;
        break;
      }
     }
    return j;
  }




//The structure of the menu





//The description and initialization of the nodes
void NodeInitialization()
{
  //sprintf(print.title, "___MAIN MENU____");
  //sprintf(print.name, " Print          ");
  //print.nodeType = (int)SIMPLENODETYPE;
  //print.mode = (int)OFFMODE;
  print.upNode = NULL;
  print.downNode = & settings;
  print.leftNode = NULL;
  print.rightNode = NULL;

  //sprintf(settings.title, "___MAIN MENU____");
  //sprintf(settings.name, " Settings       ");
  //settings.nodeType = (int)SIMPLENODETYPE;
  //settings.mode = (int)OFFMODE;
  settings.upNode = & print;
  settings.downNode = & changeFilament;
  settings.leftNode = NULL;
  settings.rightNode = & typeOfPlastic;

    //sprintf(typeOfPlastic.title, "____SETTINGS____");
    //sprintf(typeOfPlastic.name, " Type of plastic");
    //typeOfPlastic.nodeType = (int)SIMPLENODETYPE;
    //typeOfPlastic.mode = (int)OFFMODE;
    typeOfPlastic.upNode = NULL;
    typeOfPlastic.downNode = & extruderTemperature;
    typeOfPlastic.leftNode = & settings;
    typeOfPlastic.rightNode = & ABSplastic;

      //sprintf(ABSplastic.title, "TYPE OF PLASTIC_");
      //sprintf(ABSplastic.name, " ABS plastic    ");
      //ABSplastic.nodeType = (int)SIMPLENODETYPE;
      //ABSplastic.mode = (int)OFFMODE;
      ABSplastic.upNode = NULL;
      ABSplastic.downNode = & PLAplastic;
      ABSplastic.leftNode = & typeOfPlastic;
      ABSplastic.rightNode = NULL;

      //sprintf(PLAplastic.title, "TYPE OF PLASTIC_");
      //sprintf(PLAplastic.name, " PLA plastic    ");
      //PLAplastic.nodeType = (int)SIMPLENODETYPE;
      //PLAplastic.mode = (int)OFFMODE;
      PLAplastic.upNode = & ABSplastic;
      PLAplastic.downNode = NULL;
      PLAplastic.leftNode = & typeOfPlastic;
      PLAplastic.rightNode = NULL;

    //sprintf(extruderTemperature.title, "____SETTINGS____");
    //sprintf(extruderTemperature.name, " Extruder temp. ");
    //extruderTemperature.nodeType = (int)SIMPLENODETYPE;
    //extruderTemperature.mode = (int)OFFMODE;
    extruderTemperature.upNode = & typeOfPlastic;
    extruderTemperature.downNode = & bedTemperature;
    extruderTemperature.leftNode = & settings;
    extruderTemperature.rightNode = NULL;

    //sprintf(calibrate.title, "____SETTINGS____");
    //sprintf(calibrate.name, " Calibrate      ");
    //calibrate.nodeType = (int)SIMPLENODETYPE;
    //calibrate.mode = (int)OFFMODE;
    bedTemperature.upNode = & extruderTemperature;
    bedTemperature.downNode = & printCube;
    bedTemperature.leftNode = & settings;
    bedTemperature.rightNode = NULL;

    //sprintf(brightness.title, "____SETTINGS____");
    //sprintf(brightness.name, " Brightness     ");
    //brightness.nodeType = (int)SIMPLENODETYPE;
    //brightness.mode = (int)OFFMODE;
    printCube.upNode = & bedTemperature;
    printCube.downNode = & language;
    printCube.leftNode = & settings;
    printCube.rightNode = NULL;

    //sprintf(language.title, "____SETTINGS____");
    //sprintf(language.name, " Language       ");
    //language.nodeType = (int)SIMPLENODETYPE;
    //language.mode = (int)OFFMODE;
    language.upNode = & printCube;
    language.downNode = NULL;
    language.leftNode = & settings;
    language.rightNode = & english;

      english.upNode = NULL;
      english.downNode = & russian;
      english.leftNode = & language;
      english.rightNode = NULL;

      russian.upNode = & english;
      russian.downNode = NULL;
      russian.leftNode = & language;
      russian.rightNode = NULL;
  //sprintf(changeFilament.title, "___MAIN MENU____");
  //sprintf(changeFilament.name, " Change filament");
  //changeFilament.nodeType = (int)SIMPLENODETYPE;
  //changeFilament.mode = (int)OFFMODE;
  changeFilament.upNode = & settings;
  changeFilament.downNode = & help;
  changeFilament.leftNode = NULL;
  changeFilament.rightNode = NULL;

  //sprintf(help.title, "___MAIN MENU____");
  //sprintf(help.name, " Help           ");
  //help.nodeType = (int)SIMPLENODETYPE;
  //help.mode = (int)OFFMODE;
  help.upNode = & changeFilament;
  help.downNode = NULL;
  help.leftNode = NULL;
  help.rightNode = NULL;

}



/*char* getMenuNodeTitle(volatile menuNode * pmenuNode)
{
  volatile char str[16];
  sprintf(str, "%s", pmenuNode->title);
  return str;
}*/


//When a button is pressed
//extern volatile menuNode * pcurrentMenuNode;
//For a USB Flash-Drive
extern ApplicationTypeDef Appli_state;
//Pointer for the USB flash-drive content
//extern node * pNode;
//extern char path[100];

void pressedDown()
{
  if(pcurrentMenuNode->mode == OFFMODE)
  {
    if(pcurrentMenuNode->downNode != NULL)
    {
      pcurrentMenuNode=pcurrentMenuNode->downNode;
      loadNewScreen(pcurrentMenuNode);
    }
  }else{
    switch(pcurrentMenuNode->nodeType)
    {
      case PRINTNODETYPE:
      if (pcurrentMenuNode->mode == ONMODE)
      {
        DOWNfunction();
        loadFlashDriveContent(pNode);
      }
      break;

      case EXTRUDERTEMPERATURENODETYPE:
      if (extruderTargetTamperature > extruderLowerTamperature) extruderTargetTamperature = extruderTargetTamperature - 1;
      sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(extruderTargetTamperature), " ", 0b11101111,"C      ");
      break;

      case BEDTEMPERATURENODETYPE:
      if (bedTargetTamperature > bedLowerTamperature) bedTargetTamperature = bedTargetTamperature - 1;
      sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(bedTargetTamperature), " ", 0b11101111,"C      ");
      break;
    }
  }
}

void pressedUp()
{
  if(pcurrentMenuNode->mode == OFFMODE)
  {
    if(pcurrentMenuNode->upNode != NULL)
    {
      pcurrentMenuNode=pcurrentMenuNode->upNode;
      loadNewScreen(pcurrentMenuNode);
    }
  }else{
    switch(pcurrentMenuNode->nodeType)
    {
      case PRINTNODETYPE:
      if (pcurrentMenuNode->mode == ONMODE)
      {
        UPfunction();
        loadFlashDriveContent(pNode);
      }
      break;

      case EXTRUDERTEMPERATURENODETYPE:
      if (extruderTargetTamperature < extruderHigherTamperature) extruderTargetTamperature = extruderTargetTamperature + 1;
      sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(extruderTargetTamperature), " ", 0b11101111,"C      ");
      break;

      case BEDTEMPERATURENODETYPE:
      if (bedTargetTamperature < bedHigherTamperature) bedTargetTamperature = bedTargetTamperature + 1;
      sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(bedTargetTamperature), " ", 0b11101111,"C      ");
      break;
    }
  }
}

void pressedOk()
{
  switch (pcurrentMenuNode->nodeType)
  {
    case SIMPLENODETYPE:
    if(pcurrentMenuNode->rightNode != NULL)
    {
      pcurrentMenuNode=pcurrentMenuNode->rightNode;
      loadNewScreen(pcurrentMenuNode);
    }
    break;

    case PRINTNODETYPE:
    if (Appli_state == APPLICATION_START)
    {
      if (pcurrentMenuNode->mode == OFFMODE)
      {
        pcurrentMenuNode->mode = ONMODE;
        RootContentLinkedList();
        GoToTheFirstNode();
        loadFlashDriveContent(pNode);
      }else{
        OKfunction();
        if(pNode!=NULL){loadFlashDriveContent(pNode);}
      }
    }
    break;

    case EXTRUDERTEMPERATURENODETYPE:
    if (pcurrentMenuNode->mode == OFFMODE)
      {
      pcurrentMenuNode->mode = ONMODE;
      switch (CurrentLanguage)
        {
          case ENGLISH:
          sprintf(Text[0], "%s", "Extruder        ");
          sprintf(Text[1], "%s", "    temperature ");
          sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(extruderTargetTamperature), " ", 0b11101111,"C      ");
          sprintf(Text[3], "%s", "Press up or down");
          break;
          case RUSSIAN:
          sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'T','e',0b10111100,0b10111110,'e','p','a',0b10111111,'y','p','a',' ',' ',' ',' ',' ','\0');
          sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',' ',0b11000101,0b10111010,'c',0b10111111,'p','y',0b11100011,'e','p','a','\0');
          sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(extruderTargetTamperature), " ", 0b11101111,"C      ");
          sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'H','a',0b10110110,0b10111100,0b10111000,0b10111111,'e',' ',0b11011001,' ',0b10111000,0b10111011,0b10111000,' ',0b11011010,' ','\0');
          break;
          default:
          sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'T','e',0b10111100,0b10111110,'e','p','a',0b10111111,'y','p','a',' ',' ',' ',' ',' ','\0');
          sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',' ',0b11000101,0b10111010,'c',0b10111111,'p','y',0b11100011,'e','p','a','\0');
          sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(extruderTargetTamperature), " ", 0b11101111,"C      ");
          sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'H','a',0b10110110,0b10111100,0b10111000,0b10111111,'e',' ',0b11011001,' ',0b10111000,0b10111011,0b10111000,' ',0b11011010,' ','\0');
        }
      }
    break;
    case BEDTEMPERATURENODETYPE:
    if (pcurrentMenuNode->mode == OFFMODE)
      {
       pcurrentMenuNode->mode = ONMODE;
      switch (CurrentLanguage)
        {
          case ENGLISH:
          sprintf(Text[0], "%s", "Bed             ");
          sprintf(Text[1], "%s", "    temperature ");
          sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(bedTargetTamperature), " ", 0b11101111,"C      ");
          sprintf(Text[3], "%s", "Press up or down");
          break;
          case RUSSIAN:
          sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'T','e',0b10111100,0b10111110,'e','p','a',0b10111111,'y','p','a',' ',' ',' ',' ',' ','\0');
          sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','c',0b10111111,'o',0b10111011,'a','\0');
          sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(bedTargetTamperature), " ", 0b11101111,"C      ");
          sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'H','a',0b10110110,0b10111100,0b10111000,0b10111111,'e',' ',0b11011001,' ',0b10111000,0b10111011,0b10111000,' ',0b11011010,' ','\0');
          break;
          default:
          sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'T','e',0b10111100,0b10111110,'e','p','a',0b10111111,'y','p','a',' ',' ',' ',' ',' ','\0');
          sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','c',0b10111111,'o',0b10111011,'a','\0');
          sprintf(Text[2], "%s%s%s%c%s", "   ", NumberToString(bedTargetTamperature), " ", 0b11101111,"C      ");
          sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'H','a',0b10110110,0b10111100,0b10111000,0b10111111,'e',' ',0b11011001,' ',0b10111000,0b10111011,0b10111000,' ',0b11011010,' ','\0');
        }
      }
    break;

    case ABSPLASTICNODETYPE:
    plasticType = ABS;
    extruderTargetTamperature = ABSNORMEXTRUDERTEMPERATURE;
    extruderHigherTamperature = ABSHIGHEREXTRUDERTEMPERATURE;
    extruderLowerTamperature = ABSLOWEREXTRUDERTEMPERATURE;
    bedTargetTamperature = ABSNORMBEDTEMPERATURE;
    bedHigherTamperature = ABSHIGHERBEDTEMPERATURE;
    bedLowerTamperature = ABSLOWERBEDTEMPERATURE;
    switch (CurrentLanguage)
    {
      case ENGLISH:
      sprintf(Text[3], "%s",  "ABS selected    "); //Kostyl
      break;
      case RUSSIAN:
      sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'A','B','S',' ',0b10110011,0b11000011,0b10110010,'p','a',0b10111101,' ',' ',' ',' ',' ',' ','\0');
      break;
      default:
      sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'A','B','S',' ',0b10110011,0b11000011,0b10110010,'p','a',0b10111101,' ',' ',' ',' ',' ',' ','\0');
    }
    writeFlash();
    break;
    case PLAPLASTICNODETYPE:
    plasticType = PLA;
    extruderTargetTamperature = PLANORMEXTRUDERTEMPERATURE;
    extruderHigherTamperature = PLAHIGHEREXTRUDERTEMPERATURE;
    extruderLowerTamperature = PLALOWEREXTRUDERTEMPERATURE;
    bedTargetTamperature = PLANORMBEDTEMPERATURE;
    bedHigherTamperature = PLAHIGHERBEDTEMPERATURE;
    bedLowerTamperature = PLALOWERBEDTEMPERATURE;
    switch (CurrentLanguage)
    {
      case ENGLISH:
      sprintf(Text[3], "%s",  "PLA selected    "); //Kostyl
      break;
      case RUSSIAN:
      sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'P','L','A',' ',0b10110011,0b11000011,0b10110010,'p','a',0b10111101,' ',' ',' ',' ',' ',' ','\0');
      break;
      default:
      sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'P','L','A',' ',0b10110011,0b11000011,0b10110010,'p','a',0b10111101,' ',' ',' ',' ',' ',' ','\0');
    }
    writeFlash();
    break;

    case HELPNODETYPE:
    switch (CurrentLanguage)
    {
      case ENGLISH:
      sprintf(Text[0], "Manual          ");
      sprintf(Text[1], "and tutorials   ");
      sprintf(Text[2], "are available at");
      sprintf(Text[3], "www.webpage.com ");
      break;
      case RUSSIAN:
      sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10100101,0b10111101,'c',0b10111111,'p','y',0b10111010,0b11100101,0b10111000,0b11000111,' ',' ',' ',' ',' ',' ','\0');
      sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10111000,' ',0b10111111,'y',0b10111111,'o','p',0b10111000,'a',0b10111011,0b11000011,' ',' ',' ',' ',' ','\0');
      sprintf(Text[2], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10111101,'a',' ','c','a',0b10111001,0b10111111,'e',' ',' ',' ',' ',' ',' ',' ',' ','\0');
      sprintf(Text[3], "www.webpage.com ");
      break;
      default:
      sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10100101,0b10111101,'c',0b10111111,'p','y',0b10111010,0b11100101,0b10111000,0b11000111,' ',' ',' ',' ',' ',' ','\0');
      sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10111000,' ',0b10111111,'y',0b10111111,'o','p',0b10111000,'a',0b10111011,0b11000011,' ',' ',' ',' ',' ','\0');
      sprintf(Text[2], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10111101,'a',' ','c','a',0b10111001,0b10111111,'e',' ',' ',' ',' ',' ',' ',' ',' ','\0');
      sprintf(Text[3], "www.webpage.com ");
    }
    UpdateLCD = true;
    while(UpdateLCD) {}
    while(printerState!=PRESSEDBACK) {}
    loadNewScreen(pcurrentMenuNode);
    break;

    case CHANGEFILAMENTNODETYPE:
    switch (CurrentLanguage)
    {
      case ENGLISH:
      sprintf(Text[0], "CHANGE FILAMENT_");
      sprintf(Text[1], "up  -  pull     ");
      sprintf(Text[2], "down - push     ");
      sprintf(Text[3], "back - main menu");
      break;
      case RUSSIAN:
      sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'C','M','E','H',0b10100101,'T','b',' ',0b10101000,0b10100111,'A','C','T',0b10100101,'K','_','\0');
      sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b11011001,' ','-',' ',0b10111000,0b10110111,0b10110011,0b10111011,'e',0b11000000,0b11000100,' ',' ',' ',' ',' ','\0');
      sprintf(Text[2], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b11011010,' ','-',' ',0b10110011,'c',0b10111111,'a',0b10110011,0b10111000,0b10111111,0b11000100,' ',' ',' ',' ','\0');
      sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10111101,'a',0b10110111,'a',0b11100011,' ','-',' ',0b10110100,0b10111011,'.',' ',0b10111100,'e',0b10111101,0b11000110,'\0');
      break;
      default:
      sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 'C','M','E','H',0b10100101,'T','b',' ',0b10101000,0b10100111,'A','C','T',0b10100101,'K','_','\0');
      sprintf(Text[1], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b11011001,' ','-',' ',0b10111000,0b10110111,0b10110011,0b10111011,'e',0b11000000,0b11000100,' ',' ',' ',' ',' ','\0');
      sprintf(Text[2], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b11011010,' ','-',' ',0b10110011,'c',0b10111111,'a',0b10110011,0b10111000,0b10111111,0b11000100,' ',' ',' ',' ','\0');
      sprintf(Text[3], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10111101,'a',0b10110111,'a',0b11100011,' ','-',' ',0b10110100,0b10111011,'.',' ',0b10111100,'e',0b10111101,0b11000110,'\0');
    }
    UpdateLCD = true;
    while(UpdateLCD) {}
    while (printerState!=PRESSEDBACK)
    {
      MX_USB_HOST_Process();
      if (printerState==PRESSEDDOWN)
      {
        printerState=IDLE;
        translationBuffer = malloc(sizeof(moveNode));
        translationBuffer->previousNode = NULL;
        translationBuffer->nextNode = NULL;
        translationBuffer->translationX = CHANGEFILAMENTTRANSLATION; //FOR DEBUG
        translationBuffer->translationY = 0;
        translationBuffer->translationZ = 0;
        translationBuffer->translationE = 0; // CHANGEFILAMENTTRANSLATION should be placed here
        translationBuffer->translationLength = CHANGEFILAMENTTRANSLATION;
        translationBuffer->period = CHANGEFILAMENTSPEED;
        translationBuffer->smoothNext = true;
        translationBuffer->smoothPrevious = true;
        printFl=true;
        while (printFl) {}
        ClearMoveBufferNodes();
      }
      if (printerState==PRESSEDUP)
      {
        printerState=IDLE;
        translationBuffer = malloc(sizeof(moveNode));
        translationBuffer->previousNode = NULL;
        translationBuffer->nextNode = NULL;
        translationBuffer->translationX = -CHANGEFILAMENTTRANSLATION; //FOR DEBUG
        translationBuffer->translationY = 0;
        translationBuffer->translationZ = 0;
        translationBuffer->translationE = 0; // CHANGEFILAMENTTRANSLATION should be placed here
        translationBuffer->translationLength = CHANGEFILAMENTTRANSLATION;
        translationBuffer->period = CHANGEFILAMENTSPEED;
        translationBuffer->smoothNext = true;
        translationBuffer->smoothPrevious = true;
        printFl=true;
        while (printFl) {}
        ClearMoveBufferNodes();
      }
    }
    loadNewScreen(pcurrentMenuNode);
    break;

    case ENGLISHNODETYPE:
    CurrentLanguage = ENGLISH;
    SwitchToEnglish();
    loadNewScreen(pcurrentMenuNode);
    writeFlash();
    break;
    case RUSSIANNODETYPE:
    CurrentLanguage = RUSSIAN;
    SwitchToRussian();
    loadNewScreen(pcurrentMenuNode);
    writeFlash();
    break;
  }
}

void pressedBack()
{
  if(pcurrentMenuNode->mode == OFFMODE)
  {
    if(pcurrentMenuNode->leftNode != NULL)
    {
      pcurrentMenuNode=pcurrentMenuNode->leftNode;
      loadNewScreen(pcurrentMenuNode);
    }
  }else{
    switch(pcurrentMenuNode->nodeType)
    {
      case PRINTNODETYPE:
      if (pcurrentMenuNode->mode == ONMODE)
      {
        if(FindSlash(path)<0)
        {
          pcurrentMenuNode->mode = OFFMODE;
          sprintf(path,"\0");
          ClearNodes();
          loadNewScreen(pcurrentMenuNode);
        }else{
          BACKfunction();
          //GoToTheFirstNode();
          loadFlashDriveContent(pNode);
        }
      }
      break;

      case EXTRUDERTEMPERATURENODETYPE:
      pcurrentMenuNode->mode = OFFMODE;
      loadNewScreen(pcurrentMenuNode);
      if (data[2]!=extruderTargetTamperature) writeFlash();
      break;

      case BEDTEMPERATURENODETYPE:
      pcurrentMenuNode->mode = OFFMODE;
      loadNewScreen(pcurrentMenuNode);
      if (data[3]!=bedTargetTamperature) writeFlash();
      break;
    }
  }
}


//Update the Text for the LCD
//extern  char Text[4][TEXT_LENGTH];

char* getMenuNodeName(volatile menuNode * pmenuNode)
{
  if (pmenuNode == NULL)
  {
    return "                ";
  }else{
    return pmenuNode->name;
  }
}
/*{
  char str[16];
  if (pmenuNode == NULL)
  {
    sprintf(str,  "                ");
  }else{
    sprintf(str, pmenuNode->name);
  }
  return str;
}*/

void loadNewScreen(volatile menuNode * pmenuNode)
{
  longName = false;
  //PinD15Off();
  sprintf(Text[0], pmenuNode->title);
  //sprintf(Text[0], "%s.16", getMenuNodeTitle(pmenuNode));
  if ((pmenuNode->upNode == NULL)&&(pmenuNode->downNode != NULL))
  {
    sprintf(Text[1], "%s", getMenuNodeName(pmenuNode));
    sprintf(Text[2], "%s",  getMenuNodeName(pmenuNode->downNode));
    sprintf(Text[3], "%s",  getMenuNodeName(pmenuNode->downNode->downNode));
    Text[1][0] = '>';
  }else if((pmenuNode->upNode == NULL)&&(pmenuNode->downNode == NULL)){
    sprintf(Text[1], "%s", getMenuNodeName(pmenuNode));
    sprintf(Text[2], "%s",  getMenuNodeName(pmenuNode->downNode));
    sprintf(Text[3], "%s",  getMenuNodeName(pmenuNode->downNode));
    Text[1][0] = '>';
  }else if((pmenuNode->downNode == NULL)&&(pmenuNode->upNode->upNode == NULL)){
    sprintf(Text[1], "%s",  getMenuNodeName(pmenuNode->upNode));
    sprintf(Text[2], "%s",  getMenuNodeName(pmenuNode));
    sprintf(Text[3], "%s",  getMenuNodeName(pmenuNode->downNode));
    Text[2][0] = '>';
  }else if((pmenuNode->downNode == NULL)&&(pmenuNode->upNode->upNode != NULL)){
    sprintf(Text[1], "%s",  getMenuNodeName(pmenuNode->upNode->upNode));
    sprintf(Text[2], "%s",  getMenuNodeName(pmenuNode->upNode));
    sprintf(Text[3], "%s",  getMenuNodeName(pmenuNode));
    Text[3][0] = '>';
  }else{
    sprintf(Text[1], "%s", getMenuNodeName(pmenuNode->upNode));
    sprintf(Text[2], "%s",  getMenuNodeName(pmenuNode));
    sprintf(Text[3], "%s",  getMenuNodeName(pmenuNode->downNode));
    Text[2][0] = '>';
  }
}


//USB flash-drive content into char* Text

char* getFlashDrivePieceName(node * pFlashDriveNode)
{
  if (pFlashDriveNode == NULL)
  {
    return "                ";
  }else{
    return pFlashDriveNode->fno.fname;
  }
}

/*{
  volatile char str[16];
  volatile int i=1;
  volatile int j=0;
  if (pFlashDriveNode == NULL)
  {
    sprintf(str,  "                ");
  }else{
    str[0] = ' ';
    while((pFlashDriveNode->fno.fname[i-1] != 0)&&(i<16))
    {
      str[i]=(char)pFlashDriveNode->fno.fname[i-1];
      i+=1;
    }
    for (j=i; j<16; j++)
    {
      str[j]=' ';
    }
  }
  return str;
}*/


void loadFlashDriveContent(node * pFlashDriveNode)
{
    switch (CurrentLanguage)
    {
      case ENGLISH:
      sprintf(Text[0], "_SELECT A FILE__");
      break;
      case RUSSIAN:
      sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','B',0b10101110,0b10100000,'E','P',0b10100101,'T','E',' ',0b10101010,'A',0b10100110,0b10100111,'_','_','\0');
      break;
      default:
      sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','B',0b10101110,0b10100000,'E','P',0b10100101,'T','E',' ',0b10101010,'A',0b10100110,0b10100111,'_','_','\0');
    }
  int j1, j2;
  startTranslation = 2; //Because of '>' simbol
  for (j1=1; j1<4; j1++)
    {
      for(j2=0; j2<TEXT_LENGTH; j2++) //The length of Text!!!!!
      {
        Text[j1][j2] = '\0';
      }
    }
  if ((pFlashDriveNode->previousNode == NULL)&&(pFlashDriveNode->nextNode != NULL))
  {
    sprintf(Text[1], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode));
    sprintf(Text[2], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->nextNode));
    sprintf(Text[3], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->nextNode->nextNode));
    Text[1][0] = '>';
    if (FindNULL(Text[1])>16)
    {
      longName = true;
      currentOption = 1;
      maxTranslation = FindNULL(Text[1]) - 16;
      //PinD15On();
    }else{
      longName = false;
      currentOption = 1;
      //PinD15Off();
    }
  }else if((pFlashDriveNode->previousNode == NULL)&&(pFlashDriveNode->nextNode == NULL)){
    sprintf(Text[1], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode));
    sprintf(Text[2], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->nextNode));
    sprintf(Text[3], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->nextNode));
    Text[1][0] = '>';
    if (FindNULL(Text[1])>16)
    {
      longName = true;
      currentOption = 1;
      maxTranslation = FindNULL(Text[1]) - 16;
      //PinD15On();
    }else{
      longName = false;
      currentOption = 1;
      //PinD15Off();
    }
  }else if((pFlashDriveNode->nextNode == NULL)&&(pFlashDriveNode->previousNode->previousNode == NULL)){
    sprintf(Text[1], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->previousNode));
    sprintf(Text[2], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode));
    sprintf(Text[3], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->nextNode));
    Text[2][0] = '>';
    if (FindNULL(Text[2])>16)
    {
      longName = true;
      currentOption = 2;
      maxTranslation = FindNULL(Text[2]) - 16;
      //PinD15On();
    }else{
      longName = false;
      currentOption = 2;
      //PinD15Off();
    }
  }else if((pFlashDriveNode->nextNode == NULL)&&(pFlashDriveNode->previousNode->previousNode != NULL)){
    sprintf(Text[1], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->previousNode->previousNode));
    sprintf(Text[2], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->previousNode));
    sprintf(Text[3], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode));
    Text[3][0] = '>';
    if (FindNULL(Text[3])>16)
    {
      longName = true;
      currentOption = 3;
      maxTranslation = FindNULL(Text[3]) - 16;
      //PinD15On();
    }else{
      longName = false;
      currentOption = 3;
      //PinD15Off();
    }
  }else{
    sprintf(Text[1], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->previousNode));
    sprintf(Text[2], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode));
    sprintf(Text[3], "%s%s", " ", getFlashDrivePieceName(pFlashDriveNode->nextNode));
    Text[2][0] = '>';
    if (FindNULL(Text[2])>16)
    {
      longName = true;
      currentOption = 2;
      maxTranslation = FindNULL(Text[2]) - 16;
      //PinD15On();
    }else{
      longName = false;
      currentOption = 2;
      //PinD15Off();
    }
  }

}


void SwitchToEnglish()
{
sprintf(print.title, "%s", "___MAIN MENU____\0");
sprintf(print.name, "%s", " Print          \0");

sprintf(settings.title, "%s", "___MAIN MENU____\0");
sprintf(settings.name, "%s", " Settings       \0");

sprintf(typeOfPlastic.title, "%s", "____SETTINGS____\0");
sprintf(typeOfPlastic.name, "%s", " Type of plastic\0");

sprintf(ABSplastic.title, "%s", "TYPE OF PLASTIC_\0");
sprintf(ABSplastic.name, "%s", " ABS plastic    \0");

sprintf(PLAplastic.title, "%s", "TYPE OF PLASTIC_\0");
sprintf(PLAplastic.name, "%s", " PLA plastic    \0");

sprintf(extruderTemperature.title, "%s", "____SETTINGS____\0");
sprintf(extruderTemperature.name, "%s", " Extruder temp. \0");

sprintf(bedTemperature.title, "%s", "____SETTINGS____\0");
sprintf(bedTemperature.name, "%s", " Bed temp.      \0");

sprintf(printCube.title, "%s", "____SETTINGS____\0");
sprintf(printCube.name, "%s", " Print a cube   \0");

sprintf(language.title, "%s", "____SETTINGS____\0");
sprintf(language.name, "%s", " Language       \0");

sprintf(english.title, "%s", "____LANGUAGE____\0");
sprintf(english.name, "%s", " English        \0");

sprintf(russian.title, "%s", "____LANGUAGE____\0");
sprintf(russian.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','P','y','c','c',0b10111010,0b10111000,0b10111001,' ',' ',' ',' ',' ',' ',' ',' ','\0');

sprintf(changeFilament.title, "%s", "___MAIN MENU____\0");
sprintf(changeFilament.name, "%s", " Change filament\0");

sprintf(help.title, "%s", "___MAIN MENU____\0");
sprintf(help.name, "%s", " Help           \0");

}

void SwitchToRussian()
{
sprintf(print.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",'_','_',0b10100001,0b10100111,'A','B','H','O','E',' ','M','E','H',0b10110000,'_','_','\0');
sprintf(print.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ', 0b10101000, 'e', 0b11000000,'a',0b10111111, 0b11000100,' ',' ',' ',' ',' ',' ',' ',' ',' ','\0');

sprintf(settings.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",'_','_',0b10100001,0b10100111,'A','B','H','O','E',' ','M','E','H',0b10110000,'_','_','\0');
sprintf(settings.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",' ','H','a','c',0b10111111,'p','o',0b10111001,0b10111010,0b10111000,' ',' ',' ',' ',' ',' ','\0');

sprintf(typeOfPlastic.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','H','A','C','T','P','O',0b10100110,'K',0b10100101,'_','_','_','_','\0');
sprintf(typeOfPlastic.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','T',0b10111000,0b10111110,' ',0b10111110,0b10111011,'a','c',0b10111111,0b10111000,0b10111010,'a',' ',' ',' ','\0');

sprintf(ABSplastic.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','T',0b10100101,0b10101000,' ',0b10101000,0b10100111,'A','C','T',0b10100101,'K','A','_','_','\0');
sprintf(ABSplastic.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','A','B','S',' ',0b10111110,0b10111011,'a','c',0b10111111,0b10111000,0b10111010,' ',' ',' ',' ','\0');

sprintf(PLAplastic.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','T',0b10100101,0b10101000,' ',0b10101000,0b10100111,'A','C','T',0b10100101,'K','A','_','_','\0');
sprintf(PLAplastic.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','P','L','A',' ',0b10111110,0b10111011,'a','c',0b10111111,0b10111000,0b10111010,' ',' ',' ',' ','\0');

sprintf(extruderTemperature.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','H','A','C','T','P','O',0b10100110,'K',0b10100101,'_','_','_','_','\0');
sprintf(extruderTemperature.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','t',0b11101111,'C',' ',0b11000101,0b10111010,'c',0b10111111,'p','y',0b11100011,'e','p','a',' ',' ','\0');

sprintf(bedTemperature.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','H','A','C','T','P','O',0b10100110,'K',0b10100101,'_','_','_','_','\0');
sprintf(bedTemperature.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','t',0b11101111,'C',' ','c',0b10111111,'o',0b10111011,'a',' ',' ',' ',' ',' ',' ','\0');

sprintf(printCube.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','H','A','C','T','P','O',0b10100110,'K',0b10100101,'_','_','_','_','\0');
sprintf(printCube.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','H','a',0b10111110,'e',0b11000000,'a',0b10111111,'a',0b10111111,0b11000100,' ',0b10111010,'y',0b10110010,' ','\0');

sprintf(language.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','H','A','C','T','P','O',0b10100110,'K',0b10100101,'_','_','_','_','\0');
sprintf(language.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',0b10110001,0b10110111,0b11000011,0b10111010,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0');

sprintf(english.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','_','_','_',0b10110001,0b10100100,0b10101110,'K','_','_','_','_','_','_','\0');
sprintf(english.name, "%s", " English        \0");

sprintf(russian.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','_','_','_',0b10110001,0b10100100,0b10101110,'K','_','_','_','_','_','_','\0');
sprintf(russian.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ','P','y','c','c',0b10111010,0b10111000,0b10111001,' ',' ',' ',' ',' ',' ',' ',' ','\0');

sprintf(changeFilament.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",'_','_',0b10100001,0b10100111,'A','B','H','O','E',' ','M','E','H',0b10110000,'_','_','\0');
sprintf(changeFilament.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",' ','C',0b10111100,'e',0b10111101,0b10111000,0b10111111,0b11000100,' ',0b10111110,0b10111011,'a','c',0b10111111,0b10111000,0b10111010,'\0');

sprintf(help.title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",'_','_',0b10100001,0b10100111,'A','B','H','O','E',' ','M','E','H',0b10110000,'_','_','\0');
sprintf(help.name, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", ' ',0b10101000,'o',0b10111100,'o',0b11100110,0b11000100,' ',' ',' ',' ',' ',' ',' ',' ',' ','\0');

}



























char* MenuOption(volatile int* pointer)
{
  static char str[16];
  sprintf(str, "                ");
  switch (pointer[0])
  {
    case 1:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str," Print          ");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 1         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 2         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 3         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 4         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str," file 5         ");
              //sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 2:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str, " Settings       ");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Type of plastic");
              //sprintf(str,"____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " ABS plastic    ");
                  //sprintf(str,"TYPE OF PLASTIC_");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                sprintf(str, " PLA plastic    ");
                //sprintf(str,"TYPE OF PLASTIC_");
                break;
              }
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Extruder temp. ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Calibrate      ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " Yes, do it     ");
                  //sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " No, don't do it");
                  //sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Brightness     ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              sprintf(str, " Language       ");
              //sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " English        ");
                  //sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  sprintf(str, " Russian        ");
                  //sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 3:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str, " Change filament");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
    case 4:
    {
      switch (pointer[1])
      {
        case 0:
        {
          sprintf(str, " Help           ");
          //sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
  }
  return str;
}


char* MenuTitle(volatile int* pointer)
{
  static char str[16];
  sprintf(str, "                ");
  switch (pointer[0])
  {
    case 1:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str," Print          ");
          sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 1         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 2         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 3         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 4         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str," file 5         ");
              sprintf(str,"__SELECT FILE___");
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 2:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str, " Settings       ");
          sprintf(str,"___MAIN MENU____");
          break;
        }
        case 1:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Type of plastic");
              sprintf(str,"____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " ABS plastic    ");
                  sprintf(str,"TYPE OF PLASTIC_");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                //sprintf(str, " PLA plastic    ");
                sprintf(str,"TYPE OF PLASTIC_");
                break;
              }
              break;
            }
          }
          break;
        }
        case 2:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Extruder temp. ");
              sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 3:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Calibrate      ");
              sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " Yes, do it     ");
                  sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " No, don't do it");
                  sprintf(str, "___CALIBRATE?___");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
        case 4:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Brightness     ");
              sprintf(str, "____SETTINGS____");
              break;
            }
          }
          break;
        }
        case 5:
        {
          switch (pointer[2])
          {
            case 0:
            {
              //sprintf(str, " Language       ");
              sprintf(str, "____SETTINGS____");
              break;
            }
            case 1:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " English        ");
                  sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
            case 2:
            {
              switch (pointer[3])
              {
                case 0:
                {
                  //sprintf(str, " Russian        ");
                  sprintf(str, "____LANGUAGE____");
                  break;
                }
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case 3:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str, " Change filament");
          sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
    case 4:
    {
      switch (pointer[1])
      {
        case 0:
        {
          //sprintf(str, " Help           ");
          sprintf(str,"___MAIN MENU____");
          break;
        }
      }
      break;
    }
  }
  return str;
}
