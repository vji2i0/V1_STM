/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include <stdbool.h>
#include "LCD.h"
#include "main.h"
#include "MenuLibrary.h"
#include "fatfs.h"
#include "usb_host.h"
#include "StatusLEDs.h"
#include "USBdriveLib.h"
#include "LibraryA4988.h"
#include "global_variables.h"
#include "config.h"
#include "steps.h"
#include "Temperature.h"




extern volatile unsigned int Lines;
extern volatile unsigned int MenuLayers;
extern volatile unsigned int CurrentLayer;
extern volatile int CurrentMenuPosition[MENU_LAYERS];
extern volatile int portAPin15Counter;
extern volatile _Bool SetLCD;
extern volatile unsigned int PeriodsToGo;
//extern volatile _Bool UpdateLCD;
extern volatile unsigned int PhaseLCD;
extern volatile const int TotalPhasesLCDSetup;
extern volatile const int TotalPhasesLCDUpdate;
//extern volatile char Text[4][TEXT_LENGTH];
extern volatile unsigned int colomn;
extern volatile unsigned int row;

/*For timer debouncing*/
extern volatile int jTimer;
extern volatile int jOnDOWN; //PC10
extern volatile int jOnUP; //PA15
extern volatile int jOnOK; //PB4
extern volatile int jOnBACK; //PB5
extern volatile const int CheckCircles;
extern volatile const int jOnThreshold;

/*Printer state*/
extern volatile int printerState;

//Menu node
extern volatile menuNode * pcurrentMenuNode;
//volatile struct menuNode *pcurrentMenuNode = & print;//print;
//extern struct menuNode * pcurrentMenuNode;

//For a USB Flash-Drive
extern ApplicationTypeDef Appli_state;

//For step

volatile int phaseStep = 1;


