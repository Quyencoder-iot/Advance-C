#ifndef __MOTOR_H
#define __MOTOR_H

typedef struct {
	 void (*start)(int gpio);
   void (*stop)(int gpio);
   void (*changeSpeed)(int gpio, int speed);
} MotorController;

typedef int PIN;

static void startMotor(PIN pin); 
static void stopMotor(PIN pin);
void changeSpeedMotor(PIN pin, int speed);

/// khi khai báo toàn cục static void như này thì các hàm startMotr, stopMotor chỉ sử dụng được trong file motor.h, và motor.c này
// các file như main.c cũng không thể gọi ra hoặc khai báo 1 hàm trùng tên "" startMotr, stopMotor" này được

	 
void init_motor(MotorController *motorName); 


#endif
