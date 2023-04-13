#include <kipr/botball.h>
//2.75" from top edge of first tape
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
const int noodleBump = 2;
const int leftBump = 1;
const int rightBump = 0;

const int TAPE_THRESHOLD = 3000;
const int GRAY_THRESHOLD = 2700;

const int MOTOR_SPEED = 250;

int main() {
    //accepted argument 2550
    //turnLeft(90);
    //turnRight(90);
    //getNoodle();
    //forwardTillTape();
    enable_servos();
    //start_everything();
    //turnRight(1);
    startMoving();
    //forwardTillBump();
    disable_servos();
    return 0;
    ao();
    
}

void start_everything() {
    set_servo_position(claw, 500);
    set_servo_position(arm, 1280);
    motor(magSpin, 60);
    msleep(200);    
    off(magSpin);
    disable_servo(arm);
    disable_servo(claw);
}

void jiggle() {
    motor(magSpin, -100);
    msleep(200);
    motor(magSpin, 100);
    msleep(200);
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
            motor(rightWheel, 90);
        } else {
            motor(rightWheel, 60);
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

void turnLeft(int inches) {
    cmpc(leftWheel);
    cmpc(rightWheel);
    
    	while((gmpc(leftWheel)*-1) < (inches * 14.1)) {
        motor(leftWheel, -75);
        if(gmpc(rightWheel) < gmpc((leftWheel)*-1)) {
            motor(rightWheel, 100);
        } else {
            motor(rightWheel, 50);
        }

}
}
void turnRight(int inches) {
        cmpc(leftWheel);
    cmpc(rightWheel);
    	while((gmpc(rightWheel)*-1) < (inches * 13.3)) {
        motor(rightWheel, -75);
        if(gmpc(leftWheel) < gmpc((rightWheel)*-1)) {
            motor(leftWheel, 100);
        } else {
            motor(leftWheel, 50);
        }

}
}

void suckTillHit() {
    while(digital(noodleBump)==0) {
        motor(suckerWheels, -250);
    }
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
    set_servo_position(arm, 450);
    set_servo_position(claw, 2047);
    msleep(200);   
    forwardTillTape();
    off(leftWheel);
    off(rightWheel);
    msleep(1000);
    backOffTape();
    off(leftWheel);
    off(rightWheel); 
    
    msleep(700);
    robotForward(1100);
    off(leftWheel);
    off(rightWheel);    
    //motor(magSpin, 15);
    //msleep(2000);
    //off(magSpin);  
    
    grabNoodle();
    
    enable_servo(arm);
    enable_servo(claw);
    set_servo_position(arm, 450);
    set_servo_position(claw, 2047);   
    
    robotForward(2100);
    
    msleep(1000);
    grabNoodle();
    
    motor(suckerWheels, -250);
    msleep(1000);
    motor(suckerWheels, 250);
    msleep(5000);
}

void startMoving() {
    forwardTillTape();
    backOffTape();
    robotForward(10000);
    msleep(3500);
	turnLeft(97);
	robotForward2(-120, -83);
	msleep(4700);
   	robotForward2(300, 0);
	msleep(800);
    robotForward2(100, 300);
    msleep(600);
	off(leftWheel);
	off(rightWheel);
	getNoodleFromTower();
	getNoodleFromTower();
	getNoodleFromTower();
	robotForward2(75, 72);
	robotForward(4000);
	turnLeft(90);
	 
	
	
    
}
void grabNoodle() {
   set_servo_position(claw, 500);
    msleep(500);    
    set_servo_position(arm, 1600);
    msleep(1000);
    set_servo_position(claw, 2000);
    msleep(500);
    disable_servo(claw);
    msleep(1000); 
    jiggle(); 
}

void getNoodleFromTower() {
    forwardTillTapeAgainstWall();
    msleep(1000);
    backOffTapeAgainstWall();
    msleep(200);
    motor(leftWheel, 75);
    motor(rightWheel, 72);
    msleep(400);    
    motor(leftWheel, 0);
    motor(rightWheel, 0);
    suckTillHit();
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