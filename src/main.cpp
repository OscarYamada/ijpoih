#include "main.h"
#include "lemlib/api.hpp"
ASSET(offenseside1_txt);
ASSET(offenseside2_txt);
ASSET(offenseside3_txt);
ASSET(offenseside4_txt);
ASSET(offenseside5_txt);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate the chassis
	chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

	// Set Brake Modes
	leftSide.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // Set brake to coast on left side of Drivetrain
	rightSide.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // Set brake to coast on right side of Drivetrain
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); // For some reason, hold and brake have different setbrake functions
	cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); // Brake hold on intake and cata
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

	on_center_button();
	screenSetup();
	
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// 2000 is the interval the follow lasts for. change it accordingly
	// to the autonomous.
	// also, lookahead distance, look into that, but it's probably not
	// important right now. save it for when we tune auton.


	pros::millis(); //set time to 0

	// Offense Auto (all triball + under hang + enemy matchload)
	//PATH 1:
	chassis.follow(offenseside1_txt, 2000, 15);
	// intake for grabbing triball
	chassis.waitUntilDist(10);
	intakeDeploy(true);
	// wings open after grabbing first triball
	pros::delay(1000);
	wingsDeploy(true);
	chassis.waitUntilDist(10000);
	wingsDeploy(false);

	//PATH 2:
	chassis.follow(offenseside2_txt, 2000, 15, true);
	//180 degree turn
	chassis.waitUntilDist(10000);
	chassis.turnTo(-26, 0, 1000, 200);

	//PATH 3:
	chassis.follow(offenseside3_txt, 2000, 15);
	//intake to pick up triball
	chassis.waitUntilDist(10);
	intakeDeploy(false);
	//intake for putting down triball
	chassis.waitUntilDist(20);
	intakeDeploy(true);
	// add async for grabbing triball underneath the hang
	chassis.waitUntilDist(10000);
	intakeDeploy(true);

	//PATH 4:
	chassis.follow(offenseside4_txt, 2000, 15, true);
	//180 degree turn
	chassis.waitUntilDist(10000);
	chassis.turnTo(-30, 60, 1000, 200);

	//PATH 5:
	chassis.follow(offenseside5_txt, 2000, 15);
	pros::delay(1000);
	intakeDeploy(true);
	// then it goes 3 into the goal rite

	//PATH 6:
	chassis.follow(offenseside5_txt, 2000, 15, true);
	//turn 180 degrees to hang
	chassis.turnTo(-10, 60, 1000, 200);
	//Touch intake to hang
	chassis.follow(offenseside4_txt, 2000, 15);



}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while (true) {
		// Drive, Intake, and Cata functions from the different cpp files
		setDriveMotors();
		setIntakeMotors();
		setCataShoot();
		setCataBlockIntake();

        //2msec Delay for Refresh Rate
        pros::delay(2);
  }
}
