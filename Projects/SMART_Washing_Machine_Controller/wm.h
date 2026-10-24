#ifndef SMART_WASHING_MACHINE
#define SMART_WASHING_MACHINE
#include <Arduino.h>

#define HEAT_PIN                    13
#define PUMP_PIN                    14
#define VALVE_WATER_PIN             15
#define VALVE_SOAP_PIN              16
#define DOOR_LOCK_PIN               17
#define MOTOR_PHASE_PIN             18
#define MOTOR_SPEED_PIN_1           19
#define MOTOR_SPEED_PIN_2           20
#define MOTOR_DIR_PIN               21
#define TEMP_SENSOR_45_PIN          5
#define TEMP_SENSOR_60_PIN          6
#define TEMP_SENSOR_90_PIN          7
#define WATER_LEVEL_HALF_SENSOR_PIN 3
#define WATER_LEVEL_FULL_SENSOR_PIN 11
#define DOOR_LOCK_SENSOR_PIN        12

typedef enum
{
    COTTON,
    ECO_COTTON,
    SYNTHETICS,
    WOOL,
    HAND_WASH,
    QUICK_WASHING,
    OUTDOOR,
    SANITIZE,
    DARK,
    DUVETS,
    PREWASH,
    RINSE,
    STEAM,
    DRUM_CLEAN,
    UNKNOWN_PROGRAM
} program_t;

typedef enum
{
    MOTOR_ON,
    MOTOR_OFF
} motor_phase_t;

typedef enum
{
    MOTOR_SLOW,
    MOTOR_FAST
} motor_speed_t;

typedef enum
{
    MOTOR_CLOCKWISE,
    MOTOR_CCLOCKWISE
} motor_dir_t;

typedef enum
{
    HEAT_ON,
    HEAT_OFF
} heat_stat_t;

typedef enum
{
    PUMP_ON,
    PUMP_OFF
} pump_stat_t;

typedef enum
{
    VALVE_OPEN,
    VALVE_CLOSED
} valve_stat_t;

typedef enum
{
    VALVE_WATER,
    VALVE_SOAP
} valve_type_t;

typedef enum
{
    DOOR_LOCK_OPEN,
    DOOR_LOCK_CLOSED
} door_lock_stat_t;

typedef struct {
    char payload[64];
    uint8_t length;
} data_message_t;

class Motor 
{
public:
    Motor();
    ~Motor();
    void phaseSet( motor_phase_t phase );
    void speedSet( motor_speed_t speed );
    void dirSet( motor_dir_t dir );
};

class Heat
{
public:
    Heat();
    void heatSet( heat_stat_t stat );
};

class Pump
{
public:
    Pump();
    void pumpSet( pump_stat_t stat );
};

class Valve
{
public:
    Valve();
    void valveSet( valve_type_t type, valve_stat_t stat ); 
};

class doorLock
{
public:
    doorLock();
    void doorLockSet( door_lock_stat_t stat );
};

class Washing
{
public:
    Washing();
    ~Washing();
    program_t programSelect( data_message_t *msg );
    void Cotton();
    void ecoCotton();
    void Synthetics();
    void Wool();
    void handWash();
    void quckWashing( uint8_t dur );
    void Outdoor();
    void Sanitize();
    void Dark();
    void Duvets();
    void Prewash();
    void Rinse();
    void Steam();
    void drumClean();
};

class Sensors 
{
private:
    volatile bool interruptTriggered; 
    uint32_t pressCount;
    uint32_t lastDebounceTime;          
    uint32_t debounceDelay;           
    bool validEvent;
    uint8_t activeTriggeredPin; 

    uint8_t temp_sens_45_pin;
    uint8_t temp_sens_60_pin;
    uint8_t temp_sens_90_pin;
    uint8_t water_level_sens_half_pin;
    uint8_t water_level_sens_full_pin;
    uint8_t door_lock_sens_pin;

    struct InterruptContext 
    {
        Sensors* parent;
        uint8_t pin;
        void ( Sensors::*isrMethod )(); 
    };

    InterruptContext ctx45;
    InterruptContext ctx60;
    InterruptContext ctx90;
    InterruptContext ctxHalf;
    InterruptContext ctxFull;
    InterruptContext ctxDoor;

    static void IRAM_ATTR handleInterrupt(void* arg);

public:
    Sensors();

    void triggerTempSens45ISR();
    void triggerTempSens60ISR();
    void triggerTempSens90ISR();
    void triggerWaterLevelSensHalfISR();
    void triggerWaterLevelSensFullISR();
    void triggerDoorLockISR();

    bool checkEvent();
    uint8_t getActivePin() const;
};

#endif