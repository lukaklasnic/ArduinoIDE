#include <Arduino.h>
#include <WiFi.h>

const int PIN_DOOR_SENSOR = 14;  
const int PIN_WATER_LEVEL = 34;  
const int PIN_MOTOR_PWM   = 25;  

TaskHandle_t SafetyTaskHandle = NULL;
TaskHandle_t MotorTaskHandle = NULL;
TaskHandle_t SensorTaskHandle = NULL;
TaskHandle_t DisplayTaskHandle = NULL;
TaskHandle_t WifiTaskHandle = NULL;

void vSafetyTask(void *pvParameters);
void vMotorTask(void *pvParameters);
void vSensorTask(void *pvParameters);
void vDisplayTask(void *pvParameters);
void vWifiTask(void *pvParameters);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n[System] Starting the washing machine programmer...");

  pinMode(PIN_DOOR_SENSOR, INPUT_PULLUP);
  pinMode(PIN_MOTOR_PWM, OUTPUT);

  
  xTaskCreatePinnedToCore(
    vSafetyTask, "SafetyTask", 2048, NULL, 4, &SafetyTaskHandle, 1
  ); 

  xTaskCreatePinnedToCore(
    vMotorTask, "MotorTask", 2048, NULL, 3, &MotorTaskHandle, 1
  );

  xTaskCreatePinnedToCore(
    vSensorTask, "SensorTask", 2048, NULL, 2, &SensorTaskHandle, 0
  );

  xTaskCreatePinnedToCore(
    vDisplayTask, "DisplayTask", 2048, NULL, 1, &DisplayTaskHandle, 0
  ); 

  xTaskCreatePinnedToCore(
    vWifiTask, "WifiTask", 4096, NULL, 1, &WifiTaskHandle, 0
  ); 
}

void loop() {

  vTaskDelete(NULL);
}

void vSafetyTask(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_Ticks(50); 
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    bool doorOpen = digitalRead(PIN_DOOR_SENSOR) == HIGH;
    int waterLevel = analogRead(PIN_WATER_LEVEL);

    if (doorOpen && waterLevel > 500) {
      Serial.println("[URGENT] The door is open and there is water! Urgent gassing of the engine!");
      digitalWrite(PIN_MOTOR_PWM, LOW);
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void vMotorTask(void *pvParameters) {
  for (;;) {
    Serial.println("[Motor] Drum rotation to the right...");
    analogWrite(PIN_MOTOR_PWM, 128);
    vTaskDelay(pdMS_TO_Ticks(3000));

    Serial.println("[Motor] Pause...");
    analogWrite(PIN_MOTOR_PWM, 0);
    vTaskDelay(pdMS_TO_Ticks(1000)); 

    Serial.println("[Motor] Drum rotation to the left...");
    analogWrite(PIN_MOTOR_PWM, 128);
    vTaskDelay(pdMS_TO_Ticks(3000));

    analogWrite(PIN_MOTOR_PWM, 0);
    vTaskDelay(pdMS_TO_Ticks(2000));
  }
}

void vSensorTask(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_Ticks(200);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    int water = analogRead(PIN_WATER_LEVEL);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void vDisplayTask(void *pvParameters) {
  for (;;) {
    Serial.println("[Display] Display update: Program 1 - Washing in progress (45 min to end)");
    
    vTaskDelay(pdMS_TO_Ticks(1000));
  }
}

void vWifiTask(void *pvParameters) {

  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("[WiFi] Status: Connected. Sending telemetry...");
    } else {

    }

    vTaskDelay(pdMS_TO_Ticks(10000));
  }
}