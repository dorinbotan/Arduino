#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include <croutine.h>

TimerHandle_t xAutoReloadTimer;
TimerHandle_t xOneShotTimers[3];

void vAutoReloadTimerFunction(TimerHandle_t xTimer)
{
  Serial.write("-- 1\n");
}

void vOneShotTimerFunction(TimerHandle_t xTimer)
{
  if(xTimer == xOneShotTimers[0])
  {
    Serial.write("One shot timer 1\n");
    
    xTimerStart(xOneShotTimers[1], 0);
  }
  else if(xTimer == xOneShotTimers[1])
  {
    Serial.write("One shot timer 2\n");
    
    xTimerStart(xOneShotTimers[2], 0);
  }
  else if(xTimer == xOneShotTimers[2])
  {
    Serial.write("One shot timer 3\n");

    xTimerDelete(xAutoReloadTimer, 0);
  }
}

void setup() 
{
  Serial.begin(9600);
  Serial.write("Start\n");
  
  xAutoReloadTimer = xTimerCreate("",
                                  500/portTICK_PERIOD_MS,
                                  pdTRUE,
                                  NULL,
                                  vAutoReloadTimerFunction);

  xOneShotTimers[0] = xTimerCreate("",
                                   5000/portTICK_PERIOD_MS,
                                   pdFALSE,
                                   NULL,
                                   vOneShotTimerFunction);

  xOneShotTimers[1] = xTimerCreate("",
                                   5000/portTICK_PERIOD_MS,
                                   pdFALSE,
                                   NULL,
                                   vOneShotTimerFunction);

  xOneShotTimers[2] = xTimerCreate("",
                                   5000/portTICK_PERIOD_MS,
                                   pdFALSE,
                                   NULL,
                                   vOneShotTimerFunction);

  xTimerStart(xAutoReloadTimer, 0);
  xTimerStart(xOneShotTimers[0], 0);
}

void loop() {}
