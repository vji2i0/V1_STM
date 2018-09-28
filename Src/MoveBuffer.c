#include "MoveBuffer.h"
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
#include "config.h"






void GoToTheFirstMoveBufferNode(void)
{
  if (translationBufferHead!=NULL)
  {
    do
    {
      if(translationBufferHead->previousNode==NULL)
      {
        break;
      }else{
       translationBufferHead=translationBufferHead->previousNode;
      }
    }while(1);
  }
}

void GoToTheLastMoveBufferNode(void)
{
  if (translationBufferHead!=NULL)
  {
    do
    {
      if(translationBufferHead->nextNode==NULL)
      {
        break;
      }else{
       translationBufferHead=translationBufferHead->nextNode;
      }
    }while(1);
  }
}

void ClearMoveBufferNodes(void)
{
  if (translationBufferHead!=NULL)
  {
    GoToTheLastMoveBufferNode();
    do
    {
      if(translationBufferHead->previousNode==NULL)
      {
        break;
      }else{
       translationBufferHead=translationBufferHead->previousNode;
       free(translationBufferHead->nextNode);
      }
    }while(1);
    free(translationBufferHead);
    translationBufferHead=NULL;
  }
}

void SmoothTranslations(void)
{
  _Bool condX;
  _Bool condY;
  _Bool condZ;
  _Bool condE;
  //Go to the first move node
  GoToTheFirstMoveBufferNode();
  if (translationBufferHead!=NULL)
  {
    translationBufferHead->smoothPrevious = false;
    while(translationBufferHead->nextNode!=NULL)
    {
      condX = ((((translationBufferHead->translationX)*(translationBufferHead->nextNode->translationX))>0)||((translationBufferHead->translationX==0)&&(translationBufferHead->nextNode->translationX==0)));
      condY = ((((translationBufferHead->translationY)*(translationBufferHead->nextNode->translationY))>0)||((translationBufferHead->translationY==0)&&(translationBufferHead->nextNode->translationY==0)));
      condZ = ((((translationBufferHead->translationZ)*(translationBufferHead->nextNode->translationZ))>0)||((translationBufferHead->translationZ==0)&&(translationBufferHead->nextNode->translationZ==0)));
      condE = ((((translationBufferHead->translationE)*(translationBufferHead->nextNode->translationE))>0)||((translationBufferHead->translationE==0)&&(translationBufferHead->nextNode->translationE==0)));
      translationBufferHead->smoothNext = (condX && condY && condZ && condE);
      translationBufferHead->nextNode->smoothPrevious = (condX && condY && condZ && condE);
      translationBufferHead = translationBufferHead->nextNode;
    }
    translationBufferHead->smoothNext = false;
    GoToTheFirstMoveBufferNode();
  }
}

void SmoothThisTranslation(void)
{
  _Bool condX;
  _Bool condY;
  _Bool condZ;
  _Bool condE;
  if (translationBufferHead->previousNode==NULL)
  {
    translationBufferHead->smoothPrevious = false;
  }else{
    condX = ((((translationBufferHead->previousNode->translationX)*(translationBufferHead->translationX))>0)||((translationBufferHead->previousNode->translationX==0)&&(translationBufferHead->translationX==0)));
    condY = ((((translationBufferHead->previousNode->translationY)*(translationBufferHead->translationY))>0)||((translationBufferHead->previousNode->translationY==0)&&(translationBufferHead->translationY==0)));
    condZ = ((((translationBufferHead->previousNode->translationZ)*(translationBufferHead->translationZ))>0)||((translationBufferHead->previousNode->translationZ==0)&&(translationBufferHead->translationZ==0)));
    condE = ((((translationBufferHead->previousNode->translationE)*(translationBufferHead->translationE))>0)||((translationBufferHead->previousNode->translationE==0)&&(translationBufferHead->translationE==0)));
    translationBufferHead->smoothPrevious = (condX && condY && condZ && condE);
    translationBufferHead->previousNode->smoothNext = (condX && condY && condZ && condE);
  }
}
