#include "CANTalon.h"
#include "CANSpeedController.h"

#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/OperatorInputDriveTrain.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    portTalon = RobotMap::driveTrainPortTalon;
    starboardTalon = RobotMap::driveTrainStarboardTalon;
    steamEngineRobotDrive = RobotMap::driveTrainSteamEngineRobotDrive;

    portTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    portTalon->SetControlMode(CANSpeedController::kPercentVbus);
    portTalon->EnableControl();
    portTalon->Set(RobotMap::ALL_STOP);

    starboardTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    starboardTalon->SetControlMode(CANSpeedController::kPercentVbus);
    starboardTalon->EnableControl();
    starboardTalon->Set(RobotMap::ALL_STOP);

    steamEngineRobotDrive->SetSafetyEnabled(false);
    steamEngineRobotDrive->SetExpiration(0.1);
    steamEngineRobotDrive->SetSensitivity(0.5);
    steamEngineRobotDrive->SetMaxOutput(1.0);
    steamEngineRobotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
    steamEngineRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new OperatorInputDriveTrain());
}

/********* BEGIN METHODS CALLED BY COMMANDS **********/
void DriveTrain::controllerInputToSteamEngine(double speedPort, double speedStarboard){
	printf("DriveTrain - Left: %f\tRight: %f\n", speedPort, speedStarboard);
	steamEngineRobotDrive->TankDrive(speedPort, speedStarboard);
}

