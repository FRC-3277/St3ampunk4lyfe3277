#include "CANTalon.h"
#include "CANSpeedController.h"

#include "Climber.h"
#include "../Commands/OperatorInputClimber.h"


Climber::Climber() : Subsystem("Climber") {
	climberTalon = RobotMap::climberTalon;

	climberTalon->SetControlMode(CANSpeedController::kPercentVbus);
	climberTalon->EnableControl();
	climberTalon->Set(RobotMap::ALL_STOP);
}

void Climber::InitDefaultCommand() {
	//SetDefaultCommand(new OperatorInputClimber());
}

/********* BEGIN METHODS CALLED BY COMMANDS **********/
void Climber::climberEngineAscend(){
	double
		speedOfAscent = RobotMap::CLIMBER_SPEED;

	climberTalon->Set(speedOfAscent);
}

void Climber::climberEngineStop(){
	climberTalon->Set(RobotMap::ALL_STOP);
}
