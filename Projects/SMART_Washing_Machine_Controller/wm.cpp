#include "wm.h"

Motor::Motor() 
{
    Serial.println( "Instanciran motor" );
    pinMode( MOTOR_PHASE_PIN, OUTPUT );
    pinMode( MOTOR_SPEED_PIN_1, OUTPUT );
    pinMode( MOTOR_SPEED_PIN_2, OUTPUT );
    pinMode( MOTOR_DIR_PIN, OUTPUT );
}

Motor::~Motor() {}

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

Washing::Washing() {}
Washing::~Washing() {}

program_t Washing::programSelect( data_message_t *msg )
{
  if( strcmp( msg->payload, "COTTON" ) == 0 )
  {
    return COTTON;
  } 
  else if( strcmp( msg->payload, "ECO_COTTON" ) == 0 )
  {
    return ECO_COTTON;
  } 
  else if( strcmp( msg->payload, "SYNTHETICS" ) == 0 ) 
  {
    return SYNTHETICS;
  }
  else if( strcmp( msg->payload, "WOOL" ) == 0 ) 
  {
    return WOOL;
  }
  else if( strcmp( msg->payload, "HAND_WASH" ) == 0 ) 
  {
    return HAND_WASH;
  }
  else if( strcmp( msg->payload, "QUICK_WASHING" ) == 0 ) 
  {
    return QUICK_WASHING;
  }
  else if( strcmp( msg->payload, "OUTDOOR" ) == 0 ) 
  {
    return OUTDOOR;
  }
  else if( strcmp( msg->payload, "SANITIZE" ) == 0 ) 
  {
    return SANITIZE;
  }
  else if( strcmp( msg->payload, "DARK" ) == 0 ) 
  {
    return DARK;
  }
  else if( strcmp( msg->payload, "DUVETS" ) == 0 ) 
  {
    return DUVETS;
  }
  else if( strcmp( msg->payload, "PREWASH" ) == 0 ) 
  {
    return PREWASH;
  }
  else if( strcmp( msg->payload, "RINSE" ) == 0 ) 
  {
    return RINSE;
  }
   
  else if( strcmp( msg->payload, "STEAM" ) == 0 ) 
  {
    return STEAM;
  }
  else if( strcmp( msg->payload, "DRUM_CLEAN" ) == 0 ) 
  {
    return DRUM_CLEAN;
  }

  return UNKNOWN_PROGRAM;
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
  digitalWrite( HEAT_PIN, ( stat == HEAT_ON ) ? HIGH : LOW ); 
}

Pump::Pump() 
{ 
  pinMode( PUMP_PIN, OUTPUT ); 
}
void Pump::pumpSet( pump_stat_t stat ) 
{ 
  digitalWrite( PUMP_PIN, ( stat == PUMP_ON ) ? HIGH : LOW ); 
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
    digitalWrite( VALVE_WATER_PIN, ( stat == VALVE_OPEN ) ? HIGH : LOW );
  } 
  if( type == VALVE_SOAP )
  {
    digitalWrite( VALVE_SOAP_PIN, ( stat == VALVE_OPEN ) ? HIGH : LOW );
  }
    
}

doorLock::doorLock() 
{ 
  pinMode( DOOR_LOCK_PIN, OUTPUT ); 
}

void doorLock::doorLockSet( door_lock_stat_t stat )
{
  digitalWrite( DOOR_LOCK_PIN, ( stat == DOOR_LOCK_OPEN ) ? HIGH : LOW );
}

Sensors::Sensors() 
{
  pinMode( TEMP_SENSOR_45_PIN, INPUT_PULLUP );
  pinMode( TEMP_SENSOR_60_PIN, INPUT_PULLUP );
  pinMode( TEMP_SENSOR_90_PIN, INPUT_PULLUP );
  pinMode( WATER_LEVEL_FULL_SENSOR_PIN, INPUT_PULLUP );
  pinMode( WATER_LEVEL_HALF_SENSOR_PIN, INPUT_PULLUP );
  pinMode( DOOR_LOCK_SENSOR_PIN, INPUT_PULLUP );

  attachInterruptArg( TEMP_SENSOR_45_PIN, handleInterrupt, &ctx45, FALLING );
  attachInterruptArg( TEMP_SENSOR_60_PIN, handleInterrupt, &ctx60, FALLING );
  attachInterruptArg( TEMP_SENSOR_90_PIN, handleInterrupt, &ctx90, FALLING );
  attachInterruptArg( WATER_LEVEL_HALF_SENSOR_PIN, handleInterrupt, &ctxHalf, FALLING );
  attachInterruptArg( WATER_LEVEL_FULL_SENSOR_PIN, handleInterrupt, &ctxFull, FALLING );
  attachInterruptArg( DOOR_LOCK_SENSOR_PIN, handleInterrupt, &ctxDoor, FALLING );

  ctx45 = { this, TEMP_SENSOR_45_PIN, &Sensors::triggerTempSens45ISR };
  ctx60 = { this, TEMP_SENSOR_60_PIN, &Sensors::triggerTempSens60ISR };
  ctx90 = { this, TEMP_SENSOR_90_PIN, &Sensors::triggerTempSens90ISR };
  ctxHalf = { this, WATER_LEVEL_HALF_SENSOR_PIN, &Sensors::triggerWaterLevelSensHalfISR };
  ctxFull = { this, WATER_LEVEL_FULL_SENSOR_PIN, &Sensors::triggerWaterLevelSensFullISR };
  ctxDoor = { this, DOOR_LOCK_SENSOR_PIN, &Sensors::triggerDoorLockISR };

  interruptTriggered = false;
  lastDebounceTime = 0;
  debounceDelay = 200;
  validEvent = false;
  activeTriggeredPin = 0;
}

void Sensors::triggerTempSens45ISR() 
{ 
  interruptTriggered = true; 
}

void Sensors::triggerTempSens60ISR() 
{ 
  interruptTriggered = true; 
}

void Sensors::triggerTempSens90ISR() 
{ 
  interruptTriggered = true; 
}

void Sensors::triggerWaterLevelSensHalfISR() 
{ 
  interruptTriggered = true; 
}

void Sensors::triggerWaterLevelSensFullISR() 
{ 
  interruptTriggered = true; 
}

void Sensors::triggerDoorLockISR() 
{ 
  interruptTriggered = true; 
}

bool Sensors::checkEvent() 
{
  validEvent = false;
  if ( interruptTriggered ) 
  {
    interruptTriggered = false; 
    uint32_t currentTime = millis();
    if ( currentTime - lastDebounceTime > debounceDelay ) 
    {
      if ( digitalRead( activeTriggeredPin ) == LOW ) 
      {
        lastDebounceTime = currentTime;

        validEvent = true; 
      }
    }
  }
  return validEvent;
}

uint8_t Sensors::getActivePin() const 
{ 
  return activeTriggeredPin; 
}

void IRAM_ATTR Sensors::handleInterrupt( void *arg ) 
{
  InterruptContext* ctx = static_cast< InterruptContext*>( arg );
  if ( ctx && ctx -> parent && ctx -> isrMethod ) 
  {
    ctx -> parent -> activeTriggeredPin = ctx -> pin; 
    ( ctx -> parent ->*( ctx -> isrMethod ) )();         
  }
}