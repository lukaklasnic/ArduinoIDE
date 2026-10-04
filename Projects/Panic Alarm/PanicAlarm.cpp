#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "PanicAlarm.h"

PanicAlarm::PanicAlarm( panicAlarm alarm ) : _buttonPin( alarm.buttonPin ), _phoneNumber( alarm.phoneNumber ), _callNumber( alarm.callNumber ), _sim800( alarm.simRxPin, alarm.simTxPin )
{

}

void PanicAlarm::begin()
{
    pinMode( _buttonPin, INPUT_PULLUP );

    _sim800.begin( PANIC_ALARM_SERIAL_BOUDRATE );

    delay( PANIC_ALARM_SERIAL_INIT_DELAY );
}

void PanicAlarm::sleep()
{
    set_sleep_mode( SLEEP_MODE_PWR_DOWN );

    sleep_enable();

    GIMSK |= _BV( INT0 );

    MCUCR &= ~ ( _BV( ISC01 ) | _BV( ISC00 ) );

    sei();

    sleep_cpu();

    cli();

    sleep_disable();

    GIMSK &= ~ _BV( INT0 );

    sei();
}

void PanicAlarm::executePanicSequence()
{
    _sim800.println( "AT+CMGF=1" );
    delay( PANIC_ALARM_SMS_NUM_SET_DELAY );

    _sim800.print( "AT+CMGS=\"" );
    _sim800.print( _messageNumber );
    _sim800.println( "\"" );
    delay( PANIC_ALARM_SMS_NUM_SET_DELAY );

    _sim800.print( "ALARM! Panic button pressed!" );
    delay( PANIC_ALARM_SMS_MESSAGE_DELAY );

    _sim800.write( PANIC_ALARM_EOF_SIGNAL );

    delay( PANIC_ALARM_SMS_SENT_DELAY );

    _sim800.print( "ATD" );
    _sim800.print( _callNumber );
    _sim800.println( ";" );

    delay( PANIC_ALARM_CALL_DURATION );

    _sim800.println( "ATH" );

    delay( PANIC_ALARM_SEQUENCE_DELAY );
}

ISR( INT0_vect )
{
}