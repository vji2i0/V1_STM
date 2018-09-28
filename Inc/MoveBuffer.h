#ifndef MoveBufferH
#define MoveBufferH

#include "fatfs.h"
#include "usb_host.h"
#include "config.h"



void GoToTheFirstMoveBufferNode(void);

void GoToTheLastMoveBufferNode(void);

void ClearMoveBufferNodes(void);

void SmoothTranslations(void);

#endif
