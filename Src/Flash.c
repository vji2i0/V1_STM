#include "Flash.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"
#include "usb_host.h"
#include "main.h"
#include "config.h"
#include "init.h"
#include "global_variables.h"

void writeFlash (void)
{
  data[0] = 1;
  data[1] = CurrentLanguage;
  data[2] = extruderTargetTamperature;
  data[3] = bedTargetTamperature;
  data[4] = plasticType;
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG( FLASH_FLAG_EOP |  FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
  FLASH_Erase_Sector(FLASH_SECTOR_11, FLASH_VOLTAGE_RANGE_3);
  int i;
  for(i=0; i<DATAPIECES; i++)
  {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, startAddress+sizeof(uint16_t)*i, (uint16_t)data[i]);
  }
  HAL_FLASH_Lock();
}

void readFlash (void)
{
  int i;
  for(i=0; i<DATAPIECES; i++)
  {
    data[i]=(*(uint16_t *)(startAddress+sizeof(uint16_t)*i));
  }
  CurrentLanguage = data[1];
  extruderTargetTamperature = data[2];
  bedTargetTamperature = data[3];
  plasticType = data[4];
}
