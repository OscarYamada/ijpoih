#include "main.h"
//HELPER FUNCTIONS

void setIntake(int power){
    intake = power;
}

//INTAKE DRIVER FUNCTIONS

void setIntakeMotors(){
    int intakePower = 127* (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    setIntake(intakePower);
}