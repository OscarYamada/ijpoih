#include "main.h"

//HELPER FUNCTIONS

void setDrive(int left, int right){
    leftSide.move(left);
    rightSide.move(right);
}

//DRIVER CONTROL FUNCTIONS
void setDriveMotors(){
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if (abs(leftJoystick) < 12)
        leftJoystick = 0;
    if (abs(rightJoystick) < 12)
        rightJoystick = 0;
    setDrive(leftJoystick, rightJoystick);
}

void turn(float lowerbound, float upperbound, int leftpower){
    while(inertial.get_yaw() > lowerbound && inertial.get_yaw() < upperbound){
        leftSide.move_absolute(50, leftpower);
        rightSide.move_absolute(50, -leftpower);
        pros::delay(5);
    }
}