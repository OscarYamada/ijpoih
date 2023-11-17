#include "main.h"

// Helper Function
void setCata(int power){
    cata.move(power);
}

// Driver Control Functions - Fire Function
void setCataShoot(){
    // Hold keeps cata spinning, letting go keeps spinning until the arm goes
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        setCata(127);
    }
    else{
        // While Cata rotation sensor is below 60 degrees, it spins
        if(cata_rot.get_position() < 6000){
            setCata(0);
        }
        else{
            setCata(127);
        }
    }
}
