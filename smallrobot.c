#include <kipr/botball.h>

//MOTORS
const int leftWheel = 1;
const int rightWheel = 0;
const int suckerWheels = 3;
const int magSpin = 2;

//SERVOS
const int claw = 2; // 2047 open ; 500 closed
const int arm = 1; // 315 down; 1280 up

const float TICKS_CONSTSANT = .5;

//infared? sensors
const int leftIR = 0;
const int rightIR = 1;

// digital buttons 
const int leftBump = 1;
const int rightBump = 0;

const int TAPE_THRESHOLD = 3000;
const int GRAY_THRESHOLD = 2700;

const int MOTOR_SPEED = 250;

int main() {
    //enable_servos();
    
    
    getNoodle();
    robotForward(1000);
    getNoodle();
    
    
    
    
    //motor(magSpin, -30);
    //msleep(1000);
    
    disable_servo(arm);
    disable_servo(claw);
    disable_servos();  	    

    ao();
    return 0;
}

void start_everything() {
    set_servo_position(claw, 500);
    set_servo_position(arm, 1280);
    motor(magSpin, -15);
    msleep(100);    
    off(magSpin);
    disable_servo(arm);
    disable_servo(claw);
}

void jiggle() {
    motor(magSpin, -100);
    msleep(200);
    motor(magSpin, 100);
    msleep(300);
    motor(magSpin, 0);
}

void spinServo(int port, int pos) {
    if(get_servo_position(port) > pos) {
    	while(get_servo_position(port) > pos) {
            set_servo_position(port, (get_servo_position(port) - 50));
            msleep(1000);
        }        
    } else {
        while(get_servo_position(port) < pos) {
            set_servo_position(port, (get_servo_position(port) + 5));
            msleep(1000);
        }
    }
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
    motor(leftWheel, 0);
    motor(rightWheel, 0);
}

void forwardTillBump() {
    cmpc(leftWheel);
    cmpc(rightWheel);
    while(digital(leftBump) == 0 || digital(rightBump) == 0) {
        motor(leftWheel, 75);
        if(gmpc(rightWheel) < gmpc(leftWheel)) {
            motor(rightWheel, 100);
        } else {
            motor(rightWheel, 50);
        }
    }    
    motor(leftWheel, 0);
    motor(rightWheel, 0);
}

void forwardTillBumpAgainstWall() {
    while(digital(leftBump) == 0 || digital(rightBump) == 0) {
        motor(leftWheel, 75);
        motor(rightWheel, 72);
    }
    motor(leftWheel, 0);
    motor(rightWheel, 0);
}

void forwardTillTapeAgainstWall() {
    while(analog(rightIR) < GRAY_THRESHOLD) {
        motor(leftWheel, 75);
        motor(rightWheel, 72);
    }
    msleep(200);
    motor(leftWheel, 0);
    motor(rightWheel, 0);
}

void backOffTapeAgainstWall() {
    while(analog(rightIR) > GRAY_THRESHOLD) {
        motor(leftWheel, -10);
        motor(rightWheel, -11);
    }
}

void robotForward2(int left, int right){
    motor(leftWheel, left);
    motor(rightWheel, right);
}

void forwardTillTape() {
    while(analog(leftIR) < TAPE_THRESHOLD || analog(rightIR) < TAPE_THRESHOLD) {
        if(analog(leftIR) < TAPE_THRESHOLD && analog(rightIR) >= TAPE_THRESHOLD ){
            robotForward2(0.05*MOTOR_SPEED, 0);
        }
        else if(analog(leftIR) >= TAPE_THRESHOLD && analog(rightIR) < TAPE_THRESHOLD ) {
            robotForward2(0, 0.05*MOTOR_SPEED);
        }
        else{
            robotForward(50);
        }
    }
}

void backOffTape() {
    while(analog(leftIR) > TAPE_THRESHOLD || analog(rightIR) > TAPE_THRESHOLD) {
        if(analog(leftIR) > TAPE_THRESHOLD && analog(rightIR) <= TAPE_THRESHOLD ){
            robotForward2(-.05*MOTOR_SPEED, 0);
        }
        else if(analog(leftIR) <= TAPE_THRESHOLD && analog(rightIR) > TAPE_THRESHOLD ) {
            robotForward2(0, -0.05*MOTOR_SPEED);
        }
        else{
            robotForward2(-10, -10);
        }
    }
}

void turnRight() {
    robotForward2(100, -100);
}

void turnLeft() {
	robotForward2(-100, 100);
}

void dispenseNoodlesTesting() {    
    motor(suckerWheels, -70);
    msleep(1000);
    motor(suckerWheels, 70);
    msleep(6000);
    motor(suckerWheels, -70);
    motor(magSpin, -100);
    msleep(200);
    motor(magSpin, 100);
    msleep(200);
    motor(magSpin, 0);
    msleep(1500);
}

void getNoodleFromStand(){
	enable_servo(arm);
    enable_servo(claw);
    set_servo_position(arm, 315);
    set_servo_position(claw, 2047);
    msleep(200);   
    forwardTillTape();
    off(leftWheel);
    off(rightWheel);
    msleep(2000);
    backOffTape();
    off(leftWheel);
    off(rightWheel); 
    msleep(1000);
    robotForward(500);
    off(leftWheel);
    off(rightWheel);    
    motor(magSpin, 15);
    msleep(2000);
    off(magSpin);  
    set_servo_position(claw, 600);
    msleep(500);    
    set_servo_position(arm, 1500);
    msleep(3000);
    set_servo_position(claw, 2000);
    msleep(500);
    disable_servo(claw);
    msleep(1000); 
    jiggle();
    motor(suckerWheels, -250);
    msleep(1000);
    motor(suckerWheels, 250);
    msleep(5000);
}

void getNoodle() {
    forwardTillTapeAgainstWall();
    msleep(1000);
    backOffTapeAgainstWall();
    msleep(200);
    motor(leftWheel, 75);
    motor(rightWheel, 72);
    msleep(500);    
    motor(leftWheel, 0);
    motor(rightWheel, 0);
    motor(suckerWheels, -250);
    msleep(3000);
    motor(suckerWheels, 0);    
    motor(magSpin, -60);
    msleep(300);
    motor(suckerWheels, 70);
    msleep(700);    
    motor(magSpin, 0);
    msleep(3000);
    motor(suckerWheels, 0);
    motor(magSpin, 60);
    msleep(1000);
    motor(magSpin, 0);
}