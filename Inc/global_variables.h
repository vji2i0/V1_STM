/*
	Global variables
*/
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "global_variables.h"
#include "config.h"
#include "stm32f4xx_hal.h"
#include "USBdriveLib.h"
#include "main.h"
#include <stdbool.h>


extern struct vector location;
extern struct vector placement;

extern uint8_t state0;
extern unsigned int current_temperature_extruder;
extern unsigned int current_temperature_bed;

extern struct discret_vector translation_discret;
extern long translation_discret_length;
extern struct discret_vector progress;
extern long counter;
extern long kappa;

extern char path[MAX_PATH_LENGTH];
extern node * pNode;
extern volatile menuNode * pcurrentMenuNode;
extern volatile _Bool UpdateLCD;

extern TIM_HandleTypeDef htim5;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;


extern volatile _Bool readString;
extern FIL MyFile;
extern volatile int printerState;

extern volatile _Bool longName;
extern volatile int currentOption;
extern volatile int maxTranslation;
extern volatile int startTranslation;
extern volatile char Text[4][TEXT_LENGTH];
extern volatile _Bool UpdateProgressBar;
//Current and previous x and y translations
extern volatile long previousXtranslation;
extern volatile long previousYtranslation;
extern volatile long currentXtranslation;
extern volatile long currentYtranslation;
extern volatile long nextXtranslation;
extern volatile long nextYtranslation;
extern volatile _Bool smoothPrevious;
extern volatile _Bool smoothNext;

extern moveNode * translationBuffer;
extern moveNode * translationBufferHead;
extern moveNode * translationBufferTail;
//flag for printing
extern volatile _Bool printFl;
//Temperature control
extern volatile int extruderTargetTamperature;
extern volatile int extruderHigherTamperature;
extern volatile int extruderLowerTamperature;
extern volatile int bedTargetTamperature;
extern volatile int bedHigherTamperature;
extern volatile int bedLowerTamperature;

//Bed and extruder heat on or off
extern volatile _Bool heatOn;
//Do step
extern volatile _Bool DoStep;
//Motors control
extern signed char motorX; //INC_X, DEC_X, IDLE_MOTOR
extern signed char motorY; //INC_X, DEC_X, IDLE_MOTOR
extern signed char motorZ; //INC_X, DEC_X, IDLE_MOTOR
extern signed char motorE; //INC_X, DEC_X, IDLE_MOTOR


//Type of plastic used
extern volatile int plasticType;

//Current language
extern volatile int CurrentLanguage;

//Start address for flash memory
extern const volatile uint32_t startAddress;
    //0. [int] -- has the flash memory been used?
    //1. [int] -- CurrentLanguage;
    //2. [int] -- extruderTargetTamperature;
    //3. [int] -- bedTargetTamperature;
    //4. [int] -- plasticType
extern volatile int data[DATAPIECES];

//For buffer
//The number of the commands done
extern volatile long numberOfCommandsDone;
//The number of the commands red
extern volatile long numberOfCommandsRed;



//The list of the menu nodes
extern volatile  menuNode print;
extern volatile  menuNode settings;
    extern volatile  menuNode typeOfPlastic;
        extern volatile   menuNode ABSplastic;
        extern volatile  menuNode PLAplastic;
    extern volatile  menuNode extruderTemperature;
    extern volatile  menuNode bedTemperature;
    extern volatile  menuNode printCube;
    extern volatile  menuNode language;
        extern volatile  menuNode english;
        extern volatile  menuNode russian;
extern volatile  menuNode changeFilament;
extern volatile  menuNode help;

//extern ADC_HandleTypeDef hadc1;
/*
	state0 - control byte
	0b
	1 - 0 - we can't move, 1 - we can move
	2 - 0 - absolute, 1 - relative positioning
	3 - 0 - no CRS check, 1 - CRC check
	4
	5
	6
	7
	8
*/
#endif
