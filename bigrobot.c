#include <kipr/botball.h>

// DRIVING CONSTANTS
const int TAPE_THRESHOLD = 1800;
const int TAPE_SPEED = 250; // mm per second, should be low
const double ROTATION_CONSTANT = 27.0 / 90.0;

int main()
{
    enable_servos();
    create_connect();

    int i = 0;
    while (i == 0)
    {
        printf("%i", get_create_lfcliff_amt());
        printf(",");
        msleep(250);
    }

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
        while (get_create_distance() < (i))
        {
            create_drive_direct(-200, -200);
        }
    }
    create_stop();
}

void forwardTillTape()
{

    while ((get_create_lfcliff_amt() < TAPE_THRESHOLD) || (get_create_rfcliff_amt() < TAPE_THRESHOLD))
    {
        if ((get_create_lfcliff_amt() < TAPE_THRESHOLD) && (get_create_rfcliff_amt() >= TAPE_THRESHOLD))
        {
            create_drive_direct(0.75 * TAPE_SPEED, -0.1 * TAPE_SPEED);
        }
        else if ((get_create_lfcliff_amt() >= TAPE_THRESHOLD) && (get_create_rfcliff_amt() < TAPE_THRESHOLD))
        {
            create_drive_direct(-0.1 * TAPE_SPEED, 0.75 * TAPE_SPEED);
        }
        else
        {
            create_drive_direct(TAPE_SPEED, TAPE_SPEED);
        }
    }
    create_stop();
}

void FromNthTowerToMthTower(int n, int m)
{
    // assumes the robot is not already on a tape
    // m > n

    int i = n;
    while (i <= m)
    {
        printf("%i", get_create_lfcliff_amt());
        printf(",");
        printf("%i", TAPE_THRESHOLD);
        while ((get_create_lfcliff_amt() < TAPE_THRESHOLD))
        {
            printf("%i", get_create_lfcliff_amt());
            create_drive_direct(TAPE_SPEED, TAPE_SPEED);
        }

        create_stop();
        i++;
    }
}

void forwardTillBump()
{
    while (get_create_rbump() == 0)
    {
        create_drive_direct(200, 200);
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
void turnAround()
{
    robotTurn(90);
    robotTurn(90);
}

/*--------------------------------------------------------Claws--------------------------------------------------------*/

// SERVO PINS
const int CLAW = 0;         // powering the claw to open and close
const int CLAW_PARLLEL = 1; // the vertical rotation of the servo for the sake of making the claw move parallel-ly
// MOTOR PINS
const int ORANGE_MOTOR = 0; // this is the motor on the LEFT
const int BLACK_MOTOR = 1;  // this is the motor on the RIGHT
// MOTOR RATIOS
const int MOTOR_ROATION_CONSTANT = 1;

/* ringIndex :
0 - RED
1 - ORANGE
2 - YELLOW
3 - GREEN
4 - BLUE
*/

void initServos()
{
    clawOpen();
    msleep(1000);

    clawParallel(0);
    msleep(1000);
}

const int closeClawPositionList[5] = {245, 245, 320, 650, 690};
void closeClaw(int ringIndex)
{
    set_servo_position(CLAW, closeClawPositionList[ringIndex]);
}
void clawOpen()
{
    set_servo_position(CLAW, 1000);
}

const int clawParallelPositionList[5] = {0, 0, 0, 0, 0};
void clawParallel(int ringIndex)
{
    set_servo_position(CLAW_PARLLEL, clawParallelPositionList[ringIndex]);
}

const int motorBottomTickList[5] = {750, 0, 0, 0, 0}; // in ticks (aka. position) this is for picking up the rings
void motorMoveRingBottom(int ringIndex)
{
    cmpc(ORANGE_MOTOR);
    cmpc(BLACK_MOTOR);

    while (gmpc(ORANGE_MOTOR) < (motorBottomTickList[ringIndex]))
    {
        motor(ORANGE_MOTOR, 75);
        if (gmpc(BLACK_MOTOR) < gmpc(ORANGE_MOTOR))
        {
            motor(BLACK_MOTOR, 100);
        }
        else
        {
            motor(BLACK_MOTOR, 50);
        }
    }
}

void doRingBottom(int ringIndex) // pick up the rings FROM the (bottom)
{
}

/*--------------------------------------------------------Complex Movement--------------------------------------------------------*/

void boxUnderPomPom()
{
    robotTurn(90);
    robotMove(20);

    robotTurn(-90);
    forwardTillBump();
}

void getBotGirl()
{
    FromNthTowerToMthTower(1, 3);
}