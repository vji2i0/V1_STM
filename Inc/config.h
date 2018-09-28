#ifndef config
#define config


#include <stdbool.h>

    #define TEMPERATURE_OF_EXTRUDER 220
    #define TEMPERATURE_OF_BED 110
    #define TEMPERATURE_WINDOW 1

    #define HEAT_EXTRUDER_PIN GPIO_PIN_2
    #define HEAT_EXTRUDER_PORT GPIOB
    #define HEAT_BED_PIN GPIO_PIN_5
    #define HEAT_BED_PORT GPIOC

    #define C0 20000
    #define TIMER1_FREQURENCY 1000000

    #define PHASE_LENGTH 8
    #define BUFFER_LENGTH 64
    #define WAS_OVERFOLLOW 0b00000001
    #define WAS_COMMENT 0b00000010
    #define CRC_CHECK_ENABLED 0b00100000


    #define ERROR_BUFFER_OVERFOLLOW "Error: the command buffer full!\n"
    #define WARNING_NOTHING_TO_DO "Warning: nothing to do!\n"
    #define WARNING_UNSUPPORTED_COMMAND "Warning: unsupported command!\n"
    #define ERROR_CHECKSUM_FAILED "rs\n"
    #define SUCCESS_DONE "ok\n"
    #define WARNING_WAITING "_\n"
    #define START_MESSAGE "start\n"




    #define DRIVER_X1_PIN GPIO_PIN_0
    #define DRIVER_X1_PORT GPIOC
    #define DRIVER_X2_PIN GPIO_PIN_1
    #define DRIVER_X2_PORT GPIOC
    #define DRIVER_X3_PIN GPIO_PIN_2
    #define DRIVER_X3_PORT GPIOC
    #define DRIVER_X4_PIN GPIO_PIN_3
    #define DRIVER_X4_PORT GPIOC

    #define DRIVER_Y1_PIN GPIO_PIN_4
    #define DRIVER_Y1_PORT GPIOA
    #define DRIVER_Y2_PIN GPIO_PIN_5
    #define DRIVER_Y2_PORT GPIOA
    #define DRIVER_Y3_PIN GPIO_PIN_6
    #define DRIVER_Y3_PORT GPIOA
    #define DRIVER_Y4_PIN GPIO_PIN_7
    #define DRIVER_Y4_PORT GPIOA

    #define DRIVER_Z1_PIN GPIO_PIN_6
    #define DRIVER_Z1_PORT GPIOC
    #define DRIVER_Z2_PIN GPIO_PIN_7
    #define DRIVER_Z2_PORT GPIOC
    #define DRIVER_Z3_PIN GPIO_PIN_8
    #define DRIVER_Z3_PORT GPIOC
    #define DRIVER_Z4_PIN GPIO_PIN_9
    #define DRIVER_Z4_PORT GPIOC

    #define DRIVER_E1_PIN GPIO_PIN_8
    #define DRIVER_E1_PORT GPIOA
    #define DRIVER_E2_PIN GPIO_PIN_9
    #define DRIVER_E2_PORT GPIOA
    #define DRIVER_E3_PIN GPIO_PIN_10
    #define DRIVER_E3_PORT GPIOA
    #define DRIVER_E4_PIN GPIO_PIN_11
    #define DRIVER_E4_PORT GPIOA

    #define DRIVER_ENABLE_X_PIN GPIO_PIN_6
    #define DRIVER_ENABLE_X_PORT GPIOB
    #define DRIVER_ENABLE_Y_PIN GPIO_PIN_7
    #define DRIVER_ENABLE_Y_PORT GPIOB
    #define DRIVER_ENABLE_Z_PIN GPIO_PIN_8
    #define DRIVER_ENABLE_Z_PORT GPIOB
    #define DRIVER_ENABLE_E_PIN GPIO_PIN_9
    #define DRIVER_ENABLE_E_PORT GPIOB


    #define ABSOLUTE_POSITIONING 0b01000000
    #define NEW_TASK 0b10000000
    #define STEPS_PER_X 10 //5
    #define STEPS_PER_Y 10 //5
    #define STEPS_PER_Z 304
    #define STEPS_PER_E 20 //10
    #define MAX_ALLOWED_SPEED_X 15000
    #define MAX_ALLOWED_SPEED_Y 15000
    #define MAX_ALLOWED_SPEED_Z 3000
    #define MAX_ALLOWED_SPEED_E 5000
    #define INITIAL_F 1000
    #define INC_X  1
    #define DEC_X -1
    #define INC_Y  2
    #define DEC_Y -2
    #define INC_Z  3
    #define DEC_Z -3
    #define INC_E  4
    #define DEC_E -4
    #define IDLE_MOTOR 0

    #define TEXT_LENGTH 100
    #define PERIODS_FOR_SLIDING 50000

    //Buttons
    #define PRESSEDUP 1
    #define PRESSEDDOWN 2
    #define PRESSEDOK 3
    #define PRESSEDBACK 4
    #define IDLE 5

    //List of Menu Nodes types
    #define SIMPLENODETYPE 1
    #define PRINTNODETYPE 2 // Ok -> choose the file
    #define EXTRUDERTEMPERATURENODETYPE 3 // Extruder temperature
    #define BEDTEMPERATURENODETYPE 4 // Bed temperature
    #define ABSPLASTICNODETYPE 5 // ABS plastic in type of plastic
    #define PLAPLASTICNODETYPE 6 // PLA plastic in type of plastic
    #define HELPNODETYPE 7 // PLA plastic in type of plastic
    #define CHANGEFILAMENTNODETYPE 8 // Move E axis to change the filament
    #define ENGLISHNODETYPE 9 // English language
    #define RUSSIANNODETYPE 10 // Russian language

    //List of Menu Nodes modes
    #define OFFMODE 0
    #define ONMODE 1

    //Languages
    #define ENGLISH 1
    #define RUSSIAN 2

    //Types of plastic
    #define ABS 1
    #define PLA 2

    //Limits of temperatures for ABS
    #define ABSLOWEREXTRUDERTEMPERATURE 200
    #define ABSNORMEXTRUDERTEMPERATURE 220
    #define ABSHIGHEREXTRUDERTEMPERATURE 240
    #define ABSLOWERBEDTEMPERATURE 100
    #define ABSNORMBEDTEMPERATURE 110
    #define ABSHIGHERBEDTEMPERATURE 120

    //Limits of temperatures for PLA
    #define PLALOWEREXTRUDERTEMPERATURE 140
    #define PLANORMEXTRUDERTEMPERATURE 150
    #define PLAHIGHEREXTRUDERTEMPERATURE 160
    #define PLALOWERBEDTEMPERATURE 70
    #define PLANORMBEDTEMPERATURE 80
    #define PLAHIGHERBEDTEMPERATURE 90

    //Translation for the filament change
    #define CHANGEFILAMENTTRANSLATION 35
    #define CHANGEFILAMENTSPEED 6500

    /* Base address of the Flash sectors */
    #define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
    #define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
    #define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
    #define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
    #define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
    #define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
    #define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
    #define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
    #define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
    #define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
    #define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
    #define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
    #define VoltageRange_1        ((uint8_t)0x00)  /*!< Device operating range: 1.8V to 2.1V */
    #define VoltageRange_2        ((uint8_t)0x01)  /*!<Device operating range: 2.1V to 2.7V */
    #define VoltageRange_3        ((uint8_t)0x02)  /*!<Device operating range: 2.7V to 3.6V */
    #define VoltageRange_4        ((uint8_t)0x03)  /*!<Device operating range: 2.7V to 3.6V + External Vpp */

    //data pices
    #define DATAPIECES 5
        //0. [int] -- has the flash memory been used?
        //1. [int] -- CurrentLanguage;
        //2. [int] -- extruderTargetTamperature;
        //3. [int] -- bedTargetTamperature;
        //4. [int] -- plasticType

    //The number of the commands in the buffer
    #define BUFFERCAPACITY 10

    struct vector
    {
        float x;
        float y;
        float z;
        float e;
    };

    struct discret_vector
    {
        long x;
        long y;
        long z;
        long e;
    };


    #define DISPLAYLENGTH 17
    //Structure for menu
    typedef struct menuNode_this
    {
        struct menuNode_this * upNode; // pointer to the next node
        struct menuNode_this * downNode; // pointer to the previous node
        struct menuNode_this * leftNode; // pointer to the next node
        struct menuNode_this * rightNode; // pointer to the previous node
        int mode; // Default or active mode? For example, you can change the filament mode
        const int nodeType; // The type of the mode defines the behaviour of the buttons' functions
        const char title[DISPLAYLENGTH]; // the layer of the menu node
        const char name[DISPLAYLENGTH]; // the name
    } menuNode;

    //The buffer for the translations
    typedef struct moveNode_this
    {
        struct moveNode_this * nextNode; // pointer to the next node
        struct moveNode_this * previousNode; // pointer to the previous node
        long translationX;
        long translationY;
        long translationZ;
        long translationE;
        long translationLength;
        long period; //speed
        _Bool smoothNext; // true -- hold the speed, false -- stop
        _Bool smoothPrevious; // true -- hold the speed, false -- stop
    } moveNode;

#endif
