#include "PanicAlarm.h"
#define RESET_WAIT_DELAY 10
#define INT_WAIT_DELAY 50
#define SIM_RX_PIN 3
#define SIM_TX_PIN 4
#define BUTTON_PIN 2

panicAlarm config = { 
    .buttonPin = BUTTON_PIN,
    .simRxPin = SIM_RX_PIN,
    .simTxPin = SIM_TX_PIN,
    .phoneNumber = " ",     //Configure phone number by yourself
    .callNumber = " "       //Configure phone number by yourself
};

PanicAlarm alarm( config );

void setup()
{
    alarm.begin();
}

void loop()
{
    alarm.sleep();

    delay( INT_WAIT_DELAY );

    if (digitalRead( BUTTON_PIN ) == LOW)
    {
        alarm.executePanicSequence();

        while ( digitalRead( BUTTON_PIN ) == LOW )
        {
            delay( RESET_WAIT_DELAY );
        }
    }
}