#ifndef steps_H
#define steps_H
/*
    16 bit Timer/Counter 1 for stepper motors phase change
*/
#include <stdint.h>
#include "config.h"
//#include "global_variables.h"
//#include "gcode.h"

/*void moveOn(struct vector endpoint, float F);*/

_Bool smoothPath(long Px, long Py, long Cx, long Cy);

void moveOn(float F);

void doStep(signed char motor);


#endif
