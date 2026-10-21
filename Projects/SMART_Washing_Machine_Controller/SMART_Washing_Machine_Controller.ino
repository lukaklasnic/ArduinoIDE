#include <WiFi.h>
#include "wm.h"

const char* ssid = "ESP32S3_Server";
const char* password = "12345678";

WiFiServer wifiServer( 3333 );

typedef struct {

} data_message_t;

QueueHandle_t xDataQueue = NULL;

void xWashingTask( void *pvParameters ) 
{
    data_message_t received_msg;
    Motor motor;
    for( ; ; ) 
    {
        if ( xQueueReceive( xDataQueue, &received_msg, portMAX_DELAY ) == pdPASS ) 
        {
          received_msg.payload[ received_msg.length ] = '\0';
            if( strcmp( received_msg.payload, "Cotton" ) == 0 )
          
            }
            else if( strcmp( received_msg.payload, "ecoCotton" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Synthetics" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Wool" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "handWash" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "quckWashing" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Outdoor" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Sanitize" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Dark" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Duvets" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Prewash" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Rinse" ) == 0 )
            {

            }
            else if( strcmp( received_msg.payload, "Steam" ) == 0 )
            {
            
            }
            else if( strcmp( received_msg.payload, "drumClean" ) == 0 )
            {

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
                    int bytesRead = client.read( ( uint8_t* )buffer, sizeof( buffer ) - 1 );
                    
                    if (bytesRead > 0) 
                    {
                        data_message_t msg;
                        memset( &msg, 0, sizeof( msg ) );
                        int copy_len = ( bytesRead < sizeof( msg.payload ) - 1 ) ? bytesRead : ( sizeof( msg.payload ) - 1 );
                        memcpy( msg.payload, buffer, copy_len );
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

    xTaskCreatePinnedToCore( xWashingTask, "WashingTask", 2048, NULL, 1, NULL, 1 ); 
    xTaskCreatePinnedToCore( xWiFiServerTask, "WiFiServerTask", 4096, NULL, 1, NULL, 1 );
}

void loop() 
{
    vTaskDelete( NULL ); 
}