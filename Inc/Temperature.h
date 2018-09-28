#ifndef Temperature_H
#define Temperature_H

unsigned int getTemperature_extruder(unsigned int adc_value);

unsigned int getTemperature_bed(unsigned int adc_value);

void HeatExtruderEnable();

void HeatExtruderDisable();

void HeatBedEnable();

void HeatBedDisable();

#endif
