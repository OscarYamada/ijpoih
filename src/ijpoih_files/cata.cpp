#include "main.h"

// Helper Function
void setCata(int power){
    cata.move(power);
}

// Driver Control Functions - Fire Function
void setCataShoot(){
    // Hold keeps cata spinning, letting go keeps spinning until the arm goes
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        setCata(127);
    }
    else if(cata_rot.get_angle() < 50 || cata_rot.get_angle() > 340){
        setCata(127);
    }
    else{
        setCata(0);
    }
}
