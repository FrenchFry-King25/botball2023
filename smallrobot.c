#include <kipr/botball.h>
//2.75" from top edge of first tape
//MOTORS
const int leftWheel = 3;
const int rightWheel = 1;
const int suckerWheels = 0;
const int magSpin = 2;

//SERVOS
const int claw = 2; // 2047 open ; 500 closed
const int arm = 1; // 315 down; 1280 up
const int magPin = 3; 
const int magOut = 50;
const int magIn = 10;

const float TICKS_CONSTSANT = .5;

//infared? sensors
const int leftIR = 1;
const int rightIR = 0;
const int lightPort = 2;

// digital buttons 
const int noodleBump = 2;
const int leftBump = 1;
const int rightBump = 0;

const int TAPE_THRESHOLD = 3000;
const int GRAY_THRESHOLD = 2700;

const int MOTOR_SPEED = 250;

const int leftStraight = 60;
const int rightStraight = 60; 

const float K = 1.0;

int main() {
    //enable_servos();
    //start_everything();
    wait_for_light(2); // change the port number to match the port you use
    shut_down_in(119);
    
    
    // leftStraight, rightStraight straight
    
    //robotForward2(-62, -60);
    //msleep(6000000);
    //robotForward2(0, 0);
    //msleep(200);
    //robotForward2(70, 75);
    //msleep(300);
    
    
    //robotForward2(70, 75);
    //msleep(2200);
    //turnRight(90);    
    
    
    enable_servos();
    set_servo_position(claw, 1900);
    set_servo_position(arm, 1300);
    msleep(500);
    set_servo_position(3, 1120);
    msleep(500);
    disable_servos();  
    
    
    //pushOutStackedNoodles();
    
    //turnLeft(90);
    //msleep(30000);
    
    startMoving();   
    
    
    forwardTillBump(); 
    
    robotForward2(-70, -75);
    msleep(450);
    robotForward2(150, 0);
    msleep(1000);  
    robotForward2(-70, -75);
    msleep(400);
    robotForward2(150, 0);
    msleep(1000); 
    
    getNoodlesFromTower();
    
    
    
    
    
    
    //startMoving();
   
    //robotForward(000);
    
    
    //suckTillHit();
    
    
    //enable_servo(arm);
    //enable_servo(claw);
    //set_servo_position(arm, 450);
    //set_servo_position(claw, 2047);
    //disable_servos();
    
    disable_servo(claw);
    
    
    //robotForward2(69, 75);
    //msleep(3000);
    //getNoodlesFromTower();
    //suckTillHit();
    
    //jiggle();
    //getNoodleFromStand(); 
    
    //robotForward2(70, 75);
    //msleep(7000);
    
    
    disable_servos();
    return 0;
    ao();
    
}

void start_everything() {
    enable_servo(arm);
    enable_servo(claw);
    enable_servo(magPin);
    set_servo_position(arm, 450);
    msleep(500);
    set_servo_position(claw, 600); 
    msleep(500);
    set_servo_position(magPin, magOut); 
    msleep(500);
    disable_servo(arm);
    disable_servo(claw);
    disable_servo(magPin);
    // motor(magSpin, 60);
    // msleep(500);   
    // motor(magSpin, 0);
    // msleep(500);
    // motor(magSpin, 60);
    // msleep(30); 
    // motor(magSpin, 0);
    // msleep(500);
}

void jiggleOLD() {
    motor(magSpin, -100);
    msleep(100);
    motor(magSpin, 100);
    msleep(100);  
    motor(magSpin, -100);
    msleep(100);
    motor(magSpin, 100);
    msleep(100);  
    motor(magSpin, 100);
    msleep(10);
    motor(magSpin, 0); 
    msleep(500);
    motor(magSpin, 50);
    msleep(10);      
    motor(magSpin, 0);
    msleep(10);
    motor(magSpin, 50);
    msleep(10);     
    motor(magSpin, 0);
    msleep(10);
    motor(magSpin, 50);
    msleep(10);
    motor(magSpin, 0);
    msleep(500);
    motor(magSpin, 60);
    msleep(30); 
    motor(magSpin, 0);
}

void jiggle() {
    enable_servo(magPin);  
    set_servo_position(magPin, magOut + 100); 
    msleep(100);
    set_servo_position(magPin, magOut); 
    msleep(100);
    set_servo_position(magPin, magOut + 100); 
    msleep(100);
    set_servo_position(magPin, magOut); 
    msleep(100);
    disable_servo(magPin);
}

void jiggle2() {
    motor(magSpin, 100);
    msleep(100);
    motor(magSpin, -100);
    msleep(100);  
    motor(magSpin, 100);
    msleep(100);
    motor(magSpin, -100);
    msleep(100);  
    motor(magSpin, -100);
    msleep(10);
    motor(magSpin, 0); 
    msleep(200);
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
        motor(leftWheel, 110);
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
        motor(leftWheel, leftStraight);
        motor(rightWheel, rightStraight);
    }
    motor(leftWheel, 0);
    motor(rightWheel, 0);
}

