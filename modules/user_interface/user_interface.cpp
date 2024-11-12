//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"



#include "smart_home_system.h"
#include "display.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

#define DISPLAY_CONNECTION_MODE_0 (0)   //DISPLAY_CONNECTION_GPIO_4BITS
#define DISPLAY_CONNECTION_MODE_1 (1)   //DISPLAY_CONNECTION_GPIO_8BITS
#define DISPLAY_CONNECTION_MODE_2 (2)   //DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER

#define DISPLAY_CONNECTION_MODE (DISPLAY_CONNECTION_MODE_2)

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================

static void userInterfaceDisplayInit()
{
    if (DISPLAY_CONNECTION_MODE == 0){
        displayInit( DISPLAY_CONNECTION_GPIO_4BITS );
    };
    

    if(DISPLAY_CONNECTION_MODE == 1){
        displayInit( DISPLAY_CONNECTION_GPIO_8BITS );
    };
    

    if(DISPLAY_CONNECTION_MODE == 2){
        displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
    };
        
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Temperature:" );

}

uint32_t contador = 0;

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    char temperatureString[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        sprintf(temperatureString, "%.0d", contador++);
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( temperatureString );
        displayCharPositionWrite ( 14,0 );
        displayStringWrite( "'C" );
    
        
    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

static void incorrectCodeIndicatorUpdate()
{
    incorrectCodeLed = incorrectCodeStateRead();
}

static void systemBlockedIndicatorUpdate()
{
    systemBlockedLed = systemBlockedState;
}