#ifndef LCD
#define LCD


#define LCD_DB0_PIN GPIO_PIN_6
#define LCD_DB0_PORT GPIOC
#define LCD_DB1_PIN GPIO_PIN_13
#define LCD_DB1_PORT GPIOC
#define LCD_DB2_PIN GPIO_PIN_8
#define LCD_DB2_PORT GPIOC
#define LCD_DB3_PIN GPIO_PIN_9
#define LCD_DB3_PORT GPIOC
#define LCD_DB4_PIN GPIO_PIN_8
#define LCD_DB4_PORT GPIOA
#define LCD_DB5_PIN GPIO_PIN_5
#define LCD_DB5_PORT GPIOE
#define LCD_DB6_PIN GPIO_PIN_8
#define LCD_DB6_PORT GPIOB
#define LCD_DB7_PIN GPIO_PIN_15
#define LCD_DB7_PORT GPIOA
#define LCD_RS_PIN GPIO_PIN_0
#define LCD_RS_PORT GPIOD
#define LCD_RW_PIN GPIO_PIN_2
#define LCD_RW_PORT GPIOD
#define LCD_ENABLE_PIN GPIO_PIN_6
#define LCD_ENABLE_PORT GPIOD
#define DELAY_TIME_BEFORE_ENABLE 2000
#define DELAY_TIME_BEFORE_DISABLE 4000
//Buttons
#define OK_PIN GPIO_PIN_10
#define OK_PORT GPIOB
#define BACK_PIN GPIO_PIN_12
#define BACK_PORT GPIOB
#define UP_PIN GPIO_PIN_14
#define UP_PORT GPIOB
#define DOWN_PIN GPIO_PIN_8
#define DOWN_PORT GPIOD



  void notExactTimeDelay(long timeDelay);

  void LCDSetToWrite(void);

  void LCDSetToRead(void);

  void LCDSetCommandMode(void);

  void LCDSetCharacterMode(void);

  void LCDEnableOn(void);

  void LCDEnableOff(void);

  void SetPins(void);

  void LCDSetACharacter(char character);

  void LCDSetACommand(char character);

  void LCDSetCursorPosition(int y, int x);

  void LCDSet(unsigned int phase);

  unsigned int LCDSetPeriodsToGo(unsigned int phase);


#endif
