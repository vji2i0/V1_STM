#include "init.h"
#include "global_variables.h"
#include "stm32f4xx_hal.h"
#include "config.h"
#include <stdbool.h>

/*
    Init global variables
*/
    struct vector placement = {0.0,0.0,0.0,0.0};
    struct vector location = {0.0,0.0,0.0,0.0};
    unsigned int current_temperature_extruder = 0;
    unsigned int current_temperature_bed = 0;
    uint8_t state0 = 0;

    moveNode * translationBuffer = NULL; 
    moveNode * translationBufferHead = NULL;
    moveNode * translationBufferTail = NULL;


    volatile _Bool printFl = false;

    //bed and extruder temperature
    volatile int extruderTargetTamperature = ABSNORMEXTRUDERTEMPERATURE;
    volatile int extruderHigherTamperature = ABSHIGHEREXTRUDERTEMPERATURE;
    volatile int extruderLowerTamperature = ABSLOWEREXTRUDERTEMPERATURE;
    volatile int bedTargetTamperature = ABSNORMBEDTEMPERATURE;
    volatile int bedHigherTamperature = ABSHIGHERBEDTEMPERATURE;
    volatile int bedLowerTamperature = ABSLOWERBEDTEMPERATURE;

    volatile _Bool heatOn = false; //should be false!!! true for debug only
    volatile _Bool DoStep = false; // Do step
    //Motors control
    signed char motorX = IDLE_MOTOR; //INC_X, DEC_X, IDLE_MOTOR
    signed char motorY = IDLE_MOTOR; //INC_X, DEC_X, IDLE_MOTOR
    signed char motorZ = IDLE_MOTOR; //INC_X, DEC_X, IDLE_MOTOR
    signed char motorE = IDLE_MOTOR; //INC_X, DEC_X, IDLE_MOTOR
    //Type of plastic used
    volatile int plasticType = ABS;
    //Current Languge
    volatile int CurrentLanguage = RUSSIAN;
    //Start adress for flash memory
    const volatile uint32_t startAddress = ADDR_FLASH_SECTOR_11;//16 Kbytes are available
        //0. [int] -- has the flash memory been used?
        //1. [int] -- CurrentLanguage;
        //2. [int] -- extruderTargetTamperature;
        //3. [int] -- bedTargetTamperature;
        //4. [int] -- plasticType
    //Initial parameters
    volatile int data[DATAPIECES] = {0, RUSSIAN, ABSNORMEXTRUDERTEMPERATURE, ABSNORMBEDTEMPERATURE, ABS};
    //The number of the commands done
    volatile long numberOfCommandsDone = 0;
    //The number of the commands red
    volatile long numberOfCommandsRed = 0;


