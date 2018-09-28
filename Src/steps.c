#include "steps.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "global_variables.h"
#include "config.h"
#include "LibraryA4988.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
//#include "DriverControl.h"




const char DRIVE_PHASES_X[] = {0b10000000,0b11000000,0b01000000,0b01100000,0b00100000,0b00110000,0b00010000,0b10010000};
const char DRIVE_PHASES_Y[] = {0b00001000,0b00001100,0b00000100,0b00000110,0b00000010,0b00000011,0b00000001,0b00001001};
const char DRIVE_PHASES_Z[] = {0b10000000,0b11000000,0b01000000,0b01100000,0b00100000,0b00110000,0b00010000,0b10010000};
const char DRIVE_PHASES_E[] = {0b00001001,0b00000001,0b00000011,0b00000010,0b00000110,0b00000100,0b00001100,0b00001000};


/*static struct discret_vector translation_discret = {0,0,0,0};
static long translation_discret_length = 0;
static struct discret_vector progress;
static long counter;
static long kappa;*/

struct discret_vector translation_discret = {0,0,0,0};
long translation_discret_length = 0;
struct discret_vector progress;
long counter;
long kappa;


_Bool smoothPath(long Px, long Py, long Cx, long Cy)
{
    if((Px==0)&&(Cx==0))
    {
        if((Py*Cy)>0)
        {
            return true;
        }else{
            return false;
        }
    }
    if((Py==0)&&(Cy==0))
    {
        if((Px*Cx)>0)
        {
            return true;
        }else{
            return false;
        }
    }
    if (((Px*Cx)>0)&&((Py*Cy)>0))
    {
        return true;
    }else{
        return false;
    }
}


void moveOn(float F){
    /*
        Calculate translation vector
    */

    struct vector translation;

    translation.x = placement.x - location.x;
    translation.y = placement.y - location.y;
    translation.z = placement.z - location.z;
    translation.e = placement.e - location.e;

    translation_discret.x = translation.x*STEPS_PER_X;
    translation_discret.y = translation.y*STEPS_PER_Y;
    translation_discret.z = translation.z*STEPS_PER_Z;
    translation_discret.e = translation.e*STEPS_PER_E;


    /*
        Calcutale length of vectors
    */

    float translation_length = sqrt(
        translation.x*translation.x +
        translation.y*translation.y +
        translation.z*translation.z +
        translation.e*translation.e
    );

    translation_discret_length = (long) sqrt(
        translation_discret.x*translation_discret.x +
        translation_discret.y*translation_discret.y +
        translation_discret.z*translation_discret.z +
        translation_discret.e*translation_discret.e
    );

    if(translation_discret.z == 1) {HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);}
    /*
    Максимально достижимая скорость соответствует kappa = 0.5, следовательно F=6000
    Смысл F - это скорость движения, выраженная в мм/мин
    */
    //if (F>6000){F=6000;}

    /*
        Calculate speed if F changed
    */
    if ((F>0) && (translation_length > 0)){

        /*
            Check for speed limit
        */

        if ((translation.x != 0) && (F*abs(translation.x)/translation_length > MAX_ALLOWED_SPEED_X)){
            F = MAX_ALLOWED_SPEED_X*translation_length/abs(translation.x);
        }
        if ((translation.y != 0) && (F*abs(translation.y)/translation_length > MAX_ALLOWED_SPEED_Y)){
            F = MAX_ALLOWED_SPEED_Y*translation_length/abs(translation.y);
        }
        if ((translation.z != 0) && (F*abs(translation.z)/translation_length > MAX_ALLOWED_SPEED_Z)){
            F = MAX_ALLOWED_SPEED_Z*translation_length/abs(translation.z);
        }
        if ((translation.e != 0) && (F*abs(translation.e)/translation_length > MAX_ALLOWED_SPEED_E)){
            F = MAX_ALLOWED_SPEED_E*translation_length/abs(translation.e);
        }

        kappa = (TIMER1_FREQURENCY*60)/(STEPS_PER_X*((long) F));

        if (translation_discret_length != 0)
        {
            //Fullfill moveBuffer
            if(translationBufferHead == NULL)
            {
                ////Create a new moveNode
                translationBufferHead = malloc(sizeof(moveNode));
                translationBufferHead->previousNode=NULL;
                translationBufferHead->nextNode = NULL;
                //Fill this moveNode
                translationBufferHead->translationX = translation_discret.x;
                translationBufferHead->translationY = translation_discret.y;
                translationBufferHead->translationZ = translation_discret.z;
                translationBufferHead->translationE = translation_discret.e;
                translationBufferHead->translationLength = translation_discret_length;
                translationBufferHead->period = kappa;
                //Incriment the red commands counter
                numberOfCommandsRed+=1;
                //Smooth this
                SmoothThisTranslation();
            }else{
                //Create a new moveNode
                translationBufferHead->nextNode = malloc(sizeof(moveNode));
                translationBufferHead->nextNode->previousNode=translationBufferHead;
                translationBufferHead=translationBufferHead->nextNode;
                translationBufferHead->nextNode = NULL;
                //Fill this moveNode
                translationBufferHead->translationX = translation_discret.x;
                translationBufferHead->translationY = translation_discret.y;
                translationBufferHead->translationZ = translation_discret.z;
                translationBufferHead->translationE = translation_discret.e;
                translationBufferHead->translationLength = translation_discret_length;
                translationBufferHead->period = kappa;
                //Incriment the red commands counter
                numberOfCommandsRed+=1;
                //Smooth this
                SmoothThisTranslation();
            }
        }

        location.x=placement.x;
        location.y=placement.y;
        location.z=placement.z;
        location.e=placement.e;



        /*
            Calculate new kappa
        */
        /*kappa = translation_length*CPU_FREQURENCY*60/(F*TIMER1_DIVIDER*translation_discret_length);

        if (translation_discret_length == 0){
            kappa = (OVERFLOWS_PER_SECOND_TIMER1*60)/(STEPS_PER_X*((long) F));
        }else{
            kappa = (OVERFLOWS_PER_SECOND_TIMER1*60)/(STEPS_PER_X*((long) F));
        }
        */
        //counter = C0;
        //OCR1A = C0;
        //htim5.Init.Period = C0;
        //HAL_TIM_Base_Init(&htim5);

        //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);

        /*if (F==10000) {PORTC ^= (1 << PC3);}*/
        /*if (translation_discret.e==100*STEPS_PER_E) {PORTC ^= (1 << PC3);}*/
    }
    /*
        Prepare variables
    */
   /*
    progress.x = 0;
    progress.y = 0;
    progress.z = 0;
    progress.e = 0;
    if (translation_discret.x != 0){
        //PWM_PORT |= (1<<ENABLE_X);
        //DriverEnableX();
        EnableX();
    }
    if (translation_discret.y != 0){
        //PWM_PORT |= (1<<ENABLE_Y);
        //DriverEnableY();
        EnableY();
    }
    if (translation_discret.z != 0){
        //PWM_PORT |= (1<<ENABLE_Z);
        //DriverEnableZ();
        EnableZ();
    }

    //PWM_PORT |= (1<<ENABLE_E);
    //DriverEnableE();
    EnableE();

    state0 |= NEW_TASK;
    */
}

