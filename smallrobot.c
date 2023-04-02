#include <kipr/botball.h>

const int leftWheel = 0;
const int rightWheel = 1;

const float TICKS_CONSTSANT = .5;


int main() {
    enable_servos();
    
    disable_servos();
    ao();
    return 0;
}

void forward(int inches){
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
}

void releaseNoodle(){

}