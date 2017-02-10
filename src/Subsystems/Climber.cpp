#include "CANTalon.h"
#include "CANSpeedController.h"

#include "Climber.h"
#include "../Commands/OperatorInputClimber.h"


Climber::Climber() : Subsystem("Climber") {
	climberTalon = RobotMap::climberTalon;

	//Encoder
	climberTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
	climberTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
	climberTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
	climberTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
	climberTalon->SetIzone(TALON_IZONE);
	climberTalon->SetCloseLoopRampRate(TALON_MAXRAMP);

	//Everything else
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
