#include "distance.h"
#include <Arduino.h>


     unsigned int meter_left=0;
     unsigned int count_left=0;
     unsigned int meter_right=0;
     unsigned int count_right=0;


void distance_init(){
    attachInterrupt(digitalPinToInterrupt(left_interrupt_pin),step_on_left, RISING);
    attachInterrupt(digitalPinToInterrupt(right_interrupt_pin),step_on_right, RISING);
}

void step_on_left(){
    count_left+=step_;
    if(count_left>10000){
        meter_left++;
        count_left%=10000;
    }
    delay(10);
}

void step_on_right(){
    count_right+=step_;
    if(count_right>10000){
        meter_right++;
        count_right%=10000;
    }
    delay(10);
}
