#include <kipr/botball.h>

// DRIVING CONSTANTS
const int TAPE_THRESHOLD = 1800;
const int TAPE_SPEED = 250; // mm per second, should be low
const double ROTATION_CONSTANT = 27 / 90;

int main()
{
    enable_servos();
    create_connect();

    initServos();

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
        while ((get_create_lfcliff_amt() < TAPE_THRESHOLD))
        {
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
const int TOWER_LEFT = 2;   // this servo is used to drop off the rings on the TOWER
const int TOWER_RIGHT = 3;  // this servo is used to pick up the rings from the FLOOR (tower left and right do different things b/c we want it to go more than 180 degrees)

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

    disable_servo(TOWER_RIGHT);
    msleep(100);
    set_servo_position(TOWER_LEFT, 0);
    msleep(1000);

    clawPickup(0);
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

const int clawPickupPositionList[5] = {1260, 1295, 1380, 1410, 1500};
void clawPickup(int ringIndex)
{
    // The right servo does this
    disable_servo(TOWER_LEFT); // disable to prevent any breaking of servos
    msleep(100);
    enable_servo(TOWER_RIGHT); // enable because it might potentionally be disabled
    msleep(100);
    set_servo_position(TOWER_RIGHT, clawPickupPositionList[ringIndex]);
}

void int clawDropOffPositionList[5] = {0, 0, 0, 0, 0};
void clawDropOff(int ringIndex)
{
    disable_servo(TOWER_RIGHT);
    msleep(100);
    enable_servo(TOWER_LEFT);
    msleep(100);
    set_servo_position(TOWER_LEFT, clawDropOffPositionList[ringIndex]);
}

void doRingBottom(int ringIndex) // pick up the rings FROM the (bottom)
{
    clawOpen();
    msleep(1000);
    clawPickup(ringIndex);
    msleep(1000);
    clawParallel(ringIndex);
    msleep(1000);
    closeClaw(ringIndex);
    msleep(1000);
}

/*--------------------------------------------------------Complex Movement--------------------------------------------------------*/

void boxUnderPomPom()
{
    robotMove(5); // forward to push the box under the pom pom
    robotTurn(90);

    robotMove(5);
}

void getBotGirl()
{
    FromNthTowerToMthTower(1, 3);
    // arm motion
}