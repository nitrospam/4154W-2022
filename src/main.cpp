#include "main.h"

pros::Motor frontLeft(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontRight(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backLeft(4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backRight(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelFront(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelBack(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Controller controller(pros::E_CONTROLLER_MASTER);

void setDrive(int left, int right) {

  frontLeft = left;
  backLeft = left;
  frontRight = right;
  backRight = right;

}

void setDriveMotors() {

  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  setDrive(leftJoystick,rightJoystick);

}

void setIntake() {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            intake.move_velocity(600);
        }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            intake.move_velocity(200);
        }
	else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            intake.move_velocity(-500);
        }
    else {
            intake = 0;
        }
}

bool flywheelBoolean = false;

void setFlywheelToggle(){
if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            flywheelBoolean = !flywheelBoolean;
            pros::delay(300);
        }
}

void setFlywheel(){
    if (flywheelBoolean){
        flywheelFront.move_velocity(600);
		flywheelBack.move_velocity(600);
    }
    else {
        flywheelFront = 0;
		flywheelBack = 0;
    }
}


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}


void disabled() {}

void competition_initialize() {}


void autonomous() {}


void opcontrol() {

	while(true){

		setDriveMotors();
		setIntake();
		setFlywheelToggle();
		setFlywheel();

	}
}
