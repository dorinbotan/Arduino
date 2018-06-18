#include <Arduino_FreeRTOS.h>
#include "semphr.h"

SemaphoreHandle_t mutex;

volatile unsigned long myValue = 100;

void vTask1(void *pvParameters)
{
  while(1)
  {
//    taskENTER_CRITICAL();
//    vTaskSuspendAll();

    xSemaphoreTake(mutex, portMAX_DELAY);
    
    myValue += 100;
    myValue += 100;
    myValue -= 100;
    myValue -= 100;

    xSemaphoreGive(mutex);
    
//    taskEXIT_CRITICAL();
//    xTaskResumeAll();
  }
}

void vTask2(void *pvParameters)
{
  while(1)
  {
    xSemaphoreTake(mutex, portMAX_DELAY);
    
    if(myValue != 100)
    {
      Serial.write("------\n");
    }
    
    xSemaphoreGive(mutex);

    vTaskDelay(10);
  }
}

void setup() 
{
  Serial.begin(9600);
  
  mutex = xSemaphoreCreateMutex();

  xTaskCreate(vTask1, "", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(vTask2, "", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}

void loop() {}
