#include "main.h"

// Helper Function
void setCata(int power){
    cata = power;
}

// Driver Control Functions
void setCataShoot{
    // Hold keeps cata spinning, letting go keeps spinning until the arm goes
    while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        setCata(127);
    }
    setCata(0);
}

void setCataBlockIntake{
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        // While rotation sensor is below 45 degrees
        while(cata_rot.get_position() > 7000){
            setCata(127);
        }
        setCata(0);
    }
}