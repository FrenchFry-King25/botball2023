#include <kipr/botball.h>

// DRIVING CONSTANTS
const int TAPE_SPEED = 100; // mm per second, should be low
const double ROTATION_CONSTANT = 27.0 / 90.0;
const int ROTATION_RELATIVE_CONSTANT = 20;
const int ROTATION_RELATIVE_CONSTANT_SLOW = 36;

// Tape Thresholds
const int GREY_TAPE_THRESHOLD = 2600;
const int BLACK_TAPE_THRESHOLD = 1000;

int main()
{
    enable_servos();
    create_connect();

    // initServos();
    // getBotGirl();

    // AfterBotGirlGrab();
    // moveToRings();

    create_drive_direct(0, -500);
    msleep(1000);
    // robotTurnAboutRight(-90);

    // botGirlClaw();

    create_disconnect();
    disable_servos();
    ao();

    return 0;
}

/*--------------------------------------------------------Movement--------------------------------------------------------*/

void robotMove(int i)
{
    set_create_distance(0);
    if (i > 0)
    {
        while (-1 * get_create_distance() < (i))
        {
            create_drive_direct(200, 200);
        }
    }
    else
    {
        while (-1 * get_create_distance() > (i))
        {
            create_drive_direct(-200, -200);
        }
    }
    create_stop();
}

void forwardTillTape(int LEFT_THRESHOLD, int RIGHT_THRESHOLD)
{

    while ((get_create_lcliff_amt() > LEFT_THRESHOLD) &&
           (get_create_rcliff_amt() > RIGHT_THRESHOLD))
    {
        create_drive_direct(TAPE_SPEED, TAPE_SPEED);
    }
    create_stop();
}
void forwardTillRightTape(int RIGHT_THRESHOLD)
{
    while (get_create_rcliff_amt() > RIGHT_THRESHOLD)
    {
        create_drive_direct(TAPE_SPEED, TAPE_SPEED);
    }
    create_stop();
}
void forwardTillLeftTape(int LEFT_THRESHOLD)
{
    while (get_create_lcliff_amt() > LEFT_THRESHOLD)
    {
        create_drive_direct(TAPE_SPEED, TAPE_SPEED);
    }
    create_stop();
}
void forwardTillBothTape(int LEFT_THRESHOLD, int RIGHT_THRESHOLD)
{
    while ((get_create_lcliff_amt() > LEFT_THRESHOLD) || get_create_rcliff_amt() > RIGHT_THRESHOLD)
    {
        create_drive_direct(100, 100);
    }
    create_stop();
}

void MoveNTowers(int n)
{
    // assumes the robot is not already on a tape
    // m > n

    int i = 0;
    while (i <= n)
    {
        while ((get_create_lcliff_amt() < GREY_TAPE_THRESHOLD))
        {
            create_drive_direct(TAPE_SPEED, TAPE_SPEED);
        }

        create_stop();
        i++;
    }
}

void forwardTillOnceBump()
{
    while (get_create_rbump() == 0 && get_create_lbump() == 0)
    {
        create_drive_direct(100, 100);
    }
    create_stop();
}
void forwardTillBothBump()
{
    while (get_create_lbump() == 0 || get_create_rbump() == 0)
    {
        if (get_create_lbump() == 1 && get_create_rbump() == 0)
        { // left switch is clicked
            create_drive_direct(0, 100);
        }
        else if (get_create_lbump() == 0 && get_create_rbump() == 1)
        { // right switch is pressed
            create_drive_direct(100, 0);
        }
        else
        {
            create_drive_direct(100, 100);
        }
    }
}

/*--------------------------------------------------------Rotation--------------------------------------------------------*/

void robotTurn(int angle)
{
    set_create_total_angle(0);

    if (angle < 0)
    {
        while (-1 * get_create_total_angle() > angle * ROTATION_CONSTANT)
        {
            create_drive_direct(-200, 200);
        }
    }
    else
    {
        while (-1 * get_create_total_angle() < angle * ROTATION_CONSTANT)
        {
            create_drive_direct(200, -200);
        }
    }
}
void robotTurnAboutRight(int angle)
{
    if (angle < 0)
    {
        create_drive_direct(200, 0);
        msleep(-1 * angle * ROTATION_RELATIVE_CONSTANT);
    }
    else
    {
        create_drive_direct(-200, 0);
        msleep(angle * ROTATION_RELATIVE_CONSTANT);
    }

    create_stop();
}
void robotTurnAboutLeft(int angle)
{
    if (angle < 0)
    {
        create_drive_direct(0, 200);
        msleep(-1 * angle * ROTATION_RELATIVE_CONSTANT);
    }
    else
    {
        create_drive_direct(0, -200);
        msleep(angle * ROTATION_RELATIVE_CONSTANT);
    }

    create_stop();
}
void robotTurnAboutLeftSlow(int angle)
{
    if (angle < 0)
    {
        create_drive_direct(0, 100);
        msleep(-1 * angle * ROTATION_RELATIVE_CONSTANT_SLOW);
    }
    else
    {
        create_drive_direct(0, -100);
        msleep(angle * ROTATION_RELATIVE_CONSTANT_SLOW);
    }

    create_stop();
}

