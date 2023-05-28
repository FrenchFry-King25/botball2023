#include <kipr/botball.h>

int main()
{
    enable_servos();
    create_connect();

    printf("Starting...");

    printf("Ending...");
    disable_servos();
    create_disconnect();
    ao();
}

//-----------------------------------------------------------------
//-------------------------Driving---------------------------------
//-----------------------------------------------------------------
const int BLACK_TAPE = 100;
const int GREY_TAPE = 100;
const int NO_TAPE = -1; // very small number, smaller the darker

void robotMove(int distance, int speed)
{
    set_create_distance(0);
    if (distance > 0)
    { // if want to move forward
        while (-1 * get_create_distance() < distance)
        {
            create_drive_direct(speed, speed);
        }
    }
    else
    {
        while (-1 * get_create_distance() > distance)
        {
            create_drive_direct(-speed, -speed);
        }
    }
    create_stop();
}

void robotTurn(int angle, int speed)
{
}

void forwardTillTape(int leftThres, int rightThres, int speed)
{
    while ((get_create_lcliff_amt() > leftThres) && (get_create_rcliff_amt() > rightThres))
    {
        create_drive_direct(speed, speed);
    }
}

void forwardTillBump(int speed, bool both) // both bump or one bump
{
    if (both == true)
    {
    }
    else
    {
        }
}

//-----------------------------------------------------------------
//-------------------------Helper----------------------------------
//-----------------------------------------------------------------
static int bezier_a, bezier_b, bezier_c, bezier_d; // inputs for bezier

int cubic_bezier(int x)
{ // converts the input into a curve on bezier
    // use bezier_a,b,c,d....
    return 0;
}

/*
Todo :
*forwardTillBump
*robotTurn
*cubic_bezier
*/