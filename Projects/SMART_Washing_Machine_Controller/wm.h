#ifndef SMART_WASHING_MACHINE
#define SMART_WASHING_MACHINE
#include <Arduino.h>

#define HEAT_PIN                    5
#define PUMP_PIN                    6
#define VALVE_WATER_PIN             7
#define VALVE_SOAP_PIN              8
#define DOOR_LOCK_PIN               9
#define MOTOR_PHASE_PIN             10
#define MOTOR_SPEED_PIN_1           11
#define MOTOR_SPEED_PIN_2           12
#define MOTOR_DIR_PIN               13
#define TEMP_SENSOR_45_PIN          14
#define TEMP_SENSOR_60_PIN          15
#define TEMP_SENSOR_90_PIN          16
#define WATER_LEVEL_HALF_SENSOR_PIN 17
#define WATER_LEVEL_FULL_SENSOR_PIN 18
#define DOOR_LOCK_SENSOR_PIN        19

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

class Motor 
{
private:

public:
    Motor();
    ~Motor();
    
    void phaseSet( motor_phase_t phase );
    void speedSet( motor_speed_t speed );
    void dirSet( motor_dir_t dir );
};

class Heat
{
private:

public:
    Heat();
    void heatSet( heat_stat_t stat );
};

class Pump
{
private:

public:
    Pump();
    void pumpSet( pump_stat_t stat );
};

class Valve
{
private:

public:
    Valve();
    void valveSet( valve_type_t type, valve_stat_t stat ); 
};

class doorLock
{
private:

public:
    doorLock();
    void doorLockSet( door_lock_stat_t stat );
};

class Washing
{
private:

public:
    Washing();
    ~Washing();

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

  public:
    Sensors();
};

#endif