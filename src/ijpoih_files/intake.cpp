#include "main.h"
//HELPER FUNCTIONS

void setIntake(int power){
    intake = power;
}

//INTAKE DRIVER FUNCTIONS

void setIntakeMotors(){
    int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
    setIntake(intakePower);
}

void intakeDeploy(bool dir){
    intake.tare_position();
    if(dir){
        intake.move_absolute(100, 200); // Moves 100 units forward
        while (!((intake.get_position() < 105) && (intake.get_position() > 95))) {
            // Continue running this loop as long as the motor is not within +-5 units of its goal
            pros::delay(2);
        }
    }
    else{
        intake.move_absolute(-100, 200); // Moves 100 units forward
        while (!((intake.get_position() < 105) && (intake.get_position() > 95))) {
            // Continue running this loop as long as the motor is not within +-5 units of its goal
            pros::delay(2);
        }
        
    }
}