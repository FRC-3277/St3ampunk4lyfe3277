#include "CANTalon.h"
#include "CANSpeedController.h"
#include "BallPicker.h"
#include "../RobotMap.h"


BallPicker::BallPicker() : Subsystem("BallPicker") {
	pickerTalon = RobotMap::pickerTalon;
	lumberJack.reset(new LumberJack());

	//Encoder
	pickerTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
	pickerTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
	pickerTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
	pickerTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
	pickerTalon->SetIzone(TALON_IZONE);
	pickerTalon->SetCloseLoopRampRate(TALON_MAXRAMP);

	//Everything else
	pickerTalon->SetControlMode(CANSpeedController::kPercentVbus);
	pickerTalon->EnableControl();
	pickerTalon->SetInverted(true);
	pickerTalon->Set(RobotMap::ALL_STOP);

}

void BallPicker::InitDefaultCommand() {
}

void BallPicker::FuelRiserBeltOn()
{
	pickerTalon->Set(RobotMap::BALL_PICKA_SPEED);

}

void BallPicker::FuelRiserBeltOff()
{
	pickerTalon->Set(RobotMap::ALL_STOP);
}


