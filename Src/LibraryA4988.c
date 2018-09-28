#include "LibraryA4988.h"
#include "stm32f4xx_hal.h"
#include "LCD.h"

//X
void EnableX(void)
{
  HAL_GPIO_WritePin(ENABLE_X_PORT, ENABLE_X_PIN, GPIO_PIN_SET);
}
void DisableX(void)
{
  HAL_GPIO_WritePin(ENABLE_X_PORT, ENABLE_X_PIN, GPIO_PIN_RESET);
}
void ForwardX(void)
{
  HAL_GPIO_WritePin(DIRECTION_X_PORT, DIRECTION_X_PIN, GPIO_PIN_SET);
}
void BackwardX(void)
{
  HAL_GPIO_WritePin(DIRECTION_X_PORT, DIRECTION_X_PIN, GPIO_PIN_RESET);
}
void StepOnX(void)
{
  HAL_GPIO_WritePin(STEP_X_PORT, STEP_X_PIN, GPIO_PIN_SET);
}
void StepOffX(void)
{
  HAL_GPIO_WritePin(STEP_X_PORT, STEP_X_PIN, GPIO_PIN_RESET);
}
//Y
void EnableY(void)
{
  HAL_GPIO_WritePin(ENABLE_Y_PORT, ENABLE_Y_PIN, GPIO_PIN_SET);
}
void DisableY(void)
{
  HAL_GPIO_WritePin(ENABLE_Y_PORT, ENABLE_Y_PIN, GPIO_PIN_RESET);
}
void ForwardY(void)
{
  HAL_GPIO_WritePin(DIRECTION_Y_PORT, DIRECTION_Y_PIN, GPIO_PIN_SET);
}
void BackwardY(void)
{
  HAL_GPIO_WritePin(DIRECTION_Y_PORT, DIRECTION_Y_PIN, GPIO_PIN_RESET);
}
void StepOnY(void)
{
  HAL_GPIO_WritePin(STEP_Y_PORT, STEP_Y_PIN, GPIO_PIN_SET);
}
void StepOffY(void)
{
  HAL_GPIO_WritePin(STEP_Y_PORT, STEP_Y_PIN, GPIO_PIN_RESET);
}
//Z
void EnableZ(void)
{
  HAL_GPIO_WritePin(ENABLE_Z_PORT, ENABLE_Z_PIN, GPIO_PIN_SET);
}
void DisableZ(void)
{
  HAL_GPIO_WritePin(ENABLE_Z_PORT, ENABLE_Z_PIN, GPIO_PIN_RESET);
}
void ForwardZ(void)
{
  HAL_GPIO_WritePin(DIRECTION_Z_PORT, DIRECTION_Z_PIN, GPIO_PIN_SET);
}
void BackwardZ(void)
{
  HAL_GPIO_WritePin(DIRECTION_Z_PORT, DIRECTION_Z_PIN, GPIO_PIN_RESET);
}
void StepOnZ(void)
{
  HAL_GPIO_WritePin(STEP_Z_PORT, STEP_Z_PIN, GPIO_PIN_SET);
}
void StepOffZ(void)
{
  HAL_GPIO_WritePin(STEP_Z_PORT, STEP_Z_PIN, GPIO_PIN_RESET);
}
//E
void EnableE(void)
{
  HAL_GPIO_WritePin(ENABLE_E_PORT, ENABLE_E_PIN, GPIO_PIN_SET);
}
void DisableE(void)
{
  HAL_GPIO_WritePin(ENABLE_E_PORT, ENABLE_E_PIN, GPIO_PIN_RESET);
}
void ForwardE(void)
{
  HAL_GPIO_WritePin(DIRECTION_E_PORT, DIRECTION_E_PIN, GPIO_PIN_SET);
}
void BackwardE(void)
{
  HAL_GPIO_WritePin(DIRECTION_E_PORT, DIRECTION_E_PIN, GPIO_PIN_RESET);
}
void StepOnE(void)
{
  HAL_GPIO_WritePin(STEP_E_PORT, STEP_E_PIN, GPIO_PIN_SET);
}
void StepOffE(void)
{
  HAL_GPIO_WritePin(STEP_E_PORT, STEP_E_PIN, GPIO_PIN_RESET);
}
