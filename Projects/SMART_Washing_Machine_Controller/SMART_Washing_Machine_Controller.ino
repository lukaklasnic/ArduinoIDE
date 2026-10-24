#include <WiFi.h>
#include "wm.h"

const char* ssid = "ESP32S3_Server";
const char* password = "12345678";

WiFiServer wifiServer( 3333 );
QueueHandle_t xDataQueue = NULL;

void xWashingTask( void *pvParameters ) 
{
    data_message_t received_msg;
    Motor motor;
    Washing washing;
    program_t program;
    Sensors sensors;
    pinMode(2, OUTPUT);

    for( ; ; ) 
    {
        if ( xQueueReceive( xDataQueue, &received_msg, portMAX_DELAY ) == pdPASS ) 
        {
            
            program = washing.programSelect( &received_msg );
            switch( program )
            {
                case COTTON:
                {   
                    Serial.println("Izabran program: COTTON. Pocetak ciklusa pranja...");
                    
                    bool cottonCycleActive = true;
                    
                    while ( cottonCycleActive ) 
                    {
                        if ( sensors.checkEvent() ) 
                        {
                            uint8_t activePin = sensors.getActivePin();
                            
                            Serial.print("Detektovan prekid na pin-u: ");
                            Serial.println(activePin);
                            
                            if ( activePin == TEMP_SENSOR_45_PIN ) 
                            {
                                Serial.println("-> Temperatura 45°C dostignuta! Možemo isključiti grejač.");
                                tone(2, 2000, 500);
                                vTaskDelay( pdMS_TO_TICKS( 1000 ) );
                                tone(2, 2000, 500);
                                vTaskDelay( pdMS_TO_TICKS( 1000 ) );
                                tone(2, 2000, 500);
                            }
                            else if ( activePin == WATER_LEVEL_FULL_SENSOR_PIN ) 
                            {
                                Serial.println("-> Nivo vode je PUN! Krećemo sa okretanjem bubnja.");
                            }
                            else if ( activePin == DOOR_LOCK_SENSOR_PIN ) 
                            {
                                Serial.println("-> Detektovana promena na bravi vrata!");
                            }
                        }   
                        
                        vTaskDelay( pdMS_TO_TICKS( 50 ) );
                    }
                    break;
                }  
                case ECO_COTTON:
                    Serial.println("Izabran program: ECO_COTTON");
                    break;
                case SYNTHETICS:
                    Serial.println("Izabran program: SYNTHETICS");
                    break;
                case WOOL:
                    Serial.println("Izabran program: WOOL");
                    break;
                case HAND_WASH:
                    Serial.println("Izabran program: HAND_WASH");
                    break;
                case QUICK_WASHING:
                    Serial.println("Izabran program: QUICK_WASHING");
                    break;
                case OUTDOOR:
                    Serial.println("Izabran program: OUTDOOR");
                    break;
                case SANITIZE:
                    Serial.println("Izabran program: SANITIZE");
                    break;
                case DARK:
                    Serial.println("Izabran program: DARK");
                    break;
                case DUVETS:
                    Serial.println("Izabran program: DUVETS");
                    break;
                case PREWASH:
                    Serial.println("Izabran program: PREWASH");
                    break;
                case RINSE:
                    Serial.println("Izabran program: RINSE");
                    break;
                case STEAM:
                    Serial.println("Izabran program: STEAM");
                    break;
                case DRUM_CLEAN:
                    Serial.println("Izabran program: DRUM_CLEAN");
                    break;
                default:
                    Serial.println("Nepoznat program!");
                    break;
            }
        }
    }
}

void xWiFiServerTask( void *pvParameters ) 
{
    wifiServer.begin();
    Serial.println( "WiFi TCP Server pokrenut!" );

    for( ; ; )  
    {
        WiFiClient client = wifiServer.available();

        if ( client ) 
        {
            Serial.println( "Klijent povezan!" );
            
            while ( client.connected() ) 
            {
                if ( client.available() ) 
                {
                    char buffer[ 128 ];
                    int bytesRead = client.read( (uint8_t*)buffer, sizeof( buffer ) - 1 );
                    
                    if ( bytesRead > 0 ) 
                    {
                        data_message_t msg;
                        memset( &msg, 0, sizeof( msg ) );
                        int copy_len = ( bytesRead < sizeof( msg.payload ) - 1 ) ? bytesRead : ( sizeof( msg.payload ) - 1 );
                        memcpy( msg.payload, buffer, copy_len );
                        msg.payload[copy_len] = '\0';
                        msg.length = copy_len;

                        xQueueSend( xDataQueue, &msg, 0 );
                    }
                }
                vTaskDelay( pdMS_TO_TICKS( 10 ) );
            }
            client.stop();
            Serial.println( "Klijent diskonektovan." );
        }
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
    }
}

void setup() 
{
    Serial.begin( 115200 );
    delay( 1000 );

    WiFi.softAP( ssid, password );
    Serial.print( "AP IP adresa: " );
    Serial.println( WiFi.softAPIP() );

    xDataQueue = xQueueCreate( 10, sizeof( data_message_t ) );

    xTaskCreatePinnedToCore( xWashingTask, "WashingTask", 4096, NULL, 1, NULL, 1 ); 
    xTaskCreatePinnedToCore( xWiFiServerTask, "WiFiServerTask", 4096, NULL, 1, NULL, 1 );
}

void loop() 
{
    vTaskDelete( NULL );
}