#include <wm.h>

Motor::Motor() 
{
    Serial.println("Instanciran motor");
    pinMode( MOTOR_PHASE_PIN, OUTPUT );
    pinMode( MOTOR_SPEED_PIN_1, OUTPUT );
    pinMode( MOTOR_SPEED_PIN_2, OUTPUT );
    pinMode( MOTOR_DIR_PIN, OUTPUT );
}

Motor::~Motor() 
{
    
}

void Motor::phaseSet( motor_phase_t phase ) 
{
  if( phase == MOTOR_ON )
  {
    digitalWrite( MOTOR_PHASE_PIN, LOW );
  }
  else if( phase == MOTOR_OFF )
  {
    digitalWrite( MOTOR_PHASE_PIN, HIGH );
  }
}

void Motor::speedSet( motor_speed_t speed ) 
{
    if( speed == MOTOR_SLOW )
    {
      digitalWrite( MOTOR_SPEED_PIN_1, LOW );
      digitalWrite( MOTOR_SPEED_PIN_2, LOW );
    }
    else if( speed == MOTOR_FAST )
    {
      digitalWrite( MOTOR_SPEED_PIN_1, HIGH );
      digitalWrite( MOTOR_SPEED_PIN_2, HIGH );
    }
}

void Motor::dirSet( motor_dir_t dir )
{
  if( dir == MOTOR_CLOCKWISE )
  {
    digitalWrite( MOTOR_DIR_PIN, LOW );
  }
  else if( dir == MOTOR_CCLOCKWISE )
  {
    digitalWrite( MOTOR_DIR_PIN, HIGH );
  }
}

void Washing::Cotton()
{

}
void Washing::ecoCotton()
{
  
}
void Washing::Synthetics()
{
  
}
void Washing::Wool()
{
  
}
void Washing::handWash()
{
  
}
void Washing::quckWashing( uint8_t dur )
{
  
}
void Washing::Outdoor()
{
  
}
void Washing::Sanitize()
{
  
}
void Washing::Dark()
{
  
}
void Washing::Duvets()
{
  
}
void Washing::Prewash()
{
  
}
void Washing::Rinse()
{
  
}
void Washing::Steam()
{
  
}
void Washing::drumClean()
{
  
}

Heat::Heat()
{
  pinMode( HEAT_PIN, OUTPUT );
}

void Heat::heatSet( heat_stat_t stat )
{
  if( stat == HEAT_ON )
  {
    digitalWrite( HEAT_PIN, HIGH );
  }
  else if( stat == HEAT_OFF )
  {
    digitalWrite( HEAT_PIN, LOW );
  }
}

Pump::Pump()
{
  pinMode( PUMP_PIN, OUTPUT );
}

void Pump::pumpSet( pump_stat_t stat )
{
  if( stat == PUMP_ON )
  {
    digitalWrite( PUMP_PIN, HIGH );
  }
  else if( stat == PUMP_OFF )
  {
    digitalWrite( PUMP_PIN, LOW );
  }
}

Valve::Valve()
{
  pinMode( VALVE_WATER_PIN, OUTPUT );
  pinMode( VALVE_SOAP_PIN, OUTPUT );
}

void Valve::valveSet( valve_type_t type, valve_stat_t stat )
{
  if( type == VALVE_WATER )
  {
    if( stat == VALVE_OPEN )
    {
      digitalWrite( VALVE_WATER_PIN, HIGH );
    }
    else if( stat == VALVE_CLOSED )
    {
      digitalWrite( VALVE_WATER_PIN, LOW );
    }
  }

  if( type == VALVE_SOAP )
  {
    if( stat == VALVE_OPEN )
    {
      digitalWrite( VALVE_SOAP_PIN, HIGH );
    }
    else if( stat == VALVE_CLOSED )
    {
      digitalWrite( VALVE_SOAP_PIN, LOW );
    }
  }
}

doorLock::doorLock()
{
  pinMode( DOOR_LOCK_PIN, OUTPUT );
}

void doorLock::doorLockSet( door_lock_stat_t stat )
{
  if( stat == DOOR_LOCK_OPEN )
  {
    digitalWrite( DOOR_LOCK_PIN, HIGH );
  }
  else if( stat == DOOR_LOCK_OPEN )
  {
    digitalWrite( DOOR_LOCK_PIN, LOW );
  }
}

Sensors::Sensors()
{
  pinMode( TEMP_SENSOR_45_PIN, OUTPUT );
  pinMode( TEMP_SENSOR_60_PIN, OUTPUT );
  pinMode( TEMP_SENSOR_90_PIN, OUTPUT );
  pinMode( WATER_LEVEL_HALF_SENSOR_PIN, OUTPUT );
  pinMode( WATER_LEVEL_FULL_SENSOR_PIN, OUTPUT );
  pinMode( DOOR_LOCK_PIN, OUTPUT );
}