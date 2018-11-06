#include "contrl.h"
#include "distance.h"
#include <MsTimer2.h> 
car_contrl contrl;
int x=0;

void the_timer(){
  contrl.caculate_distance_value();
  Serial3.print("It has gone ");  
  Serial3.print(contrl.get_sum_meter());
  Serial3.print("m and");
  Serial3.print(contrl.get_sum_centimeter());
  Serial3.println("cm");  
  }

void setup() {
Serial.begin(9600);
Serial3.begin(9600);
distance_init();
contrl.ldc1314init();
MsTimer2::set(1000, the_timer); //设置中断，每1000ms进入一次中断服务程序
MsTimer2::start(); //开始计时  
//contrl.go(255);
//contrl.turn_right(128);
}

void loop() {
//contrl.get_ldc_value();
//Serial.print(contrl.get_ch0_value());
Serial.print(contrl.read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH0));
Serial.print("  ");
//Serial.print(contrl.get_ch1_value());
Serial.print(contrl.read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH1));
Serial.print("  ");
Serial.println(contrl.read_ldc1314(slaver_addr,LDC13xx16xx_CMD_CONFIG));
delay(500);
}















