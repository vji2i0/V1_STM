#include "Temperature.h"
#include "config.h"
#include "stm32f4xx_hal.h"

unsigned int getTemperature_extruder(unsigned int adc_value){
    //return 127+83*adc_value/(16*100);
    return 83*adc_value/(16*10);
}

unsigned int getTemperature_bed(unsigned int adc_value){
    return 83*adc_value/(16*10);
}

void HeatExtruderEnable()
{
    HAL_GPIO_WritePin(HEAT_EXTRUDER_PORT, HEAT_EXTRUDER_PIN, SET);
}

void HeatExtruderDisable()
{
    HAL_GPIO_WritePin(HEAT_EXTRUDER_PORT, HEAT_EXTRUDER_PIN, RESET);
}

void HeatBedEnable()
{
    HAL_GPIO_WritePin(HEAT_BED_PORT, HEAT_BED_PIN, SET);
}

void HeatBedDisable()
{
    HAL_GPIO_WritePin(HEAT_BED_PORT, HEAT_BED_PIN, RESET);
}

