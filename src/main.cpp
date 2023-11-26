#include "main.h"
#include "lemlib/api.hpp"
#include "pros/misc.h"

// Controller and Sensors
pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Imu inertial(17);
pros::Rotation cata_rot(16);

// Pneumatics and 3Wire
pros::ADIDigitalOut wings ('G'); 
pros::ADIDigitalOut blocker ('H');

// drive motors
pros::Motor lF(20, pros::E_MOTOR_GEARSET_06, true); // left front motor. port 8, reversed
pros::Motor lM(18, pros::E_MOTOR_GEARSET_06, true); // left middle motor. port 20, reversed
pros::Motor lB(19, pros::E_MOTOR_GEARSET_06, false); // left back motor. port 19
pros::Motor rF(11, pros::E_MOTOR_GEARSET_06, false); // right front motor. port 2
pros::Motor rM(13, pros::E_MOTOR_GEARSET_06, false); // right middle motor. port 11
pros::Motor rB(12, pros::E_MOTOR_GEARSET_06, true); // right back motor. port 13, reversed

// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group

// Lemlib drivetrain motors setup
lemlib::Drivetrain_t drivetrain {
    &leftMotors, // left drivetrain motors
    &rightMotors, // right drivetrain motors
    11.5, // track width
    3.25, // wheel diameter
    400, // wheel rpm
    8 // Chase power. 8 if traction, 2 if not.
};

// left tracking wheel encoder
// pros::ADIEncoder left_enc('A', 'B', true); // ports A and B, reversed
// right tracking wheel encoder
// pros::Rotation right_rot(1, false); // port 1, not reversed
// back tracking wheel encoder
// pros::ADIEncoder back_enc('C', 'D', false); // ports C and D, not reversed
 
// left tracking wheel
// lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, -4.6); // 2.75" wheel diameter, -4.6" offset from tracking center
// right tracking wheel
// lemlib::TrackingWheel right_tracking_wheel(&right_rot, 2.75, 1.7); // 2.75" wheel diameter, 1.7" offset from tracking center
// lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, 4.5); // 2.75" wheel diameter, 4.5" offset from tracking center
 
// inertial sensor
pros::Imu inertial_sensor(2); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizonal tracking wheel 2
    &inertial // inertial sensor
};
 
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

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
	wings.set_value(false);
	blocker.set_value(false);
    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            // help on this: lemlib(???)telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
// Use lemlib's path gen, as jerryio might not work (it prints out in 4.x lemlib follow format)
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    // example movement: Move to x: 20 and y:15, face heading 90. Timeout set to 4000 ms
    chassis.moveTo(20, 15, 90, 4000);
    // example movement: Turn to face the point x:45, y:-45. Timeout set to 1000
    // dont turn faster than 60 (out of a maximum of 127)
    chassis.turnTo(45, -45, 1000);
    // example movement: Follow the path in path.txt. Timeout set to 4000, Lookahead at 15
    // following the path with the back of the robot (forwards = false)
    // see line 116 to see how to define a path
    chassis.follow(example_txt, 4000, 15, true, false);
    // wait until the chassis has travelled 10 inches. Otherwise the code directly after
    // the movement will run immediately
    // Unless its another movement, in which case it will wait
    chassis.waitUntilDist(10);
    pros::lcd::print(4, "Travelled 10 inches during pure pursuit!");
    // wait until the movement is done
    pros::delay(4000);
    pros::lcd::print(4, "pure pursuit finished!");
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
    // loop to continuously update motors
    while (true) {
        // move chassis. If both joystick values are below 10V at the same time, it doesn't move. Else, move.
        if(!(abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) < 10 && abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)) < 10)){
			chassis.tank(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), 0);
		}
        // delay to save resources
        pros::delay(10);
    }
}