#include "main.h"

//Must Mirror motor_config.hpp
pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Imu inertial(16);

pros::Motor intake (20, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor cata (11, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

pros::Motor LFM (19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor LBB (17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor LTB (18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

pros::Motor RFM (12, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor RBB (13, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor RTB (14, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

//Motor Groups
pros::MotorGroup LeftSide({LFM, LBB, LTB});
pros::MotorGroup RightSide({RFM, RBB, RTB});


// lemlib drivetrain motors setup

lemlib::Drivetrain_t drivetrain {
    &LeftSide, // left drivetrain motors
    &RightSide, // right drivetrain motors
    11.5, // track width
    3.25, // wheel diameter
    400 // wheel rpm
};
 

//Odometry Section

// left tracking wheel encoder
pros::ADIEncoder left_enc('A', 'B', true); // ports A and B, reversed
// right tracking wheel encoder
pros::Rotation right_rot(1, false); // port 1, not reversed
// back tracking wheel encoder
pros::ADIEncoder back_enc('C', 'D', false); // ports C and D, not reversed
 
// Tracking Wheel Objects
lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, -4.6); // 2.75" wheel diameter, -4.6" offset from tracking cente
lemlib::TrackingWheel right_tracking_wheel(&right_rot, 2.75, 1.7); // 2.75" wheel diameter, 1.7" offset from tracking center
lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, -4.5); // 2.75" wheel diameter, 4.5" offset from tracking center
 

// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizonal tracking wheel 2
    &inertial // inertial sensor
};
 

// PID Section

// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);