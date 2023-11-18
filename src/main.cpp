#include "main.h"
#include "lemlib/api.hpp"

ASSET(offenseside1_txt);
ASSET(offenseside2_txt);
ASSET(offenseside3_txt);
ASSET(offenseside4_txt);
ASSET(offenseside5_txt);
ASSET(offenseside6_txt);
ASSET(offenseside7_txt);

ASSET(defenceside2_txt);
ASSET(defenceside3_txt);
ASSET(defenceside4_txt);

bool wingsTrue = false;
bool blockerTrue = false;

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
	// chassis.setPose(-33, 54, 180); // X: -33, Y: 54, Heading: 180
	chassis.setPose(-30,-60, 4.712);

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
	blockerDeploy(true);

	turn(150, 180, 20);

	//defence side code
	// chassis.follow(defenceside2_txt, 1000, 10, false, true);
	// wingsDeploy(true);
	// chassis.follow(defenceside3_txt, 1000, 10, false, false);
	// chassis.follow(defenceside4_txt, 1000, 15, false, true);

	//offense side code
	// chassis.follow(offenseside1_txt, 3200, 15, true);
	// pros::delay(1700);
	// intakeDeploy(true);
	// pros::delay(1700);
	// chassis.moveTo(-12, 11, 2.15, 1000);
	// intakeDeploy(false);
	// wingsDeploy(true);
	// chassis.follow(offenseside2_txt, 1500, 10, false);
	
	
	// pros::millis(); //set time to 0
	// chassis.follow(offenseside3_txt, 1000, 15, true);
	// wingsDeploy(false);
	// chassis.moveTo(-39, 0, 1.571, 1000);//90
	// chassis.waitUntilDist(10);
	// intakeDeploy(true);
	// pros::delay(1000);

	// pros::millis();
	// chassis.follow(offenseside4_txt, 1000, 15, true);
	// chassis.waitUntilDist(30);
	// intakeDeploy(true);
	// pros::delay(1000);

	// pros::millis();
	// chassis.follow(offenseside5_txt, 1000, 15, true);
	// chassis.moveTo(-26.586, 28.55, 5.376, 1000);//308
	// chassis.waitUntilDist(5);
	// intakeDeploy(false);
	// pros::delay(1000);

	// pros::millis();
	// chassis.follow(offenseside6_txt, 1000, 15, true);
	// chassis.moveTo(-10, 59, 1.571, 1000);//90
	// wingsDeploy(true);
	
	// chassis.follow(offenseside7_txt, 1000, 15, true);


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

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			wingsTrue = !wingsTrue;
			wingsDeploy(wingsTrue);
			pros::delay(500);
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			blockerTrue = !blockerTrue;
			blockerDeploy(blockerTrue);
			pros::delay(500);
		}

        //2msec Delay for Refresh Rate
        pros::delay(8);
  }
}
