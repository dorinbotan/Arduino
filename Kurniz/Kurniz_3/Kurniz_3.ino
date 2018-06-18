#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define xTaskCreate(A, B, C) xTaskCreate(A, NULL, configMINIMAL_STACK_SIZE, B, C, NULL);

typedef struct{
  int meaning;
  int value;
} Packet;

QueueHandle_t queue;

void vPop(void *pvParameters)
{
  Serial.write("vPop started\n");  

  Packet msg;

  while(1)
  {
    xQueueReceive(queue, &msg, portMAX_DELAY);

    if(msg.meaning == 9)
    {
      digitalWrite(6, msg.value);
    }
    else
    {
      Serial.write("Pop  ");
      Serial.print(msg.meaning);
      Serial.write(" ");
      Serial.print(msg.value);
      Serial.write('\n');
    }
  }
}

void vPush(void *pvParameters)
{
  Serial.write("vPush started\n");

  Packet msg;
  
  while(1)
  {
    randomSeed(analogRead(0));
    msg.meaning = random(2);
    msg.value = random(100);
    
    Serial.write("Push ");
    Serial.print(msg.meaning);
    Serial.write(" ");
    Serial.print(msg.value);
    Serial.write('\n');
    
    if(xQueueSend(queue, &msg, portMAX_DELAY) == NULL)
    {
      Serial.write("Push ERROR\n");
    }
    
    vTaskDelay(100);
  }
}

void checkButton(void *pvParameters)
{
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);

  Packet msg;
  msg.meaning = 9;
  
  while(1)
  {
    msg.value = digitalRead(7);
    
    if(xQueueSend(queue, &msg, 0) == NULL)
    {
      Serial.write("Check ERROR\n");
    }
  }
}

void setup()
{  
  Serial.begin(9600);

  queue = xQueueCreate(5, sizeof(Packet));
  
  if(queue != NULL)
  {  
    xTaskCreate(vPop, NULL, 10);
    xTaskCreate(vPush, NULL, 2);
    xTaskCreate(vPush, NULL, 2);
    xTaskCreate(checkButton, NULL, 1);

    vTaskStartScheduler();
  }
}

void loop() {}
