//
// Created by yu on 2018/5/14.
//
#include "ldc1314.h"
#include <Arduino.h>

LDC1314::LDC1314(){
    Wire.begin();
}

unsigned char LDC1314::iic_read_one_byte(unsigned char add) {
    unsigned char x;
/*

    x=Wire.read();
    Wire.endTransmission();

*/
    Wire.beginTransmission(slaver_addr);
    Wire.write(add);
    Wire.beginTransmission(slaver_addr+1);
    Wire.requestFrom(slaver_addr+1,1);    // request 6 bytes from slave device #8
    x = Wire.read(); // receive a byte as character
    return x;    
    
}

void LDC1314::iic_write_one_byte(unsigned char add, unsigned char x) {
    Wire.beginTransmission(slaver_addr);
    Wire.write(add);
    Wire.write(x);
    Wire.endTransmission();
}

void LDC1314::ldc1314_write(unsigned char add, unsigned char regist, unsigned int data) {
    unsigned char data_lsb=(unsigned char)(data&0x00ff);//低位
    unsigned char data_msb=(unsigned char)(data>>8);//高位
    Wire.beginTransmission(slaver_addr);
    Wire.write(regist);
    Wire.write(data_msb);
    Wire.write(data_lsb);
    Wire.endTransmission();
}

unsigned int LDC1314::read_ldc1314(unsigned char addr,unsigned char regist) {
    unsigned char data_msb=0;
    unsigned char data_lsb=0;
    unsigned int data=0;
    Wire.beginTransmission(slaver_addr);
    Wire.write(regist);
    Wire.endTransmission();
        
    Wire.requestFrom(slaver_addr, 2);    
    while(Wire.available())
    {
    data_msb=Wire.read();
    data_lsb=Wire.read();
      }

    data|=data_msb;
    data=data<<8;
    data|=data_lsb;
    return data;

    /*
    i2c_start();
    i2c_writebyte((slaver_addr<<1));
    i2c_wait_ack();
    i2c_writebyte(regist);
    i2c_wait_ack();
    i2c_start();
    i2c_writebyte((slaver_addr<<1)+1);
    i2c_wait_ack();
    data_msb=i2c_readbyte();
    sendack();
    data_lsb=i2c_readbyte();
    sendnack();
    i2c_stop();
    data|=data_msb;
    data=data<<8;
    data|=data_lsb;
    return data;
*/
}

void LDC1314::ldc1314init() {
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_RESET_DEVICE,0x8000);  
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH0,0x04d6);//配置的是传感器的转化时间
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH1,0x04d6);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH2,0x04d6);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH3,0x04d6);

    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH0,0x0000);//转化的偏移量
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH1,0x0000);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH2,0x29ff);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH3,0x29ff);

    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH0,0x0400);//利用这个时间让lc稳定在通道数据稳定之前
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH1,0x0400);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH2,0x000A);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH3,0x000A);

    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0,0x0000);
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1,0x0000);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2,0x1005);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3,0x1005);



    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_MUX_CONFIG,0xC20F);


    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH0,0x0000);
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH1,0x0000);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH2,0x7000);
    //ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH3,0x6000);

    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_RESET_DEVICE,0x0600);
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SYSTEM_CLOCK_CONFIG,0x0200);
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_STATUS,0x0001);
    ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CONFIG,0x0000);
}

void LDC1314::get_ldc_value()
{
    ldc_value[0]=read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH0);
    ldc_value[1]=read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH1);
}