/*--------------------------------------------------------Claw--------------------------------------------------------*/

// SERVO PINS
const int CLAW = 0;         // powering the claw to open and close
const int CLAW_PARLLEL = 1; // the vertical rotation of the servo for the sake of making the claw move parallel-ly
// MOTOR PINS
const int CLAW_MOTOR = 1; // used to move the claw up and down using rotation
const int MOTOR_ROATION_CONSTANT = 1;

void initServos()
{
    set_servo_position(CLAW, 600);
    msleep(1000);

    set_servo_position(CLAW_PARLLEL, 0);
    msleep(1000);
}

void moveClawY(int ticks)
{

    cmpc(CLAW_MOTOR);

    if (ticks < 0)
    {
        while (gmpc(CLAW_MOTOR) > ticks)
        {
            motor(CLAW_MOTOR, -20);
        }
    }
    else
    {
        while (gmpc(CLAW_MOTOR) < ticks)
        {
            motor(CLAW_MOTOR, 20);
        }
    }

    off(CLAW_MOTOR);
}
void moveClawYSlow(int ticks)
{

    cmpc(CLAW_MOTOR);

    if (ticks < 0)
    {
        while (gmpc(CLAW_MOTOR) > ticks)
        {
            motor(CLAW_MOTOR, -10);
        }
    }
    else
    {
        while (gmpc(CLAW_MOTOR) < ticks)
        {
            motor(CLAW_MOTOR, 10);
        }
    }

    motor(CLAW_MOTOR, 0);
}

void moveClawParallel(int position)
{
    set_servo_position(CLAW_PARLLEL, position);
}
void moveClaw(int position)
{
    set_servo_position(CLAW, position);
}

/*--------------------------------------------------------BotGirl--------------------------------------------------------*/

void initBotGirl()
{
    moveClawParallel(1500);
    msleep(500);
    moveClaw(1100);
    msleep(500);
}

void botGirlClaw()
{
    initBotGirl();

    moveClawY(-850);
    msleep(500);

    moveClawParallel(1250);
    msleep(500);

    moveClaw(0);
    moveClawParallel(1500);
    msleep(2000);

    moveClaw(0);
    moveClawParallel(1600);
    msleep(500);

    moveClawY(800);
}
void AfterBotGirlGrab()
{
    robotMove(-75);
    robotTurnAboutRight(-90);
    robotTurnAboutRight(-90);
    forwardTillOnceBump();
    moveClaw(1800);
    msleep(500);
    robotMove(-60);
}

void getBotGirl()
{
    forwardTillTape(BLACK_TAPE_THRESHOLD, BLACK_TAPE_THRESHOLD);
    robotTurn(-45);
    robotMove(40);

    moveClawY(-400);

    forwardTillOnceBump();
    msleep(500);
    robotMove(-1);

    robotTurn(45);

    forwardTillTape(GREY_TAPE_THRESHOLD, BLACK_TAPE_THRESHOLD);
    msleep(500);
    robotMove(8);

    msleep(2500);

    botGirlClaw();

    AfterBotGirlGrab();
}

/*--------------------------------------------------------Rings--------------------------------------------------------*/

/* ringIndex :
0 - RED
1 - ORANGE
2 - YELLOW
3 - GREEN
4 - BLUE
*/
void moveToRings()
{
    robotTurn(-90);
    forwardTillBothBump();
    robotMove(-23);
    robotTurn(-90);
    disable_servos();
    forwardTillBothTape(BLACK_TAPE_THRESHOLD, BLACK_TAPE_THRESHOLD);
    msleep(500);
    robotMove(3);
    enable_servos();

    moveClaw(600);
    msleep(1000);

    robotMove(-30);

    moveClaw(0);
    create_drive_direct(0, -200);
    msleep(90 * ROTATION_RELATIVE_CONSTANT);

    robotMove(-20);
}

void initRings()
{
    set_servo_position(CLAW, 600);
    msleep(1000);

    set_servo_position(CLAW_PARLLEL, 0);
    msleep(1000);
}

const int closeClawPositionList[5] = {245, 245, 320, 650, 690};
void closeClaw(int ringIndex)
{
    moveClaw(closeClawPositionList[ringIndex]);
    msleep(1000);
}
void clawOpen()
{
    set_servo_position(CLAW, 1000);
    msleep(1000);
}

const int clawParallelPositionList[5] = {2047, 0, 0, 0, 0};
void ringParallel(int ringIndex)
{
    moveClawParallel(clawParallelPositionList[ringIndex]);
    msleep(1000);
}

const int motorTickListDown[5] = {750, 0, 0, 0, 0}; // in ticks (aka. position) this is for picking up the rings
void ringYDown(int ringIndex)
{
    off(CLAW_MOTOR);
    msleep(2000);

    moveClawY(motorTickListDown[ringIndex]);
}

void ringDown(int ringIndex) // pick up the rings FROM the (bottom)
{
    ringYDown(ringIndex);
    ringParallel(ringIndex);
    closeClaw(ringIndex);
}