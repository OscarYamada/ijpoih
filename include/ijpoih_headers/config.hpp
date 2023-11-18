#include "main.h"

//Controller and Sensors Headers
extern pros::Controller controller;
extern pros::Imu inertial;
extern pros::Rotation cata_rot;

//Pneumatics and 3Wire Headers
extern pros::ADIDigitalOut wings;
extern pros::ADIDigitalOut blocker;

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
extern pros::MotorGroup leftSide;
extern pros::MotorGroup rightSide;

// Lemlib Drivetrain Header
extern lemlib::Drivetrain_t drivetrain;

// // Odom Pod Encoder Headers
// extern pros::Rotation left_rot;
// extern pros::Rotation right_rot;
// extern pros::Rotation back_rot;

// // Tracking Wheel Headers
// extern lemlib::TrackingWheel left_tracking_wheel;
// extern lemlib::TrackingWheel right_tracking_wheel;
// extern lemlib::TrackingWheel back_tracking_wheel;

// Odometry struct Heading
extern lemlib::OdomSensors_t sensor;

// Chassis Headers
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;
extern lemlib::Chassis chassis;