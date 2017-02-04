// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"
#include "CANSpeedController.h"

#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/OperatorInputDriveTrain.h"


DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    portTalon = RobotMap::driveTrainPortTalon;
    starboardTalon = RobotMap::driveTrainStarboardTalon;
    steamEngineRobotDrive = RobotMap::driveTrainSteamEngineRobotDrive;

    portTalon.get()->SetControlMode(CANSpeedController::kPercentVbus);
    portTalon.get()->EnableControl();
    portTalon.get()->Set(0.0f);

    starboardTalon.get()->SetControlMode(CANSpeedController::kPercentVbus);
    starboardTalon.get()->EnableControl();
    starboardTalon.get()->Set(0.0f);
}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new OperatorInputDriveTrain());
}

/********* BEGIN METHODS CALLED BY COMMANDS **********/
void DriveTrain::controllerInputToSteamEngine(double speedPort, double speedStarboard){
	printf("DriveTrain - Left: %f\tRight: %f\n", speedPort, speedStarboard);
	steamEngineRobotDrive.get()->TankDrive(speedPort, speedStarboard);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

