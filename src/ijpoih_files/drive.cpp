#include "main.h"

//HELPER FUNCTIONS

void setDrive(int left, int right){
    LeftSide = left;
    RightSide = right;
}

void resetDriveEncoders(){
    leftSide.tare_position();
    rightSide.tare_position();
}

double avgDriveEncoderValue(){
    return (fabs(leftSide.get_position()) + fabs(rightSide.get_position()))/2
}

//DRIVER CONTROL FUNCTIONS

void setDriveMoters(){
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if (abs(leftJoystick) < 10)
        leftJoystick = 0;
    if (abs(rightJoystick) < 10)
        rightJoystick = 0;
    void setDrive(leftJoystick, rightJoystick);
}

//AUTONOMOUS FUNCTIONS
void translate(int units, int voltage){
    int direction = abs(units)/units;
    //reset motor encoders
    resetDriveEncoders();
    //dirve forward unitl units are reached
    while(fabs(leftSide.get_position()) < abs(units)){
        setdrive(voltage * direction, voltage * direction);
        pros::delay(10);
    }

    //brief brake

    setDrive(-10* direction, -10 * direction);
    pros::delay(50);

    //set drive back to neutral
    setDrive(0,0);
}