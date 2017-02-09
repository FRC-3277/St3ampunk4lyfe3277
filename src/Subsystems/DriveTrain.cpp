#include "CANTalon.h"
#include "CANSpeedController.h"

#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/OperatorInputDriveTrain.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    portTalon = RobotMap::driveTrainPortTalon;
    starboardTalon = RobotMap::driveTrainStarboardTalon;
    steamEngineRobotDrive = RobotMap::driveTrainSteamEngineRobotDrive;

    portTalon->SetControlMode(CANSpeedController::kPercentVbus);
    portTalon->EnableControl();
    portTalon->Set(RobotMap::ALL_STOP);

    starboardTalon->SetControlMode(CANSpeedController::kPercentVbus);
    starboardTalon->EnableControl();
    starboardTalon->Set(RobotMap::ALL_STOP);
}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new OperatorInputDriveTrain());
}

/********* BEGIN METHODS CALLED BY COMMANDS **********/
void DriveTrain::controllerInputToSteamEngine(double speedPort, double speedStarboard){
	printf("DriveTrain - Left: %f\tRight: %f\n", speedPort, speedStarboard);
	steamEngineRobotDrive->TankDrive(speedPort, speedStarboard);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

