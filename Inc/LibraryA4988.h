#ifndef LibraryA4988
#define LibraryA4988

//A4988
#define STEP_X_PIN GPIO_PIN_0
#define STEP_X_PORT GPIOE
#define DIRECTION_X_PIN GPIO_PIN_2
#define DIRECTION_X_PORT GPIOE
#define ENABLE_X_PIN GPIO_PIN_4
#define ENABLE_X_PORT GPIOE
#define STEP_Y_PIN GPIO_PIN_1
#define STEP_Y_PORT GPIOD
#define DIRECTION_Y_PIN GPIO_PIN_3
#define DIRECTION_Y_PORT GPIOD
#define ENABLE_Y_PIN GPIO_PIN_5
#define ENABLE_Y_PORT GPIOD
#define STEP_Z_PIN GPIO_PIN_7
#define STEP_Z_PORT GPIOE
#define DIRECTION_Z_PIN GPIO_PIN_9
#define DIRECTION_Z_PORT GPIOE
#define ENABLE_Z_PIN GPIO_PIN_11
#define ENABLE_Z_PORT GPIOE
#define STEP_E_PIN GPIO_PIN_14
#define STEP_E_PORT GPIOE
#define DIRECTION_E_PIN GPIO_PIN_12
#define DIRECTION_E_PORT GPIOE
#define ENABLE_E_PIN GPIO_PIN_10
#define ENABLE_E_PORT GPIOE

//X
void EnableX(void);
void DisableX(void);
void ForwardX(void);
void BackwardX(void);
void StepOnX(void);
void StepOffX(void);
//Y
void EnableY(void);
void DisableY(void);
void ForwardY(void);
void BackwardY(void);
void StepOnY(void);
void StepOffY(void);
//Z
void EnableZ(void);
void DisableZ(void);
void ForwardZ(void);
void BackwardZ(void);
void StepOnZ(void);
void StepOffZ(void);
//E
void EnableE(void);
void DisableE(void);
void ForwardE(void);
void BackwardE(void);
void StepOnE(void);
void StepOffE(void);

#endif
