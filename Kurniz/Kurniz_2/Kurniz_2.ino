#include <Arduino_FreeRTOS.h>

TaskHandle_t xTask2Handle;

void vApplicationIdleHook()
{
  Serial.write("Hello\n");
}

void vTask1(void *pvParameters)
{
  UBaseType_t uxPriority = uxTaskPriorityGet(NULL);
  
  pinMode(2, OUTPUT);

  while(1)
  {
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);

    vTaskPrioritySet(xTask2Handle, uxPriority + 1);
  }

  vTaskDelete(NULL);
}

void vTask2(void *pvParameters)
{
  UBaseType_t uxPriority = uxTaskPriorityGet(NULL);

  pinMode(6, OUTPUT);

  while(1)
  {
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    
    vTaskPrioritySet(NULL, uxPriority - 2);
  }

  vTaskDelete(NULL);
}

void setup() 
{
  Serial.begin(9600);
  
  xTaskCreate(vTask1,
              "vTask1",
              configMINIMAL_STACK_SIZE,
              NULL,
              2,
              NULL);
              
  xTaskCreate(vTask2,
              "vTask2",
              configMINIMAL_STACK_SIZE,
              NULL,
              1,
              &xTask2Handle);
  
  vTaskStartScheduler();
}

void loop() {}
