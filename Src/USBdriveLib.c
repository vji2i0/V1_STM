#include "USBdriveLib.h"
#include "fatfs.h"
#include "usb_host.h"
#include "main.h"
#include <stdio.h>
#include "MenuLibrary.h"
#include "StatusLEDs.h"
#include <stdbool.h>
#include "gcode.h"
#include "global_variables.h"
#include "steps.h"
#include "MoveBuffer.h"



extern ApplicationTypeDef Appli_state;
FATFS USBDISKFatFs;
FIL MyFile;
extern USBH_HandleTypeDef hUsbHostFS;
volatile int fl=1;

volatile int ReadContentFlag=1;
volatile _Bool readString = false;


uint8_t rxBuffer = '\0';
uint8_t rxString[MAX_STRING_LENGTH];
int rxindex = 0;
int commentflag=1;
node * pNode = NULL; //This pointer is for the usb flash-drive
char path[MAX_PATH_LENGTH]="\0";
volatile _Bool UpdateProgressBar = false;

//Current and previous x and y translations
volatile long previousXtranslation = 0;
volatile long previousYtranslation = 0;
volatile long currentXtranslation = 0;
volatile long currentYtranslation = 0;
volatile long nextXtranslation = 0;
volatile long nextYtranslation = 0;
volatile _Bool smoothPrevious = false;
volatile _Bool smoothNext = false;
//for motor's timer
extern TIM_HandleTypeDef htim5;



//volatile _Bool DoStep = false;

