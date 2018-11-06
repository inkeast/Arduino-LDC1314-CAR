#ifndef _MOVE_H_
#define _MOVE_H_

#define  uchar unsigned char
#include <Arduino.h>
#include "ldc1314.h"
#include "distance.h"

#define Left_moto_pwm	  2	 
#define Right_moto_pwm	  3	 

#define contrl_pin1 4
#define contrl_pin2 5
#define contrl_pin3 6
#define contrl_pin4 7


#define Left_moto_go      {digitalWrite(contrl_pin2,1),digitalWrite(contrl_pin1,0);}//{P20=1,P21=0;}  
#define Left_moto_back    {digitalWrite(contrl_pin2,0),digitalWrite(contrl_pin1,1);}//{P20=0,P21=1;} 	
#define Left_moto_Stop    {digitalWrite(contrl_pin2,0),digitalWrite(contrl_pin1,0);}//{P24=0;}
#define Right_moto_go     {digitalWrite(contrl_pin3,1),digitalWrite(contrl_pin4,0);}//{P22=1,P23=0;}
#define Right_moto_back   {digitalWrite(contrl_pin3,0),digitalWrite(contrl_pin4,1);}//{P22=0,P23=1;}
#define Right_moto_Stop   {digitalWrite(contrl_pin3,0),digitalWrite(contrl_pin4,0);}//{P25=0;}

#define max_value 65536
#define D_value 100

#define speed 255

#define bee_pin 22


class car_move{
	protected:
	uchar left_value;
	uchar right_value;
	public:
	car_move();
	void go(uchar x);
	void turn_left(uchar x);
	void turn_right(uchar x);
	void stop_();
	void go_back(uchar x);
	void update_speed();
	void set_left_value(uchar x){
		left_value=x;
	}
	void set_right_value(uchar x){
		right_value=x;
	}
	uchar get_left_value(){
		return left_value;
	}
	uchar get_right_value(){
		return right_value;
	}
};
class distance{
  protected :
  unsigned int sum_meter;
  unsigned int sum_centimeter;
  public:
  unsigned int get_sum_meter(){return sum_meter;}
  unsigned int get_sum_centimeter(){return sum_centimeter%100;}
  void caculate_distance_value();
};


class car_contrl:public car_move,public LDC1314,public distance{
public:
	car_contrl();
	void auto_go();
};
#endif


