

#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/DriveWithJoysticks.h"

DriveTrain::DriveTrain() : Subsystems("DriveTrain") {
    leftMotor = RobotMap::driveTrainCANTalonLeft;
    rightMotor = RobotMap::driveTrainCANTalonRight;
    robotDrive21 = RobotMap::driveTrainRobotDrive21;
}

void DriveTrain::InitDefaultCommand() {
        SetDefaultCommand(new DriveWithJoysticks());
}

void DriveTrain::setdrive(float speedleft, float speedright){
	printf("Left: %f\tRight: %f\n", speedleft, speedright);
	robotDrive21.get()->TankDrive(speedleft, speedright);
}

void DriveTrain::openmotors(){
	cANJaguarRight.get()->SetControlMode(CANSpeedController::kPercentVbus);
	cANJaguarRight.get()->EnableControl();
	cANJaguarRight.get()->Set(0.0f);

	cANJaguarLeft.get()->SetControlMode(CANSpeedController::kPercentVbus);
	cANJaguarLeft.get()->EnableControl();
	cANJaguarLeft.get()->Set(0.0f);
}
