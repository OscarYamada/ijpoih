#include "main.h"

//Must Mirror motor_config.hpp

// Controller and Sensors
pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Imu inertial(17);
pros::Rotation cata_rot(4, true);

// Pneumatics and 3Wire
pros::ADIDigitalOut left_wing ('A'); 
pros::ADIDigitalOut right_wing ('B');
pros::ADIDigitalOut left_intake ('C');
pros::ADIDigitalOut right_intake ('D');
pros::ADIDigitalOut left_blocker ('E');
pros::ADIDigitalOut right_blocker ('F');

// Cata and Intake
pros::Motor intake (14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor cata (15, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

// Motors Left Side (right, front/bottom/top, middle/back)
pros::Motor LFM (20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LBB (19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LTB (18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

// Motors Right Side (right, front/bottom/top, middle/back)
pros::Motor RFM (11, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor RBB (12, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor RTB (13, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

// Motor Groups
pros::MotorGroup leftSide({LFM, LBB, LTB});
pros::MotorGroup rightSide({RFM, RBB, RTB});

// Lemlib drivetrain motors setup
lemlib::Drivetrain_t drivetrain {
    &leftSide, // left drivetrain motors
    &rightSide, // right drivetrain motors
    11.5, // track width
    3.25, // wheel diameter
    400, // wheel rpm
    8 // Chase power. 8 if traction, 2 if not.
};
 

//Odometry Section

// // left tracking wheel encoder
// pros::Rotation left_rot(3, true); // ports A and B, reversed
// // right tracking wheel encoder
// pros::Rotation right_rot(1, false); // port 1, not reversed
// // back tracking wheel encoder
// pros::Rotation back_rot(2, false); // ports C and D, not reversed
 
// // Tracking Wheel Objects
// lemlib::TrackingWheel left_tracking_wheel(&left_rot, 3.25, -4.6); // 2.75" wheel diameter, -4.6" offset from tracking cente
// lemlib::TrackingWheel right_tracking_wheel(&right_rot, 3.25, 1.7); // 2.75" wheel diameter, 1.7" offset from tracking center
// lemlib::TrackingWheel back_tracking_wheel(&back_rot, 3.25, -4.5); // 2.75" wheel diameter, 4.5" offset from tracking center
 

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