/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim12;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
*/
void TIM1_BRK_TIM9_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 0 */
  //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  if(DoStep)
  {
    switch(phaseStep)
    {
      case 1: //choose direction
      if (motorX == INC_X) ForwardX();
      if (motorX == DEC_X) BackwardX();
      if (motorY == INC_Y) ForwardY();
      if (motorY == DEC_Y) BackwardY();
      if (motorZ == INC_Z) ForwardZ();
      if (motorZ == DEC_Z) BackwardZ();
      if (motorE == INC_E) ForwardE();
      if (motorE == DEC_E) BackwardE();
      phaseStep = 2;
      break;
      case 2: //signal front formation
      if (motorX != IDLE_MOTOR) StepOnX();
      if (motorY != IDLE_MOTOR) StepOnY();
      if (motorZ != IDLE_MOTOR) StepOnZ();
      if (motorE != IDLE_MOTOR) StepOnE();
      phaseStep = 3;
      break;
      case 3: //signal back formation
      StepOffX();
      StepOffY();
      StepOffZ();
      StepOffE();
      phaseStep = 1;
      DoStep = false;
      break;
    }
  }
  /* USER CODE END TIM1_BRK_TIM9_IRQn 0 */
  HAL_TIM_IRQHandler(&htim9);
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM9_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  //pcurrentMenuNode = pcurrentMenuNode->downNode;
  //  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
  //  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
  //  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
  //  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
  jTimer+=1;
  if (HAL_GPIO_ReadPin(DOWN_PORT, DOWN_PIN) & GPIO_PIN_SET){//DOWN is pressed
    jOnDOWN+=1;
  }
  if (HAL_GPIO_ReadPin(UP_PORT, UP_PIN) & GPIO_PIN_SET){//UP is pressed
    jOnUP+=1;
  }
  if (HAL_GPIO_ReadPin(OK_PORT, OK_PIN) & GPIO_PIN_SET){//OK is pressed
    jOnOK+=1;
  }
  if (HAL_GPIO_ReadPin(BACK_PORT, BACK_PIN) & GPIO_PIN_SET){//BACK is pressed
    jOnBACK+=1;
  }

  if (jTimer == CheckCircles){
    if (jOnDOWN > jOnThreshold)
    {//Button DOWN is pressed
      printerState = PRESSEDDOWN;
    };//That is all for the button DOWN
    if (jOnUP > jOnThreshold)
    {//Button UP is pressed
      printerState = PRESSEDUP;
    };//That is all for the button UP
    if (jOnOK > jOnThreshold)
    {//Button OK is pressed
      printerState = PRESSEDOK;
    };//That is all for the button OK
    if (jOnBACK > jOnThreshold)
    {//Button BACK is pressed
      printerState = PRESSEDBACK;
    };//That is all for the button BACK
    jTimer=0;
    jOnUP=0;
    jOnDOWN=0;
    jOnOK=0;
    jOnBACK=0;
  }

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
  char character;
  static int jPeriod = 0;
  static _Bool UpdateLCD_prev = true;
  static _Bool UpdateLine = false;
  static int jTranslation = 0;
  static _Bool timeForUpdateProgressBar = false;

  static int colomnT = 1;
  if (!longName)
  {
    colomnT = 1;
    jTranslation = 0;
  }
  /*
  if(UpdateLCD_prev != UpdateLCD)
  {
   PeriodsToGo = 0;
   PhaseLCD = 1;
   jPeriod=0;
   UpdateLCD_prev = UpdateLCD;
   UpdateLine = false;
   colomn=1;
   row=1;
  }
  */
 if (UpdateLCD && (!UpdateProgressBar))
 {
  colomnT = 1;
  jTranslation = 0;
 }


  if (UpdateLCD)
  {
    if (PeriodsToGo == 0)
    {
      if (SetLCD)
      {
        if (UpdateLCD)
        {
          character = Text[row-1][colomn-1];
          if (character == '\0') character = ' ';
          LCDUpdate(PhaseLCD,character,row,colomn);
          PeriodsToGo = LCDUpdatePeriodsToGo(PhaseLCD);
          if (PhaseLCD == TotalPhasesLCDSetup)
          {
            PhaseLCD=1;
            colomn+=1;
            if (colomn>16)
            {
              colomn=1;
              row+=1;
              //This is new
              if (longName && UpdateProgressBar && (row == (currentOption+1)))
              {
                row+=1;
              }
            }
            if (row>4)
            {
              row=1;
              UpdateLCD=false;
              UpdateProgressBar=false;
            }
          }else{
            PhaseLCD+=1;
          }
        }
      }else{
        LCDSet(PhaseLCD);
        PeriodsToGo = LCDSetPeriodsToGo(PhaseLCD);
        if (PhaseLCD == TotalPhasesLCDSetup)
        {
          PhaseLCD=1;
          SetLCD=true;
          colomn=1;
          row=1;
        }else{
          PhaseLCD+=1;
        }
      }
    }else{PeriodsToGo-=1;}
  }



  if (UpdateLine)
  {
    if (PeriodsToGo == 0)
    {
      if(colomnT < startTranslation) colomnT = startTranslation;
      character = Text[currentOption][colomnT-1+jTranslation];
      if (character == '\0') character = ' ';
      LCDUpdate(PhaseLCD,character,currentOption+1,colomnT);
      PeriodsToGo = LCDUpdatePeriodsToGo(PhaseLCD);
      if (PhaseLCD == TotalPhasesLCDSetup)
      {
        PhaseLCD=1;
        colomnT=colomnT+1;
        if (colomnT>16)
        {
          UpdateLine=false;
          colomnT = startTranslation;
          //colomn=2;
        }
      }else{
        PhaseLCD+=1;
      }
    }else{PeriodsToGo-=1;}
  }


  if ((!UpdateLCD) && longName)//(UpdateLCD)
  {
    if(jPeriod < PERIODS_FOR_SLIDING)
    {
      jPeriod = jPeriod + 1;
    }else{
      jPeriod = 0;
      UpdateLine = true;
      jTranslation = jTranslation + 1;
      if (jTranslation > maxTranslation)
      {
        jTranslation = 0;
      }
      //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    }
  }


  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
    //MX_USB_HOST_Process();
      //MX_USB_HOST_Init();
      //MX_FATFS_Init();
    if (Appli_state == APPLICATION_START)
    {
      PinD12On();
      PinD13Off();
      PinD14Off();
    }else if (Appli_state == APPLICATION_IDLE){
      PinD12Off();
      PinD13On();
      PinD14Off();
    }else if (Appli_state == APPLICATION_READY){
      PinD12Off();
      PinD13Off();
      PinD14On();
    }else if (Appli_state == APPLICATION_DISCONNECT){
      //MX_USB_HOST_Init();
      //MX_FATFS_Init();
      PinD12Off();
      PinD13Off();
      PinD14Off();
      //Appli_state = APPLICATION_IDLE;
    }
    //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
* @brief This function handles TIM8 break interrupt and TIM12 global interrupt.
*/
void TIM8_BRK_TIM12_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_BRK_TIM12_IRQn 0 */

  static uint32_t ADCValue_extruder;
  static uint32_t ADCValue_bed;

  HAL_ADC_Start(&hadc1);
  if (HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK)
  {
    // Get the values from ADC
    ADCValue_extruder = HAL_ADC_GetValue(&hadc1);
    // Translate ADC values to the temperatures
    current_temperature_extruder=getTemperature_extruder((unsigned int) ADCValue_extruder);
  }
  HAL_ADC_Stop(&hadc1);

  HAL_ADC_Start(&hadc2);
  if (HAL_ADC_PollForConversion(&hadc2, 1000000) == HAL_OK)
  {
    // Get the values from ADC
    ADCValue_bed = HAL_ADC_GetValue(&hadc2);
    // Translate ADC values to the temperatures
    current_temperature_bed=getTemperature_bed((unsigned int) ADCValue_bed);
  }
  HAL_ADC_Stop(&hadc2);

  if (heatOn)
  {
    if (extruderTargetTamperature + TEMPERATURE_WINDOW > current_temperature_extruder)
    {
      HeatExtruderEnable();
      //PinD15On(); //For debug
    }else{
      HeatExtruderDisable();
      //PinD15Off(); //For debug
    }

    if (/*bedTargetTamperature*/extruderTargetTamperature + TEMPERATURE_WINDOW > current_temperature_bed)
    {
      HeatBedEnable();
      //PinD15On(); //For debug
    }else{
      HeatBedDisable();
      //PinD15Off(); //For debug
    }
  }else{
    HeatExtruderDisable();
    HeatBedDisable();
  }

  /* USER CODE END TIM8_BRK_TIM12_IRQn 0 */
  HAL_TIM_IRQHandler(&htim12);
  /* USER CODE BEGIN TIM8_BRK_TIM12_IRQn 1 */

  /* USER CODE END TIM8_BRK_TIM12_IRQn 1 */
}

