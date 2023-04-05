#include <kipr/botball.h>

//MOTORS
const int leftWheel = 0;
const int rightWheel = 1;
const int suckerWheels = 2;
const int magSpin = 3;

//SERVOS
const int claw = 0;
const int arm = 1;

const float TICKS_CONSTSANT = .5;

//infared? sensors
const int LEFT_SENSOR = 0;
const int RIGHT_SENSOR = 1;

const int TAPE_THRESHOLD = 100;
const int GRAY_THRESHOLD = 60;

const int MOTOR_SPEED = 250;

int main() {
    enable_servos();

    set_servo_position(arm, 350);
    set_servo_position(claw, 320);
    forwardTillBump();
    set_servo_position(claw, 1200);
    msleep(1000);
    set_servo_position(arm, 1350);
    msleep(1000);
    set_servo_position(arm, 350);
    msleep(1000);

    disable_servos();
    ao();
    return 0;
}

void robotForward(int inches){
    cmpc(leftWheel);
    cmpc(rightWheel);
    while(gmpc(leftWheel) < (inches * TICKS_CONSTSANT)) {
        motor(leftWheel, 75);
        if(gmpc(rightWheel) < gmpc(leftWheel)) {
            motor(rightWheel, 100);
        } else {
            motor(rightWheel, 50);
        }
    }
}

void forwardTillBump() {
    cmpc(leftWheel);
    cmpc(rightWheel);
    while(digital(0) == 0) {
        motor(leftWheel, 75);
        if(gmpc(rightWheel) < gmpc(leftWheel)) {
            motor(rightWheel, 100);
        } else {
            motor(rightWheel, 50);
        }
    }
}

void robotForward2(int left, int right){
    cmpc(leftWheel);
    cmpc(rightWheel);
    if(left >= 0){
        while(gmpc(leftWheel) < (left * TICKS_CONSTSANT)) {
            motor(leftWheel, 75);
        }
    }
    else if(right >= 0) {
        while(gmpc(rightWheel) < (right * TICKS_CONSTSANT)){
            motor(rightWheel, 75);
        }
    }
}

void forwardTillTape() {
    while(analog(LEFT_SENSOR) < TAPE_THRESHOLD || analog(RIGHT_SENSOR) < TAPE_THRESHOLD) {
        if(analog(LEFT_SENSOR) < TAPE_THRESHOLD && analog(RIGHT_SENSOR) >= TAPE_THRESHOLD ){
            robotForward2(.75*MOTOR_SPEED, -0.1*MOTOR_SPEED);
        }
        else if( analog(LEFT_SENSOR) >= TAPE_THRESHOLD && analog(RIGHT_SENSOR) < TAPE_THRESHOLD ) {
            robotForward2(-0.1*MOTOR_SPEED, 0.75*MOTOR_SPEED);
        }
        else{
            robotForward(0.1);
        }
    }
    create_stop();
}

void forwardTilGrayTape() {
    while(analog(LEFT_SENSOR) < GRAY_THRESHOLD || analog(RIGHT_SENSOR) < GRAY_THRESHOLD) {
        if(analog(LEFT_SENSOR) < GRAY_THRESHOLD && analog(RIGHT_SENSOR) >= GRAY_THRESHOLD ){
            create_drive_direct(0.75*MOTOR_SPEED, -0.1*MOTOR_SPEED);
        }
        else if( analog(LEFT_SENSOR) >= GRAY_THRESHOLD && analog(RIGHT_SENSOR) < GRAY_THRESHOLD ) {
            create_drive_direct(-0.1*MOTOR_SPEED, 0.75*MOTOR_SPEED);
        }
        else{
            create_drive_direct(MOTOR_SPEED,MOTOR_SPEED);
        }
    }
    create_stop();
}

void releaseNoodle(){

}