# Arduino-LDC1314-CAR
本项目实现了一个使用LDC1314进行电磁循迹的小车 \n
本项目使用了以下硬件：\n
LDC1314 评估板\n
L298N驱动板\n
Arduino mega 2560\n
光栅距离测量模块\n
串口蓝牙模块（如果需要）\n

函数说明：\n
底层函数：（自动调用）\n
void update_speed（）			刷新pwm波的频率\n
void set_left_value（）			更改左轮的pwm频率\n
void set_right_value（）		更改右轮的pwm频率\n
void step_on（）			光电开关给予一次脉冲后刷新距离
void the_timer()			定时器中断函数（用来用蓝牙打印行驶距离）
void step_on_left()			左轮进行一次距离加法
void step_on_right()			右轮进行一次距离加法
void iic_write_one_byte(add,x);		iic：向某地址写一个值（未用）
unsigned char iic_read_one_byte(add);	iic: 从某地址读一个值（未用）
void ldc1314_write(add,regist,data);	向LDC1314写一个两字节的值
unsigned int read_ldc1314(addr,regist);	从LDC1314中读一个两字节的值

					（所有构造函数不再列举）

应用函数：
void go（x）				小车直行函数	x为速度（0-255）
void turn_left（x）			小车左转函数	x为速度（0-255）
void turn_right（x）			小车右转函数	x为速度（0-255）
void stop_（）				小车停车
void go_back（x）			小车倒车	x为速度（0-255）
void caculate_distance_value		计算小车行驶的距离
unsigned int get_sum_meter（）		返回小车行驶的距离（整数米）
unsigned int get_sum_centimeter（）	返回小车行驶的距离（整数米后两位）
void auto_go（）			小车沿铁丝自动行驶，并会在遇到硬币后报警
void distance_init（）			初始化光电开关中断
void get_ldc_value();			从LDC1314中读出值并存到数组中
unsigned int get_ch0_value()		返回LDC1314通道0的值
unsigned int get_ch1_value()		返回LDC1314通道1的值
void ldc1314init()			LDC1314初始化
