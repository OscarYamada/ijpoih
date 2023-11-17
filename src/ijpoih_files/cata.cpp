#include "main.h"

// Helper Function
void setCata(int power){
    cata = power;
}

// Driver Control Functions - Fire Function
void setCataShoot(){
    // Hold keeps cata spinning, letting go keeps spinning until the arm goes
    if(!(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))){
        // While Cata rotation sensor is below 70 degrees, it spins
        if(!(cata_rot.get_position() < 7000)){
            setCata(127);
        }
        else{
            setCata(0);
        }
    }
    else{
        setCata(127);
    }
}

// Driver Control Functions - Intake Block
void setCataBlockIntake(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        // While rotation sensor is below 45 degrees
        while(!(cata_rot.get_position() > 5000 && cata_rot.get_position() < 6000)){
            setCata(127);
        }
        setCata(0);
    }
}