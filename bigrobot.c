#include <kipr/botball.h>




int main(){
    create_connect();
    set_create_distance(0);

    while (get_create_distance() < 448) {
        create_drive_direct(100, 100);
    }
    create_stop();

    
    create_disconnect();
    return 0;
}


