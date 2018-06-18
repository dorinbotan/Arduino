#include <Arduino_FreeRTOS.h>
#include "semphr.h"

SemaphoreHandle_t mutex;

void vTask1(void *pvParameters)
{
  BaseType_t uxIsPriorityInherited = pdFALSE;
  
  while(1)
  {
    xSemaphoreTake(mutex, portMAX_DELAY);

    for(unsigned long i = 0; i < 1000000L; i++)
    {
      __asm__("NOP");
    }

    if(uxTaskPriorityGet(NULL) != 1)
    {
      uxIsPriorityInherited = pdTRUE;
    }

    xSemaphoreGive(mutex);

    if(uxIsPriorityInherited == pdTRUE)
    {
      Serial.print(uxTaskPriorityGet(NULL));
    }

    vTaskDelay(10);
  }
}
 
void vTask2(void *pvParameters)
{
  while(1)
  {
    xSemaphoreTake(mutex, portMAX_DELAY);    
    xSemaphoreGive(mutex);
  }
}

void setup() 
{
  Serial.begin(9600);
  
  mutex = xSemaphoreCreateMutex();

  xTaskCreate(vTask1, "", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(vTask2, "", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  vTaskStartScheduler();
}

void loop() {}
