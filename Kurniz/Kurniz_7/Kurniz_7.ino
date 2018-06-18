#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <croutine.h>
#include <queue.h>

QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

void pin0_ISR()
{
  static unsigned long msg = 0;

  crQUEUE_SEND_FROM_ISR(xQueue1,
                        &msg,
                        pdFALSE);
                        
  Serial.write("PUSH 0\n");
}

void vCoRoutine1(CoRoutineHandle_t xHandle, UBaseType_t uxIndex)
{
  static long i;
  BaseType_t result;
  
  crSTART(xHandle);
  
  while(1)
  {    
    crQUEUE_RECEIVE(xHandle,
                    xQueue1,
                    (void *)&i,
                    portMAX_DELAY,
                    &result);
                    
    Serial.write("POP 1\n");
    Serial.write("PUSH 1\n");
    
                   
    crQUEUE_SEND(xHandle,
                 xQueue2,
                 (void *)&i,
                 portMAX_DELAY,
                 &result);
                 
    crDELAY(xHandle, 0);
  }

  crEND();
}

void vCoRoutine2(CoRoutineHandle_t xHandle, UBaseType_t uxIndex)
{
  static long i;
  BaseType_t result;
  
  crSTART(xHandle);
  
  while(1)
  {    
    crQUEUE_RECEIVE(xHandle,
                    xQueue2,
                    (void *)&i,
                    portMAX_DELAY,
                    &result);

    Serial.write("POP 2\n");

    crDELAY(xHandle, 0);
  }

  crEND();
}

void vApplicationIdleHook()
{
  while(1)
  {
    vCoRoutineSchedule();
  }
}

void setup()
{  
  Serial.begin(9600);

  xQueue1 = xQueueCreate(3, sizeof(unsigned long));
  xQueue2 = xQueueCreate(3, sizeof(unsigned long));

  attachInterrupt(0, pin0_ISR, CHANGE);
  
  xCoRoutineCreate(vCoRoutine1, 0, 0);
  xCoRoutineCreate(vCoRoutine2, 0, 0);

  vTaskStartScheduler();
}

void loop() {}

