#include "main.h"

//Cable Sensors and Controller Headers
extern pros::Controller controller;
extern pros::Imu inertial;

//3-Wire Sensor Headers


//Other Motor Headers
extern pros::Motor intake;
extern pros::Motor cata;

//Left Side Drive Motor Headers
extern pros::Motor LFM;
extern pros::Motor LBB;
extern pros::Motor LTB;

//Right Side Drive Motor Headers
extern pros::Motor RFM;
extern pros::Motor RBB;
extern pros::Motor RTB;

// Motor Group Headers
extern pros::MotorGroup LeftSide;
extern pros::MotorGroup RightSide;

//Miscellaneous Section
extern pros::Rotation cata_rot;

// Lemlib Drivetrain Header
extern lemlib::Drivetrain drivetrain;

// Odom Pod Encoder Headers
extern pros::Rotation left_rot;
extern pros::Rotation right_rot;
extern pros::Rotation back_rot;

// Tracking Wheel Headers
extern lemlib::TrackingWheel left_tracking_wheel;
extern lemlib::TrackingWheel right_tracking_wheel;
extern lemlib::TrackingWheel back_tracking_wheel;
extern lemlib::OdomSensors_t sensor;

// Chassis Headers
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;
extern lemlib::Chassis chassis;