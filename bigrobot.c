#include <kipr/botball.h>

// SERVO PINS
const int TOWER_RIGHT = 0;  //
const int TOWER_LEFT = 1;   // the servo that is moving the bridge(holding the servos up and down)
const int CLAW_PARLLEL = 3; // the vertical rotation of the servo for the sake of making the claw move parallel-ly
const int CLAW = 4;         // powering the claw to open and close

// CLAW CONSTANTS
const int CLAW_OPEN_POSITION = 0;
const int CLAW_CLOSE_POSITION = 0;
const int CLAW_DELAY = 100;

// DRIVING CONSTANTS
const int TAPE_THRESHOLD = 1800;
const int TAPE_SPEED = 250 ; // mm per second, should be low
const double ROTATION_CONSTANT = 27 / 90;

// ARM CONSTANTS
const int TOWER_RIGHT_MAX = 1800; // putting rings in towers
const int RIGHT_ARM_MAX = 20;
const int LEFT_ARM_MIN = 20; // collecting rings
const int RIGHT_ARM_MIN = 1800;


int main()
{
    enable_servos();
    create_connect();
    
    robotMove(100);

    create_disconnect();
    disable_servos();
    ao();
    
    
    return 0;
}


void initServoTowers()
{
    set_servo_position(TOWER_RIGHT, 0);
    set_servo_position(TOWER_LEFT, 0);
    set_servo_position(CLAW_PARLLEL, 1535);
    set_servo_position(CLAW, 1023);
}

//Movement

void robotMove(int i){
    set_create_distance(0);
    if(i > 0){
        while (-1 * get_create_distance() < (i)){
            create_drive_direct(200, 200);
        }
    }else{
        while(get_create_distance() < (i)){
            create_drive_direct(-200, -200);
        }
    }
    create_stop();
}

void forwardTillTape() { 

    while ( (get_create_lfcliff_amt() < TAPE_THRESHOLD) || (get_create_rfcliff_amt() < TAPE_THRESHOLD) ){
        if ( (get_create_lfcliff_amt() < TAPE_THRESHOLD) && (get_create_rfcliff_amt() >= TAPE_THRESHOLD) ) {
            create_drive_direct(0.75*TAPE_SPEED, -0.1*TAPE_SPEED);
        }
        else if ( (get_create_lfcliff_amt() >= TAPE_THRESHOLD) && (get_create_rfcliff_amt() < TAPE_THRESHOLD) ) {
            create_drive_direct(-0.1*TAPE_SPEED, 0.75*TAPE_SPEED);
        }
        else {
            create_drive_direct(TAPE_SPEED,TAPE_SPEED);
        }
    }
    create_stop();
}

void FromNthTowerToMthTower(int n, int m){ 
    // assumes the robot is not already on a tape
    // m > n
    
   int i = n;
   while (i <= m){
   	  while( (get_create_lfcliff_amt() < TAPE_THRESHOLD) ){
          create_drive_direct(TAPE_SPEED, TAPE_SPEED);
      }

      create_stop();
      i++;
   }
}

void forwardTillBump() {
    while (get_create_rbump() == 0) {
        create_drive_direct(200, 200);
    } 
}



void turnAround(){
    robotTurn(90);
    robotTurn(90);
}


void boxUnderPomPom(){
    robotMove(5); //forward to push the box under the pom pom
    robotTurn(90);

    robotMove(5);
}

void getBotGirl(){
    FromNthTowerToMthTower(1, 3);
    //arm motion
}




//Rings : 
// void liftArm() {
//     set_servo_position(TOWER_RIGHT, 0);
//     set_servo_position(TOWER_LEFT, 100);
//     msleep(1000);
// }

// void lowerArm(){
//     set_servo_position(TOWER_RIGHT, 100);
//     set_servo_position(TOWER_LEFT, 0);
//     msleep(1000);
// }

// void doRing(int ringIndex)
// {

//     /*
//     ringIndex 
//     0 - red ring
//     1 - orange ring
//     2 - yellow ring
//     3 - green ring
//     4 - blue ring
//     */

//    enable_servos();
   
//    setClawYRingPosition(ringIndex);
//    setClawParallelPosition(ringIndex);
//    setClawClosePosition(ringIndex);

//    disable_servos();
// }

// void openClaw()
// {
//     set_servo_position(CLAW, CLAW_OPEN_POSITION);
//     msleep(CLAW_DELAY);
// }

// void setClawClosePosition(int ringIndex)
// {
//     int ClawClosePositions[5] = {};
//     set_servo_position(CLAW, ClawClosePositions[ringIndex]); 
//     msleep(1000);
// }
// void setClawYRingPosition(int ringIndex){
//     int ClawYRingPositions[5] = {1361, 1431, 1522, 1540, 1616};
//     set_servo_position(TOWER_RIGHT, ClawYPositions[ringIndex]);
//     msleep(1000);
// }
// void setClawYTowerPosition(int ringIndex){
//     int ClawYTowerPositions[5] = {};
//     set_servo_position(TOWER_LEFT, ClawYTowerPositions[ringIndex]);
// }
// void setClawParallelPosition(int ringIndex){
//     int ClawParallelPosition[5] = {123, 123, 0, 0, 0};
//     set_servo_position(CLAW_PARLLEL, ClawParallelPosition[ringIndex]);
//     msleep(1000);
// }