void doStep(signed char motor){

    static uint8_t phases[] = {0, 0, 0, 0};
    int next_phase = 0;
    if (motor > 0){
        next_phase = phases[motor - 1];
        if (next_phase == PHASE_LENGTH - 1){
            next_phase = 0;
        }else{
            next_phase++;
        }
        phases[motor - 1] = next_phase;
    }else{
        next_phase = phases[-1 - motor];
        if (next_phase == 0){
            next_phase = PHASE_LENGTH - 1;
        }else{
            next_phase--;
        }
        phases[-1 - motor] = next_phase;
    }
    switch(motor){
        case INC_X:
            //PORT_X &= CLEAR_X;
            //PORT_X |= DRIVE_PHASES_X[next_phase];
            DriverPhaseX(DRIVE_PHASES_X[next_phase]);
            break;

        case DEC_X:
            //PORT_X &= CLEAR_X;
            //PORT_X |= DRIVE_PHASES_X[next_phase];
            DriverPhaseX(DRIVE_PHASES_X[next_phase]);
            break;

        case INC_Y:
            //PORT_Y &= CLEAR_Y;
            //PORT_Y |= DRIVE_PHASES_Y[next_phase];
            DriverPhaseY(DRIVE_PHASES_Y[next_phase]);
            break;

        case DEC_Y:
            //PORT_Y &= CLEAR_Y;
            //PORT_Y |= DRIVE_PHASES_Y[next_phase];
            DriverPhaseY(DRIVE_PHASES_Y[next_phase]);
            break;

        case INC_Z:
            //PORT_Z &= CLEAR_Z;
            //PORT_Z |= DRIVE_PHASES_Z[next_phase];
            DriverPhaseZ(DRIVE_PHASES_Z[next_phase]);
            break;

        case DEC_Z:
            //PORT_Z &= CLEAR_Z;
            //PORT_Z |= DRIVE_PHASES_Z[next_phase];
            DriverPhaseZ(DRIVE_PHASES_Z[next_phase]);
            break;

        case INC_E:
            //PORT_E &= CLEAR_E;
            //PORT_E |= DRIVE_PHASES_E[next_phase];
            DriverPhaseE(DRIVE_PHASES_E[next_phase]);
            break;

        case DEC_E:
            //PORT_E &= CLEAR_E;
            //PORT_E |= DRIVE_PHASES_E[next_phase];
            DriverPhaseE(DRIVE_PHASES_E[next_phase]);
            break;
    }

}
