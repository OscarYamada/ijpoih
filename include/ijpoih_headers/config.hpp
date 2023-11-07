#include "main.h"

//Cable Sensors and Controller Section
extern pros::Controller controller;
extern pros::Imu inertial;

//3-Wire Sensors Here


//Other Motors
extern pros::Motor intake;
extern pros::Motor cata;

//Left Side Drive Motors
extern pros::Motor LFM;
extern pros::Motor LBB;
extern pros::Motor LTB;

//Right Side Drive Motors
extern pros::Motor RFM;
extern pros::Motor RBB;
extern pros::Motor RTB;

//Miscellaneous Section


// Motor Group
extern pros::MotorGroup LeftSide;
extern pros::MotorGroup RightSide;

// structs
namespace lemlib {
    struct Drivetrain_t;
    struct TrackingWheel;
    struct OdomSensors_t;
    struct ChassisController_t;
    class Chassis;
}

// lemlib drivetrain motors setup
extern lemlib::Drivetrain_t drivetrain;

// Odometry Section
extern pros::ADIEncoder left_enc;
extern pros::Rotation right_rot;
extern pros::ADIEncoder back_enc;

extern lemlib::TrackingWheel left_tracking_wheel;
extern lemlib::TrackingWheel right_tracking_wheel;
extern lemlib::TrackingWheel back_tracking_wheel;

// odometry struct
extern lemlib::OdomSensors_t sensors;

// PID Section
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;

// create the chassis
extern lemlib::Chassis chassis;