void forwardTillTapeAgainstWall() {
    while(analog(leftIR) < GRAY_THRESHOLD) {
        motor(leftWheel, leftStraight);
        motor(rightWheel, rightStraight);
    }
    msleep(200);
    motor(leftWheel, 0);
    motor(rightWheel, 0);
}

void backOffTapeAgainstWall() {
    while(analog(leftIR) > GRAY_THRESHOLD) {
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
            robotForward2(67, 75);
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

void backOnTape() {
    while(analog(leftIR) < TAPE_THRESHOLD || analog(rightIR) < TAPE_THRESHOLD) {
        if(analog(leftIR) < TAPE_THRESHOLD && analog(rightIR) >= TAPE_THRESHOLD ){
            robotForward2(-0.05*MOTOR_SPEED, 0);
        }
        else if(analog(leftIR) >= TAPE_THRESHOLD && analog(rightIR) < TAPE_THRESHOLD ) {
            robotForward2(0, -0.05*MOTOR_SPEED);
        }
        else{
            robotForward2(-25, -25);
        }
    }
}

void forwardOffTape() {
    while(analog(leftIR) > TAPE_THRESHOLD || analog(rightIR) > TAPE_THRESHOLD) {
        if(analog(leftIR) > TAPE_THRESHOLD && analog(rightIR) <= TAPE_THRESHOLD ){
            robotForward2(.05*MOTOR_SPEED, 0);
        }
        else if(analog(leftIR) <= TAPE_THRESHOLD && analog(rightIR) > TAPE_THRESHOLD ) {
            robotForward2(0, 0.05*MOTOR_SPEED);
        }
        else{
            robotForward2(25, 25);
        }
    }
}

void turnLeft(int inches) {
    cmpc(leftWheel);
    cmpc(rightWheel);
    
    	while((gmpc(leftWheel)*-1) < (inches * 17)) {
        motor(leftWheel, -75);
        if(gmpc(rightWheel) < gmpc((leftWheel)*-1)) {
            motor(rightWheel, 100);
        } else {
            motor(rightWheel, 50);
        }
        motor(leftWheel, 0);
        motor(rightWheel, 0);

}
}
void turnRight(int inches) {
        cmpc(leftWheel);
    cmpc(rightWheel);
    	while((gmpc(rightWheel)*-1) < (inches * 21.5)) {
        motor(rightWheel, -75);
        if(gmpc(leftWheel) < gmpc((rightWheel)*-1)) {
            motor(leftWheel, 100);
        } else {
            motor(leftWheel, 50);
        }
        motor(leftWheel, 0);
        motor(rightWheel, 0);

}
}

void suckTillHit() {
    cmpc(suckerWheels);
    while(digital(noodleBump)==0 && gmpc(suckerWheels) > -4000) {
        motor(suckerWheels, -250);
    }
    off(suckerWheels);
}

void suckTillHit2() {
    cmpc(suckerWheels);
    int count = 0;
    while(digital(noodleBump)==0 && gmpc(suckerWheels) > -10000) {
        if(count == 350){jiggle(); count = 0;}
        motor(suckerWheels, -50);
        msleep(2);
        count = count + 1;
    }
    motor(suckerWheels, 0);
    off(suckerWheels);
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
    msleep(300);
    backOffTape();
    off(leftWheel);
    off(rightWheel); 
    
    msleep(200);
    robotForward2(70, 75);
    msleep(630);
    robotForward2(0, 0);
    //motor(magSpin, 15);
    //msleep(2000);
    //off(magSpin);  
    
    grabNoodle();
    
    motor(suckerWheels, 100);
    msleep(900);
    suckTillHit();
    off(suckerWheels);
    
      
    backOnTape();
    msleep(500);
    forwardOffTape();
    
    enable_servo(arm);
    enable_servo(claw);
    set_servo_position(arm, 450);
    set_servo_position(claw, 2047);   
    
    robotForward2(70, 75);
    msleep(1050);   
    robotForward2(0, 0);
    
    msleep(1000);
    grabNoodle();
    //jiggle();
    //jiggle();
    
    motor(suckerWheels, 100);
    msleep(750);
    suckTillHit();
    off(suckerWheels);
    jiggle();
    jiggle();
    
    
    robotForward2(-70, -75);
    msleep(400);
    
    backOnTape();
    msleep(500);
    forwardOffTape();
    
    enable_servo(arm);
    enable_servo(claw);
    set_servo_position(arm, 450);
    set_servo_position(claw, 2047);   
    
    robotForward2(leftStraight, rightStraight);
    msleep(3150); //fix this  
    robotForward2(0, 0);
    
    msleep(1000);
    grabNoodle();
    jiggle();
    jiggle();
    msleep(500);
    motor(magSpin, 60);
    msleep(20); 
    off(magSpin);
    
    //pushOutStackedNoodles();
    
}

void pushOutStackedNoodles() {
    //enindg
    motor(suckerWheels, -250);
    msleep(1000);
    motor(suckerWheels, 250);
    msleep(3000);
    motor(suckerWheels, 0);
    
    jiggle();
    jiggle();
    
    //
    motor(suckerWheels, 250);
    msleep(4000);
    motor(suckerWheels, -50);
    msleep(50);
    jiggle();
    jiggle();
    //suckTillHit();
    motor(suckerWheels, 250);
    msleep(1500);
    motor(suckerWheels, 0);
}

void startMoving() {
    robotForward2(leftStraight, rightStraight);
    msleep(900);    
    robotForward2(0, 0);
    turnLeft(90);
    robotForward2(-62, -60);
    msleep(3500);     
    robotForward2(0, 0);
    start_everything();
    getNoodleFromStand(); 
    
      
    robotForward2(-62, -60);
    msleep(5900);  
    
    turnRight(90);
    robotForward2(60, 60);
    msleep(2000);  
    robotForward2(0, 0);
    
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    pushOutStackedNoodles();
    
    msleep(1000000);
    //this code was moved up - avoid repeating it
    //it's meant to push te wr
    robotForward2(70, 75);
    msleep(1800);
    turnLeft(93);
    msleep(500);  
    robotForward2(-74, -76);
    msleep(500);  
    
    //after switch
    robotForward2(70, 75);
    msleep(3000);
    turnRight(90);
    
    robotForward2(70, 75);
    msleep(1500);
    robotForward2(0, 0);
    pushOutStackedNoodles();
    
    forwardTillBump();
    turnLeft(80);  
    
    robotForward2(leftStraight, rightStraight);
    msleep(1000);
    robotForward2(0, 0);
    msleep(200);
    robotForward2(70, 75);
    msleep(300);
    
    getNoodlesFromTower();
    
}

void startMovingOLD() {
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
	getNoodleFromTower(7000000, 100000);
	getNoodleFromTower(7000000, 10000);
	getNoodleFromTower(7000000,  1000);
	robotForward2(75, 72);
	robotForward(4000);
	turnLeft(90);    
}


void grabNoodle() {
   set_servo_position(claw, 500);
    msleep(500);    
    set_servo_position(arm, 1650);
    msleep(1500);    
    //set_servo_position(claw, 750);
    //msleep(500);
    set_servo_position(claw, 1900);
    msleep(500);
    disable_servo(claw);
    msleep(1000); 
    //jiggle(); 
}


void moveTowersToSwitch () {
	robotForward2(30, 40);
    msleep(2000);
    robotForward2(0, 0);
    forwardTillTape();
    backOnTape();
    backOffTape();
    robotForward2(-70, -75);
    msleep(200);
    robotForward2(0, 0); 
}

void getNoodlesFromTower() {
    
    motor(magSpin, -100);
    msleep(30); 
    motor(magSpin, 0);

    getNoodleFromTower(800, 10);
    
    //turnLeft(2);
    
    motor(leftWheel, 72);
    motor(rightWheel, 75);
    msleep(2000);
    motor(leftWheel, 0);
    motor(rightWheel, 0);
    msleep(500);
    motor(magSpin, 60);
    msleep(800);
    motor(magSpin, 0);
    jiggle();
    getNoodleFromTower(1025, 5);
    
    
    
    motor(leftWheel, leftStraight);
    motor(rightWheel, rightStraight);
    msleep(2200);
    motor(leftWheel, 0);
    motor(rightWheel, 0);
    msleep(500);
    motor(magSpin, 60);
    msleep(800);
    motor(magSpin, 0);
    jiggle();
    getNoodleFromTower(925, 5);
    
}

void getNoodleFromTower(int forwardInt, int spin) {
    forwardTillTapeAgainstWall();
    msleep(1000);
    printf("HERE");
    backOffTapeAgainstWall();
    msleep(1000);
    motor(leftWheel, leftStraight);
    motor(rightWheel, rightStraight);
    msleep(forwardInt); //default is 400;    
    //jiggle();
    //motor(suckerWheels, -250);
    //msleep(700);    
    //motor(suckerWheels, 0);
    //jiggle();
    //motor(suckerWheels, -250);
    //msleep(700);    
    //motor(suckerWheels, 0);
    //jiggle();
    motor(suckerWheels, -250);
    turnRight(spin);
    msleep(700);    
    motor(suckerWheels, 0);
    turnLeft(2);
    jiggle2();
    suckTillHit2();
    motor(suckerWheels, 0);    
    motor(magSpin, -60);
    msleep(300);
    motor(suckerWheels, 70);
    msleep(500);    
    motor(magSpin, 0);
    msleep(3000);
    motor(suckerWheels, 0);
    //motor(magSpin, 60);
    //msleep(800);
    //motor(magSpin, 0);
    turnLeft(spin);
}