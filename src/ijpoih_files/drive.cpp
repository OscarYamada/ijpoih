#include "main.h"

//HELPER FUNCTIONS

void setDrive(int left, int right){
    LeftSide = left;
    RightSide = right;
}

//DRIVER CONTROL FUNCTIONS

void setDriveMoters(){
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if (abs(leftJoystick) < 15)
        leftJoystick = 0;
    if (abs(rightJoystick) < 15)
        rightJoystick = 0;
    void setDrive(leftJoystick, rightJoystick);
}