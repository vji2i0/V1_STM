#include "LCD.h"
#include "stm32f4xx_hal.h"




  void notExactTimeDelay(long timeDelay)
  {
    volatile long i;
    for(i=0; i<timeDelay; i++)
    {

    }
  }

  void LCDSetToWrite()
  {
    HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);
  }

  void LCDSetToRead()
  {
    HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_SET);
  }

  void LCDSetCommandMode()
  {
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
  }

  void LCDSetCharacterMode()
  {
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);
  }

  void LCDEnableOn()
  {
    HAL_GPIO_WritePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, GPIO_PIN_SET);
  }

  void LCDEnableOff()
  {
    HAL_GPIO_WritePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, GPIO_PIN_RESET);
  }


  void SetPins()
  {
    HAL_GPIO_WritePin(LCD_DB0_PORT, LCD_DB0_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB1_PORT, LCD_DB1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB2_PORT, LCD_DB2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB3_PORT, LCD_DB3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB4_PORT, LCD_DB4_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB5_PORT, LCD_DB5_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB6_PORT, LCD_DB6_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DB7_PORT, LCD_DB7_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, GPIO_PIN_RESET);
  }

  void LCDSetACharacter(char character)
  {
    if (character & 0b00000001)
    {
      HAL_GPIO_WritePin(LCD_DB0_PORT, LCD_DB0_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB0_PORT, LCD_DB0_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00000010)
    {
      HAL_GPIO_WritePin(LCD_DB1_PORT, LCD_DB1_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB1_PORT, LCD_DB1_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00000100)
    {
      HAL_GPIO_WritePin(LCD_DB2_PORT, LCD_DB2_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB2_PORT, LCD_DB2_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00001000)
    {
      HAL_GPIO_WritePin(LCD_DB3_PORT, LCD_DB3_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB3_PORT, LCD_DB3_PIN, GPIO_PIN_RESET);
    }
    if (character & 0b00010000)
    {
      HAL_GPIO_WritePin(LCD_DB4_PORT, LCD_DB4_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB4_PORT, LCD_DB4_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00100000)
    {
      HAL_GPIO_WritePin(LCD_DB5_PORT, LCD_DB5_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB5_PORT, LCD_DB5_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b01000000)
    {
      HAL_GPIO_WritePin(LCD_DB6_PORT, LCD_DB6_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB6_PORT, LCD_DB6_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b10000000)
    {
      HAL_GPIO_WritePin(LCD_DB7_PORT, LCD_DB7_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB7_PORT, LCD_DB7_PIN, GPIO_PIN_RESET);
    }
  }

  void LCDSetACommand(char character)
  {
    if (character & 0b00000001)
    {
      HAL_GPIO_WritePin(LCD_DB0_PORT, LCD_DB0_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB0_PORT, LCD_DB0_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00000010)
    {
      HAL_GPIO_WritePin(LCD_DB1_PORT, LCD_DB1_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB1_PORT, LCD_DB1_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00000100)
    {
      HAL_GPIO_WritePin(LCD_DB2_PORT, LCD_DB2_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB2_PORT, LCD_DB2_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00001000)
    {
      HAL_GPIO_WritePin(LCD_DB3_PORT, LCD_DB3_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB3_PORT, LCD_DB3_PIN, GPIO_PIN_RESET);
    }
    if (character & 0b00010000)
    {
      HAL_GPIO_WritePin(LCD_DB4_PORT, LCD_DB4_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB4_PORT, LCD_DB4_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b00100000)
    {
      HAL_GPIO_WritePin(LCD_DB5_PORT, LCD_DB5_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB5_PORT, LCD_DB5_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b01000000)
    {
      HAL_GPIO_WritePin(LCD_DB6_PORT, LCD_DB6_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB6_PORT, LCD_DB6_PIN, GPIO_PIN_RESET);
    }

    if (character & 0b10000000)
    {
      HAL_GPIO_WritePin(LCD_DB7_PORT, LCD_DB7_PIN, GPIO_PIN_SET);
    }else{
      HAL_GPIO_WritePin(LCD_DB7_PORT, LCD_DB7_PIN, GPIO_PIN_RESET);
    }
  }


  void LCDSetCursorPosition(int y, int x)
  {
    int row = 0;
    int colomn = 0;
    switch (y)
    {
      case 1: row = 0;
      break;
      case 2: row = 4;
      break;
      case 3: row = 1;
      break;
      case 4: row = 5;
    }
    if ((x>=1) && (x<=16))
    {
      colomn = x-1;
    }else{
      row=0;
      colomn=0;
    }
    LCDSetACommand(0b10000000+16*row+colomn);
  }

  void LCDSet(unsigned int phase)
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
        LCDSetACommand(0b00111000); //Set the number of the lines
        break;
      }
      case 4:
      {
        LCDEnableOff();
        break;
      }
      case 5:
      {
        LCDEnableOn();
        break;
      }
      case 6:
      {
        LCDSetACommand(0b00001100); // LCDSetACommand(0b00001110);
        break;
      }
      case 7:
      {
        LCDEnableOff();
        break;
      }
      case 8:
      {
        LCDEnableOn();
        break;
      }
      case 9:
      {
        LCDSetACommand(0b00000001); //Clear display
        break;
      }
      case 10:
      {
        LCDEnableOff();
        break;
      }
      case 11:
      {
        LCDEnableOn();
        break;
      }
      case 12:
      {
        LCDSetACommand(0b00000110);
        break;
      }
      case 13:
      {
        LCDEnableOff();
        break;
      }
    }
  }

  unsigned int LCDSetPeriodsToGo(unsigned int phase)
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
        j=9;
        break;
      }
      case 8:
      {
        j=0;
        break;
      }
      case 9:
      {
        j=0;
        break;
      }
      case 10:
      {
        j=9;
        break;
      }
      case 11:
      {
        j=0;
        break;
      }
      case 12:
      {
        j=0;
        break;
      }
      case 13:
      {
        j=40;
        break;
      }
     }
    return j;
  }