/**
* @brief This function handles TIM5 global interrupt.
*/
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */
  //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  static int i = 0;
  static int steps_with_acc = 0;
  static long progressX = 0;
  static long progressY = 0;
  static long progressZ = 0;
  static long progressE = 0;


  if (printFl/*state0 & NEW_TASK*/)
  {
    //This is new
    motorX = IDLE_MOTOR;
    motorY = IDLE_MOTOR;
    motorZ = IDLE_MOTOR;
    motorE = IDLE_MOTOR;

    if (translationBuffer->translationX > 0){
      if (progressX*translationBuffer->translationLength < i*translationBuffer->translationX){
        progressX += 1;
        motorX = INC_X;
      }
    }else if (translationBuffer->translationX < 0){
      if (progressX*translationBuffer->translationLength > i*translationBuffer->translationX){
        progressX += 1;
        motorX = DEC_X;
      }
    }
    if (translationBuffer->translationY > 0){
      if (progressY*translationBuffer->translationLength < i*translationBuffer->translationY){
        progressY += 1;
        motorY = INC_Y;
      }
    }else if (translationBuffer->translationY < 0){
      if (progressY*translationBuffer->translationLength > i*translationBuffer->translationY){
        progressY -= 1;
        motorY = DEC_Y;
      }
    }
    if (translationBuffer->translationZ > 0){
      if (progressZ*translationBuffer->translationLength < i*translationBuffer->translationZ){
        progressZ += 1;
        motorZ = INC_Z;
      }
    }else if (translationBuffer->translationZ < 0){
      if (progressZ*translationBuffer->translationLength > i*translationBuffer->translationZ){
        progressZ -= 1;
        motorZ = DEC_Z;
      }
    }
    if (translationBuffer->translationE > 0){
      if (progressE*translationBuffer->translationLength < i*translationBuffer->translationE){
        progressE += 1;
        motorE = INC_E;
      }
    }else if (translationBuffer->translationE < 0){
      if (progressE*translationBuffer->translationLength > i*translationBuffer->translationE){
        progressE -= 1;
        motorE = DEC_E;
      }
    }
    //Make a step, see &htim9, void TIM1_BRK_TIM9_IRQHandler(void)
    DoStep = true;
    //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);

    if (i < translationBuffer->translationLength)
    {
      i++;
      if (translationBuffer->translationLength - i >= steps_with_acc)
      {
        //if (smoothPath(previousXtranslation, previousYtranslation, currentXtranslation, currentYtranslation))
        if (translationBuffer->smoothPrevious)//smooth previous
        {
          htim5.Init.Period = translationBuffer->period;
          HAL_TIM_Base_Init(&htim5);
          if(counter >= translationBuffer->period)
          {
            steps_with_acc++;
            counter = counter - 2*counter/(4*i + 1);
          }
        }else{
          if (htim5.Init.Period != translationBuffer->period){
            steps_with_acc++;
            counter = counter - 2*counter/(4*i + 1);
            if (counter >= translationBuffer->period){
              htim5.Init.Period = counter;
              HAL_TIM_Base_Init(&htim5);
            }else{
              htim5.Init.Period = translationBuffer->period;
              HAL_TIM_Base_Init(&htim5);
            }
          }
        }
      }else{
        //if (!smoothPath(currentXtranslation, currentYtranslation, nextXtranslation, nextYtranslation))
        if (translationBuffer->smoothNext)//smooth next
        {
          htim5.Init.Period = translationBuffer->period;
          HAL_TIM_Base_Init(&htim5);
        }else{
          //Start deceleration
          //htim5.Init.Period = htim5.Init.Period - 2*htim5.Init.Period/(4*(translationBuffer->translationLength - i - 2*steps_with_acc) + 1);
          htim5.Init.Period = htim5.Init.Period + htim5.Init.Period/(4*(translationBuffer->translationLength - i) + 1);
          HAL_TIM_Base_Init(&htim5);
        }
      }
/*

      if (i >= translation_discret_length/2){
        if (OCR1A > kappa){
          counter = counter - 2*counter/(4*(i - translation_discret_length) + 1);
        }
      }else{
        counter = counter - 2*counter/(4*i + 1);
        if (counter >= kappa){
          OCR1A = counter;
        }else{
          OCR1A = kappa;
        }
      }
*/
      //OCR1A = OCR1A - 2*OCR1A/(4*i + 1);
    }else{
      /*
        When task has been complete
      */
      numberOfCommandsDone+=1; //Counter of completed commands
      counter = C0;
      i = 0;
      progressX = 0;
      progressY = 0;
      progressZ = 0;
      progressE = 0;
      steps_with_acc = 0;
      if (translationBuffer->nextNode == NULL)
      {
        //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
        //state0 &= ~NEW_TASK;
        printFl=false;
      }else{
        translationBuffer = translationBuffer->nextNode;
        if (translationBuffer->smoothPrevious)
        {
          htim5.Init.Period = translationBuffer->period;
          HAL_TIM_Base_Init(&htim5);
        }else{
          htim5.Init.Period = C0;
          HAL_TIM_Base_Init(&htim5);
        }

      }
    }
  }else{
    /*
    state0 &= ~NEW_TASK;
    i = 0;
    counter = C0;
    htim5.Init.Period = C0;
    HAL_TIM_Base_Init(&htim5);
    readString = true;
    */
    counter = C0;
    progressX = 0;
    progressY = 0;
    progressZ = 0;
    progressE = 0;
  }


  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */

  /* USER CODE END TIM5_IRQn 1 */
}

/**
* @brief This function handles USB On The Go FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
