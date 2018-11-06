#ifndef _DISTANCE_H
#define _DISTANCE_H

    #define left_interrupt_pin 18
    #define right_interrupt_pin 19
    #define step_ 108	//10,000进制

    extern unsigned int meter_left;
    extern unsigned int count_left;
    extern unsigned int meter_right;
    extern unsigned int count_right;

void distance_init();
void step_on_left();
void step_on_right();

    #endif 
