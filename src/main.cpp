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

void setArcade(int left, int turn) {

  frontLeft = (left + turn);
  backLeft = (left + turn);
  frontRight = (left - turn);
  backRight = (left - turn);
    
}

void setDriveMotors() {

  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  int turnP = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  //setDrive(leftJoystick,rightJoystick);
  setArcade(leftJoystick,turnP);
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
bool flywheelBooleanY = false;

void setFlywheelToggle(){
if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            flywheelBoolean = !flywheelBoolean;
            pros::delay(300);
        }
if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            flywheelBooleanY = !flywheelBooleanY;
            pros::delay(300);
        }
}

void setFlywheel(){
    if (flywheelBoolean){
        flywheelFront.move_velocity(550);
		flywheelBack.move_velocity(550);
    }
    else if (flywheelBooleanY){
    flywheelFront.move_velocity(475);
		flywheelBack.move_velocity(475);

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

void moveForward(int x, int delay) {
  frontLeft.move(x);
  frontRight.move(x);
  backLeft.move(x);
  backRight.move(x);
  pros::delay(delay);
  frontLeft.move(0);
  frontRight.move(0);
  backLeft.move(0);
  backRight.move(0);
}

void flyMove(int v, int d){
  flywheelFront.move_velocity(v);
	flywheelBack.move_velocity(v);
  pros::delay(d);
  intake.move_velocity(v);
  pros::delay(500);
 flywheelFront.move_velocity(0);
	flywheelBack.move_velocity(0);
  intake.move_velocity(0);
  }

void rollMove(int i, int drivespeed, int delay){
  intake.move(i);
  frontLeft.move(drivespeed);
  frontRight.move(drivespeed);
  backLeft.move(drivespeed);
  backRight.move(drivespeed);
  pros::delay(delay);
  frontLeft.move(0);
  frontRight.move(0);
  backLeft.move(0);
  backRight.move(0);

}

void autonLeft(){
  moveForward(127,500);
  flyMove(300, 500);
  moveForward(-127,500);
  rollMove(-600,-45,500);
}


void autonRight(){


}

void autonomous() {
autonLeft();
}


void opcontrol() {

	while(true){

		setDriveMotors();
		setIntake();
		setFlywheelToggle();
		setFlywheel();

	}
}
