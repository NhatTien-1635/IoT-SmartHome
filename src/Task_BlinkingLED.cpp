#include "Task_BlinkingLED.h"

void TaskBlinkLED(void* parameters){
  pinMode(LED_PIN, OUTPUT);
  bool toggle = false;
  while(1){
    if(toggle){
      digitalWrite(LED_PIN, LOW);
    
    }else{
      digitalWrite(LED_PIN, HIGH);
    }
    toggle = !toggle;
    vTaskDelay(1000);
  }
}