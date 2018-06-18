#include <Arduino_FreeRTOS.h>
#include "semphr.h"

SemaphoreHandle_t binary_semaphore;
QueueHandle_t counting_semaphore;

void pin_ISR()
{
  Serial.write("PUSH\n");

  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(counting_semaphore, &xHigherPriorityTaskWoken);
  
  if(xHigherPriorityTaskWoken == pdTRUE)
  {
    taskYIELD();
  }
}

void vTask(void *pvParameters)
{
  Serial.write("Start task\n");

  while(1)
  {
    xSemaphoreTake(counting_semaphore, portMAX_DELAY);
    
    Serial.write("POP\n");
  }
}

void setup() 
{
  Serial.begin(9600);
  Serial.write("Start\n");

  vSemaphoreCreateBinary(binary_semaphore);
  counting_semaphore = xQueueCreateCountingSemaphore(5, 0);

  attachInterrupt(0, pin_ISR, CHANGE);

  xTaskCreate(vTask, "", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {}
