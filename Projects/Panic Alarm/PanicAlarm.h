#ifndef PANIC_ALARM_H
#define PANIC_ALARM_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define PANIC_ALARM_SERIAL_INIT_DELAY   3000
#define PANIC_ALARM_SMS_NUM_SET_DELAY   1000
#define PANIC_ALARM_SMS_MESSAGE_DELAY   500
#define PANIC_ALARM_SERIAL_BOUDRATE     9600
#define PANIC_ALARM_SEQUENCE_DELAY      1000
#define PANIC_ALARM_SMS_SENT_DELAY      10000
#define PANIC_ALARM_CALL_DURATION       20000
#define PANIC_ALARM_EOF_SIGNAL          26

typedef struct
{
    byte buttonPin;
    byte simRxPin;
    byte simTxPin;
    const char* messageNumber;
    const char* callNumber;
} panicAlarm;

class PanicAlarm
{
public:
    PanicAlarm( panicAlarm alarm );

    void begin();
    void sleep();
    void executePanicSequence();

private:
    byte _buttonPin;
    const char* _messageNumber;
    const char* _callNumber;
    SoftwareSerial _sim800;
};

#endif