void ErrorCase(void)
{
  //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  //ClearNodes();
  //MX_USB_HOST_Init();
  //MX_FATFS_Init();
  //Appli_state = APPLICATION_IDLE;
}
void FileReadWrite(void)
{
  FRESULT res;
  char rtext[100];
  UINT bytesread;
  if (f_mount(&USBDISKFatFs, (TCHAR const*)USBHPath, 0)!=FR_OK)
  {
    //sendStaicMessage((char *)"USB-drive mount error\n");
    //Error_Handler();
    ErrorCase();
  }else{
    if(f_open(&MyFile,"copy.txt",FA_READ)!=FR_OK)//this was changed
    {
      //sendStaicMessage((char *)"File open error\n");
      //Error_Handler();
      ErrorCase();
    }else{
      //sendStaicMessage("File open is OK.\n");
      res = f_read(&MyFile, rtext, sizeof(rtext), &bytesread);
      if((bytesread==0)||(res!=FR_OK))
      {
        //sendStaicMessage((char *)"File read error\n");
        ErrorCase();
      }else{
        if(fl)
        {
          //sendStaicMessage((uint8_t*)USBHPath);
          fl=0;
          rtext[bytesread]=0;
          //sendStaicMessage(rtext);
          f_close(&MyFile);
        }
      }
    }
  }
}
void ReadFileByString(void)
{
//sendStaicMessage("Function is called\n");
  char rtext[100];
/*
  res = f_read(&MyFile, rtext, sizeof(rtext),(void*)&bytesread);
  if((bytesread==0)||(res!=FR_OK))
  {
    sendStaicMessage("File read error\n");
    ErrorCase();
  }else{
    //sendStaicMessage((uint8_t*)USBHPath);
    rtext[bytesread]=0;
    sendStaicMessage(rtext);
  }
*/
  //for debug purposes
  //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  //for debug purposes
  //DoStep = true;
  readString = true;
  while ((f_eof(&MyFile) == 0))
  {
    while (!readString) {}
    if(pNode == NULL) {break;}
    readString = false;
    f_gets(rtext, sizeof(rtext), &MyFile);
    //sendStaicMessage(rtext);
    AnalyzeCommand(rtext);
    //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  }
}

void RootContentShort(void)
{
  FRESULT res;
  DIR dir;
//  UINT i;
  static FILINFO fno;
  char fileName[100];
  if (f_mount(&USBDISKFatFs, (TCHAR const*)USBHPath, 0)!=FR_OK)
  {
    //sendStaicMessage((char *)"USB-drive mount error\n");
    //Error_Handler();
    //fl=1;
    ErrorCase();
  }else{
    if(f_open(&MyFile,"1.txt",FA_READ)!=FR_OK)
    {
      //sendStaicMessage((char *)"File open error\n");
      ErrorCase();
    }else{
      //sendStaicMessage((char *)"File open OK\n");
      ReadFileByString(); //MyFile is global!
      //sendStaicMessage((char *)"THE END 2\n");
      f_close(&MyFile);
    }
  }
}

void RootContent(void)
{
  FRESULT res;
  DIR dir;
//  UINT i;
  static FILINFO fno;
  char fileName[100];
  if (f_mount(&USBDISKFatFs, (TCHAR const*)USBHPath, 0)!=FR_OK)
  {
    //sendStaicMessage((char *)"USB-drive mount error\n");
    //Error_Handler();
    fl=1;
    ErrorCase();
  }else{
    res = f_opendir(&dir, USBHPath);
    if(fl)
    {
      if (res!=FR_OK)
      {
        //sendStaicMessage("Directory open error\n");
        fl=1;
        ErrorCase();
      }else{
        //sendStaicMessage((char *)"Flash-drive content:\n");
        fl=0;
        res = f_readdir(&dir, &fno);
        while((res==FR_OK)&&(fno.fname[0] != 0))
        {
          if (fno.fattrib & AM_DIR)
          {
            sprintf(fileName, "%s%s\n", fno.fname, "/");
          }else{
            sprintf(fileName, "%s\n", fno.fname);
          }
          //sendStaicMessage(fileName);
          //sendStaicMessage((char *)"**********\n");
          if (fno.fattrib & AM_DIR)
          {
            //sendStaicMessage((char *)"This is foulder\n");
          }else{
            //sendStaicMessage((char *)"File found\n");
            if(f_open(&MyFile,fileName,FA_READ)!=FR_OK)
            {
              //sendStaicMessage((char *)"File open error\n");
              fl=1;
              ErrorCase();
            }else{
              //sendStaicMessage((char *)"File open OK\n");
              //ReadFileByString(); //MyFile is global!
              //sendStaicMessage((char *)"THE END 2\n");
              f_close(&MyFile);
            }
          }
          res = f_readdir(&dir, &fno);
        }
      }
    }
    //sendStaicMessage("Root content finishes\n");
    f_closedir(&dir);
  }
}

void RootContentLinkedList(void)
{
  //path initialization
  //sprintf(path, "%s", (char*)USBHPath);
  FRESULT res;
  DIR dir;
//  UINT i;
  //static FILINFO fno;
  FILINFO fno;
  if (f_mount(&USBDISKFatFs, (TCHAR const*)USBHPath, 0)!=FR_OK)
  {
    //sendStaicMessage((char *)"USB-drive mount error\n");
    //Error_Handler();
    ErrorCase();
  }else{
    res = f_opendir(&dir, USBHPath);
    if (res!=FR_OK)
    {
      //sendStaicMessage("Directory open error\n");
      ErrorCase();
    }else{
      //sendStaicMessage((char *)"Flash-drive content:\n");
      //path initialization
      //sprintf(path, "%s", (char*)USBHPath);
      //Dynamic mamory
      node * pBuf;
      pBuf = malloc(sizeof(node));
      pBuf->previousNode = NULL;
      pNode = pBuf;
      //Linked list gen
      do
      {
        res = f_readdir(&dir, &fno);
        pBuf->fno=fno; // Write the data to this node
        if ((res!=FR_OK)||(fno.fname[0] == 0)) // Check if the list ended
        {
          if (pNode->fno.fname[0] == 0) {pNode = NULL;} // Erase Linked List if empty
          pBuf->previousNode->nextNode=NULL;
          free(pBuf);
          pBuf = NULL;
          break;
        }
        pBuf->nextNode = malloc(sizeof(node)); // create next node
        pBuf->nextNode->previousNode = pBuf; //make a backward link
        pBuf = pBuf->nextNode; // move pointer to the next node
        /*if (fno.fattrib & AM_DIR)
        {
          sprintf(fileName, "%s%s\n", fno.fname, "/");
          sendStaicMessage((char *)"This is foulder named ");
          sendStaicMessage(fileName);
        }else{
          sprintf(fileName, "%s\n", fno.fname);
          sendStaicMessage((char *)"This is file named ");
          sendStaicMessage(fileName);
        }*/
      }while(1);//while((res==FR_OK)&&(fno.fname[0] != 0));
      // make the backward links
    }
    //sendStaicMessage("Root content finishes\n");
    f_closedir(&dir);
  }
}
void GoToTheFirstNode(void)
{
  if (pNode!=NULL)
  {
    do
    {
      if(pNode->previousNode==NULL)
      {
        break;
      }else{
       pNode=pNode->previousNode;
      }
    }while(1);
  }
}
void GoToTheLastNode(void)
{
  if (pNode!=NULL)
  {
    do
    {
      if(pNode->nextNode==NULL)
      {
        break;
      }else{
       pNode=pNode->nextNode;
      }
    }while(1);
  }
}
void ClearNodes(void)
{
  if (pNode!=NULL)
  {
    GoToTheLastNode();
    do
    {
      if(pNode->previousNode==NULL)
      {
        break;
      }else{
       pNode=pNode->previousNode;
       free(pNode->nextNode);
      }
    }while(1);
    free(pNode);
    pNode=NULL;
  }
}
void ShowRootContentLinkedList(void)
{
  char fileName[100];
  if (pNode==NULL)
  {
    //sendStaicMessage("Flash drive is empty\n");
  }else{
    do
    {
      if (pNode->fno.fattrib & AM_DIR)
      {
        sprintf(fileName, "%s%s\n", pNode->fno.fname, "/");
        //sendStaicMessage((char *)"This is foulder named ");
        //endStaicMessage(fileName);
      }else{
        sprintf(fileName, "%s\n", pNode->fno.fname);
        //sendStaicMessage((char *)"This is file named ");
        //sendStaicMessage(fileName);
      }
      if(pNode->nextNode==NULL)
      {
        break;
      }else{
       pNode=pNode->nextNode;
      }
    }while(1);
  }
  GoToTheFirstNode();
}
void FoulderContentLinkedList(void)
{
  FRESULT res;
  DIR dir;
  char folderPath[100];
  static FILINFO fno;
  GoToTheLastNode();
  if (pNode->fno.fattrib & AM_DIR)
  {
    sprintf(folderPath, "%s%s%s\n", (char*)USBHPath, "/", pNode->fno.fname);
    res = f_opendir(&dir, (TCHAR*)folderPath);
    if (res!=FR_OK)
    {
      //sendStaicMessage("Directory open error\n");
      ErrorCase();
    }else{
      //sendStaicMessage((char *)"Flash-drive content:\n");
      //Dynamic mamory
      node * pBuf;
      pBuf = malloc(sizeof(node));
      pBuf->previousNode = NULL;
      ClearNodes();
      pNode = pBuf;
      //Linked list gen
      do
      {
        res = f_readdir(&dir, &fno);
        pBuf->fno=fno; // Write the data to this node
        if ((res!=FR_OK)||(fno.fname[0] == 0)) // Check if the list ended
        {
          if (pNode->fno.fname[0] == 0) {pNode = NULL;} // Erase Linked List if empty
          pBuf->previousNode->nextNode=NULL;
          free(pBuf);
          pBuf = NULL;
          break;
        }
        pBuf->nextNode = malloc(sizeof(node)); // create next node
        pBuf->nextNode->previousNode = pBuf; //make a backward link
        pBuf = pBuf->nextNode; // move pointer to the next node
      }while(1);
    }
    //sendStaicMessage("Root content finishes\n");
    f_closedir(&dir);
  }
}

int FindSlash(char * string)
{
  int i=-1, j=0;
  for (j=0; j<=MAX_PATH_LENGTH; j++)
  {
    if(string[j]=='/') {i=j;}
    if(string[j]=='\0') {break;}
  }
  return i;
}

int FindNULL(char * string)
{
  int i=0, j=0;
  for (j=0; j<=MAX_PATH_LENGTH; j++)
  {
    if(string[j]=='\0')
    {
      i=j;
      break;//Added Do not work with this. Why???
      //return i; Do not work with this. Why???
    }
  }
  return i;
}

int FindDot(char * string)
{
  int i=-1, j=0;
  for (j=0; j<=MAX_PATH_LENGTH; j++)
  {
    if(string[j]=='.') {i=j;}
    if(string[j]=='\0') {break;}
  }
  return i;
}

_Bool IfGcode(char * string)
{
  int i;
  i = FindDot(string);
  if ((string[i+1] == 'g')&&(string[i+2] == 'c')&&(string[i+3] == 'o')&&(string[i+4] == 'd')&&(string[i+5] == 'e')&&(string[i+6] == '\0'))
  {
    return true;
  }else{
    return false;
  }
}

void ReadFile(void)
{
//  UINT i;
  char rtext[100];
  FIL MyFile1;
  char filePath[100];
  sprintf(filePath, "%s%s%s", path, "/", pNode->fno.fname);
  int NumberOfLines = 0;
  int line = 0;
  int progressBar = 0;

//How many strings
  if(f_open(&MyFile1,filePath,FA_READ)!=FR_OK)
  {
    ErrorCase();
  }else{
    while ((f_eof(&MyFile1) == 0))
    {
      if(pNode == NULL) {break;}
      NumberOfLines = NumberOfLines + 1;
      f_gets(rtext, sizeof(rtext), &MyFile1);
    }
    f_close(&MyFile1);
  }

//Read by string
  if(f_open(&MyFile1,filePath,FA_READ)!=FR_OK)
  {
    ErrorCase();
  }else{
    //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    //Clear MoveBuffer nodes
    //ClearMoveBufferNodes();
    //Create the first MoveBuffer node
    //translationBufferHead = malloc(sizeof(moveNode));
    //translationBufferHead->previousNode = NULL;
    //translationBufferHead->nextNode = NULL;
    //Reset the  counters
    numberOfCommandsRed=0;
    numberOfCommandsDone=0;
    //Set the location to be {0,0,0,0}
    //location.x=0;
    //location.y=0;
    //location.z=0;
    //location.e=0;
    //!!! Here the calibration should come!!!
    //Or the calibration should go imedialely after start?
    //Create the rest nodes


    //Read first BUFFERCAPACITY commands
    while ((numberOfCommandsRed<BUFFERCAPACITY)&&(f_eof(&MyFile1)==0))
    {
      f_gets(rtext, sizeof(rtext), &MyFile1);
      AnalyzeCommand(rtext);
    }
    //Set translationBufferTail
    GoToTheFirstMoveBufferNode();
    translationBufferTail=translationBufferHead;
    translationBuffer=translationBufferTail;
    GoToTheLastMoveBufferNode();

    //Print part
    if (translationBuffer!=NULL)
    {
      //Setting the LCD
      sprintf(Text[0], "____PRINTING____");
      int i;
      for (i=0; i<TEXT_LENGTH; i++)
      {
        Text[1][i] = '\0';
      }
      sprintf(Text[1], getFlashDrivePieceName(pNode));
      sprintf(Text[2], "Est. time       ");
      sprintf(Text[3], "Cur. time       ");
      UpdateLCD = true;
      while (UpdateLCD) {}
      if (FindNULL(Text[1])>16)
      {
        startTranslation=1;
        currentOption = 1;
        maxTranslation = FindNULL(Text[1]) - 16;
        longName = true;
        //PinD15On();
      }else{
        longName = false;
        startTranslation=1;
        currentOption = 1;
        //PinD15Off();
      }
      //Finish setting the LCD

      //Start printing
      htim5.Init.Period = C0;
      HAL_TIM_Base_Init(&htim5);
      printFl = true;

      while(f_eof(&MyFile1)==0) //While not end of file
      {
        while((numberOfCommandsDone+BUFFERCAPACITY)<numberOfCommandsRed) {}
        //Add the element to a head
        f_gets(rtext, sizeof(rtext), &MyFile1);
        AnalyzeCommand(rtext);

        //This part should never be executed
        if(printFl==false)
        {
          PinD15On();
          translationBuffer = translationBuffer->nextNode;
          if (translationBuffer->smoothPrevious)
          {
            printFl=true;
            htim5.Init.Period = translationBuffer->period;
            HAL_TIM_Base_Init(&htim5);
          }else{
            printFl=true;
            htim5.Init.Period = C0;
            HAL_TIM_Base_Init(&htim5);
          }
        }


        //Remove an element from a tail
        if(translationBufferTail != translationBuffer)
        {
          translationBufferTail=translationBufferTail->nextNode;
          free(translationBufferTail->previousNode);
          translationBufferTail->previousNode=NULL;
        }
        //Button BACK was pressed
        if((pNode == NULL)||(printerState==PRESSEDBACK))
        {
          printFl = false;
          htim5.Init.Period = C0;
          HAL_TIM_Base_Init(&htim5);
          ClearMoveBufferNodes(); //This is important
          translationBufferTail=NULL;
          translationBuffer=NULL;
          break;
        }
      }

      //
      while(printFl)
      {
        if((pNode == NULL)||(printerState==PRESSEDBACK))
        {
          printFl = false;
          htim5.Init.Period = C0;
          HAL_TIM_Base_Init(&htim5);
          ClearMoveBufferNodes(); //This is important
          translationBufferTail=NULL;
          translationBuffer=NULL;
          break;
        }
        //if (!printFl) HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
      }
      ClearMoveBufferNodes();
      translationBufferTail=NULL;
      translationBuffer=NULL;
      //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    }
  f_close(&MyFile1);
  }
}
void OpenFolder(void)
{
  char str[100];
  FRESULT res;
  DIR dir;
  static FILINFO fno;
  if (pNode->fno.fattrib & AM_DIR)
  {
    //if (FindNULL(path)<1)  //this
    //{  //this
      //sprintf(path, "%s%s", path, pNode->fno.fname);
      //sprintf(path, "%s", getFlashDrivePieceName(pNode));   //this
      //PinD15On();   //this
    //}else{   //this
      //PinD15Off();   //this
      sprintf(path, "%s%s%s", path, "/", pNode->fno.fname);
      //sprintf(str, "%s", path);
      //sprintf(path, "%s%s%s", str, "/", pNode->fno.fname);
    //}   //this
    res = f_opendir(&dir, (TCHAR*)path);
    if (res!=FR_OK)
    {
      //sprintf(path, "%s", (char*)USBHPath);
      //sendStaicMessage("Directory open error\n");
      ErrorCase();
      //Appli_state = APPLICATION_READY;
    }else{
      //sendStaicMessage(path);
      //sendStaicMessage("\n");
      //Dynamic mamory
      node * pBuf;
      pBuf = malloc(sizeof(node));
      pBuf->previousNode = NULL;
      ClearNodes();
      pNode = pBuf;
      //Linked list gen
      do
      {
        res = f_readdir(&dir, &fno);
        pBuf->fno=fno; // Write the data to this node
        if ((res!=FR_OK)||(fno.fname[0] == 0)) // Check if the list ended
        {
          if (pNode->fno.fname[0] == 0) {pNode = NULL;} // Erase Linked List if empty
          pBuf->previousNode->nextNode=NULL;
          free(pBuf);
          pBuf = NULL;
          break;
        }
        pBuf->nextNode = malloc(sizeof(node)); // create next node
        pBuf->nextNode->previousNode = pBuf; //make a backward link
        pBuf = pBuf->nextNode; // move pointer to the next node
      }while(1);
    }
    //sendStaicMessage("Root content finishes\n");
    f_closedir(&dir);
  }
}
void ShowNode(void)
{
  if (pNode!=NULL)
  {
    //sendStaicMessage(pNode->fno.fname);
    //sendStaicMessage("\n");
  }
}
void OKfunction(void)
{
  longName = false;
  int i;
  if (pNode!=NULL)
  {
    if(pNode->fno.fattrib & AM_DIR)
    {
      OpenFolder();
      GoToTheFirstNode();
      //ShowNode();
    }else if (IfGcode(pNode->fno.fname)){//Reads only if file.gcode
      //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
      //Print the progress window
      switch (CurrentLanguage)
      {
        case ENGLISH:
        sprintf(Text[0], "____PRINTING____");
        break;
        case RUSSIAN:
        sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','_','_',0b10101000,'E',0b10101011,'A','T','b','_','_','_','_','_','\0');
        break;
        default:
        sprintf(Text[0], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", '_','_','_','_','_',0b10101000,'E',0b10101011,'A','T','b','_','_','_','_','_','\0');
      }
      for (i=0; i<TEXT_LENGTH; i++)
      {
        Text[1][i] = '\0';
      }
      sprintf(Text[1], getFlashDrivePieceName(pNode));
      switch (CurrentLanguage)
      {
        case ENGLISH:
        sprintf(Text[2], " G-code loading ");
        break;
        case RUSSIAN:
        sprintf(Text[2], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10100100,'a',0b10110100,'p','y',0b10110111,0b10111010,'a',' ','G','-',0b10111010,'o',0b11100011,'a',' ','\0');
        break;
        default:
        sprintf(Text[2], "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 0b10100100,'a',0b10110100,'p','y',0b10110111,0b10111010,'a',' ','G','-',0b10111010,'o',0b11100011,'a',' ','\0');
      }
      sprintf(Text[3], "                ");
      UpdateLCD = true;
      while (UpdateLCD) {}
      if (FindNULL(Text[1])>16)
      {
        startTranslation=1;
        currentOption = 1;
        maxTranslation = FindNULL(Text[1]) - 16;
        longName = true;
        //PinD15On();
      }else{
        longName = false;
        startTranslation=1;
        currentOption = 1;
        //PinD15Off();
      }
      ReadFile();
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
      //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    }
  }
}
void BACKfunction(void)
{
  FRESULT res;
  DIR dir;
  FILINFO fno;
  int j, jStart = FindSlash(path);
  char foulderName[MAX_PATH_LENGTH];

  path[jStart]='\0';
  for(j=jStart+1; j<MAX_PATH_LENGTH; j++)
  {
    if (path[j]!='\0')
    {
      foulderName[j-jStart-1] = (char)path[j];
    }else
    {
      foulderName[j-jStart-1] = '\0';
    }
    path[j]='\0';
  }
  //sendStaicMessage(path);
  //sendStaicMessage("\n");
  res = f_opendir(&dir, (TCHAR*)path);
  if (res!=FR_OK)
  {
    sprintf(path, "%s", (char*)USBHPath);
    //sendStaicMessage("Directory open error\n");
    ErrorCase();
  }else{
    //Dynamic mamory
    node * pBuf;
    pBuf = malloc(sizeof(node));
    pBuf->previousNode = NULL;
    ClearNodes();
    pNode = pBuf;
    //Linked list gen
    do
    {
      res = f_readdir(&dir, &fno);
      pBuf->fno=fno; // Write the data to this node
      if ((res!=FR_OK)||(fno.fname[0] == 0)) // Check if the list ended
      {
        if (pNode->fno.fname[0] == 0) {pNode = NULL;} // Erase Linked List if empty
        pBuf->previousNode->nextNode=NULL;
        free(pBuf);
        pBuf = NULL;
        break;
      }
      pBuf->nextNode = malloc(sizeof(node)); // create next node
      pBuf->nextNode->previousNode = pBuf; //make a backward link
      pBuf = pBuf->nextNode; // move pointer to the next node
    }while(1);
  }
  //sendStaicMessage("Root content finishes\n");
  f_closedir(&dir);
  //return to the foulder in the list
  //GoToTheFirstNode();
  j=0;
  //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  do
  {
    if((foulderName[j]=='\0')&&(getFlashDrivePieceName(pNode)[j]=='\0'))
    {
      break;
    }
    if(foulderName[j]!=getFlashDrivePieceName(pNode)[j])
    {
      if(pNode->nextNode!=NULL)
      {
        pNode = pNode->nextNode;
        j=0;
        continue;
      }else{
        break;
      }
    }
    j=j+1;
  }while(1);

}


void UPfunction(void)
{
  if (pNode->previousNode != NULL)
  {
    pNode = pNode->previousNode;
  }
  ShowNode();
}
void DOWNfunction(void)
{
  if (pNode->nextNode != NULL)
  {
    pNode = pNode->nextNode;
  }
  ShowNode();
}

