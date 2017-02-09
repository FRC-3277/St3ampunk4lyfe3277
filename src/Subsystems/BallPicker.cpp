#include "CANTalon.h"
#include "CANSpeedController.h"
#include "BallPicker.h"
#include "../RobotMap.h"


BallPicker::BallPicker() : Subsystem("BallPicker") {
	pickerTalon = RobotMap::pickerTalon;

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


