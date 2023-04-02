#include <kipr/botball.h>
#include "Claw.h"

// SERVO PINS
const int TOWER_RIGHT = 0;  //
const int TOWER_LEFT = 1;   // the servo that is moving the bridge(holding the servos up and down)
const int CLAW_PARLLEL = 3; // the vertical rotation of the servo for the sake of making the claw move parallel-ly
const int CLAW = 4;         // powering the claw to open and close

// CLAW CONSTANTS
const int CLAW_OPEN_POSITION = 0;
const int CLAW_CLOSED_POSITION = 0;
const int CLAW_DELAY = 100;

// DRIVING CONSTANTS
const int INCHES_CONSTANT = 0.9;
const int TAPE_THRESHOLD = 1800;
const int TAPE_SPEED = 250 ;

// ARM CONSTANTS
const int TOWER_RIGHT_MAX = 1800; // putting rings in towers
const int RIGHT_ARM_MAX = 20;
const int LEFT_ARM_MIN = 20; // collecting rings
const int RIGHT_ARM_MIN = 1800;

int main()
{
    enable_servos();
    create_connect();

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

void putRingIndex(int ringIndex)
{
    /*
    ringIndex :

    0 - red ring
    1 - orange ring
    2 - yellow ring
    3 - green ring
    4 - blue ring
    */

    switch (ringIndex)
    {
    case 0:
    }
}

void putRing()
{
}

void forward(int i)
{
    set_create_distance(0);
    while (get_create_distance() < (i * INCHES_CONSTANT))
    {
        create_drive_direct(100, 100);
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

void forwardTillBump() {
    while ((get_create_distance() < 1000) && (get_create_rbump() == 0)) {
        create_drive_direct(200, 200);
    } 
}

void turnLeft(int degrees)
{
    set_create_total_angle(0);
    while (get_create_total_angle() < degrees)
    {
        create_drive_direct(-100, 100);
    }
    create_stop();
}

void turnRight(int degrees)
{
    set_create_total_angle(0);
    while (get_create_total_angle() > (degrees * -1))
    {
        create_drive_direct(100, -100);
    }
    create_stop();
}

void openClaw()
{
    set_servo_position(CLAW, CLAW_OPEN_POSITION);
    msleep(CLAW_DELAY);
}

void closeClaw()
{
    set_servo_position(CLAW, CLAW_CLOSE_POSOTION);
    msleep(CLAW_DELAY)
}