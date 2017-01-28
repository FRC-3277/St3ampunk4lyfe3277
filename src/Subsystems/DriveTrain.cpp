

#include "DriveTrain.h"
#include "../RobotMap.h"
//#include "../Commands/DriveWithJoysticks.h"


DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    leftMotor = RobotMap::motorSpeedControllerLeft;
    rightMotor = RobotMap::motorSpeedControllerRight;
    motorRobotDrive25 = RobotMap::motorRobotDrive25;
}

void DriveTrain::InitDefaultCommand() {
       //SetDefaultCommand(new DriveWithJoysticks());
}

void DriveTrain::setdrive(float speedleft, float speedright){
	printf("Left: %f\tRight: %f\n", speedleft, speedright);
	//robotDrive25.get()->TankDrive(speedleft, speedright);
}

//void DriveTrain::openmotors(){
////	rightMotor.get()->SetControlMode(PWMSpeedController::kPercentVbus);
////	rightMotor.get()->EnableControl();
////	rightMotor.get()->Set(0.0f);
////
////	leftMotor.get()->SetControlMode(PWMSpeedController::kPercentVbus);
////	leftMotor.get()->EnableControl();
////	leftMotor.get()->Set(0.0f);
//}
