#include <kipr/wombat.h>

const int claw = 2; // 2047 open ; 500 closed
const int arm = 1; // 315 down; 1280 up
const int magPin = 3; 
const int magOut = 50;

int main()
{
    printf("Hello World\n");
    enable_servos();
    set_servo_position(arm, 1300);
    set_servo_position(claw, 1900);
    msleep(500);
    set_servo_position(magPin, magOut);
    msleep(500);
    disable_servos();
    
    return 0;
}
