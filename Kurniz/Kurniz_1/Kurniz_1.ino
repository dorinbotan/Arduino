#include <Arduino_FreeRTOS.h>

typedef struct TaskParam_t {
  unsigned int led;
  long period;
} TaskParam;

TaskParam xTP1, xTP2;

void vApplicationIdleHook()
{
  Serial.write("Idle... \n");
  for(unsigned long i = 0; i < 1000000; i++)
  {
    __asm__("NOP");
  }
}

void vTask(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  TaskParam pxTaskParam = *(TaskParam *)pvParameters;
  int value = 0;

  pinMode(pxTaskParam.led, OUTPUT);

  while(1)
  {
    value = !value;
    digitalWrite(pxTaskParam.led, value);

    char str[100];
    Serial.write("LED: ");
    Serial.write(pxTaskParam.led + '0');
    Serial.write(", ");
    snprintf(str, 100, "%d", xLastWakeTime);
    Serial.write(str);
    Serial.write(", ");
    snprintf(str, 100, "%d", xTaskGetTickCount());
    Serial.write(str);
    Serial.write("\n");

    vTaskDelayUntil(&xLastWakeTime, 
                    pxTaskParam.period / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}

void setup()
{
  Serial.begin(9600);
  
  xTP1.led = 2;
  xTP1.period = 1000;
  
  xTaskCreate(vTask,
              "Task1",
              configMINIMAL_STACK_SIZE,
              &xTP1,
              1,
              NULL);
    
  xTP2.led = 6;
  xTP2.period = 1000;
    
  xTaskCreate(vTask,
              "Task2",
              configMINIMAL_STACK_SIZE,
              &xTP2,
              1,
              NULL);

  vTaskStartScheduler();
}

void loop() {}
