#include "contrl.h"
#include "ldc1314.h"
#include "distance.h"



void car_move::update_speed(){
	analogWrite(Left_moto_pwm,left_value);
	analogWrite(Right_moto_pwm,right_value);
}

void car_move::go(uchar x){
	set_left_value(x);
	set_right_value(x);
	this->update_speed();
	Right_moto_go;
	Left_moto_go;
}

void car_move::turn_left(uchar x){
	set_left_value(0);
	set_right_value(x);
	this->update_speed();
	Right_moto_go;
	Left_moto_go;
}

void car_move::turn_right(uchar x){
	set_left_value(x);
	set_right_value(0);
	this->update_speed();
	Right_moto_go;
	Left_moto_go;	
}

void car_move::stop_(){
     Left_moto_Stop;   
	 Right_moto_Stop; 	
}

void car_move::go_back(uchar x){
	set_left_value(x);
	set_right_value(x);
	this->update_speed();
	Left_moto_back;
	Right_moto_back;
}

car_move::car_move(){
	pinMode(Left_moto_pwm,OUTPUT);
	pinMode(Right_moto_pwm,OUTPUT);
	pinMode(contrl_pin1,OUTPUT);
	pinMode(contrl_pin2,OUTPUT);
	pinMode(contrl_pin3,OUTPUT);
	pinMode(contrl_pin4,OUTPUT);
}


car_contrl::car_contrl()
{
}

void car_contrl::auto_go() {
    get_ldc_value();
    if(ldc_value[0]>max_value||ldc_value[1]>max_value)
    {
        digitalWrite(bee_pin,0); 
        go(speed);
        delay(50);
    }
    else{
        digitalWrite(bee_pin,1);        
        if(ldc_value[0]-ldc_value[1]>D_value){
            turn_left(speed);
            delay(50);
        }else if(ldc_value[1]-ldc_value[0]>D_value){
            turn_right(speed);
            delay(50);
        }else {
            go(speed);
            delay(50);
        }
    }
}

void distance::caculate_distance_value(){
  sum_meter=(meter_left+meter_right)/2;
  sum_centimeter=(count_left+count_right)/2;
  }
