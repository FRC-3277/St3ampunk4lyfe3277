#include "CANTalon.h"
#include "CANSpeedController.h"
#include "BallPicker.h"
#include "../RobotMap.h"


BallPicker::BallPicker() : Subsystem("BallPicker") {
	pickerTalon = RobotMap::pickerTalon;

	pickerTalon->SetControlMode(CANSpeedController::kPercentVbus);
	pickerTalon->EnableControl();
	pickerTalon->SetInverted(true);
	pickerTalon->Set(0.0f);

}

void BallPicker::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new OperatorInputBallPicker());
}

void BallPicker::FuelRiserBeltOn()
{
	pickerTalon->Set(0.5);

}

void BallPicker::FuelRiserBeltOff()
{
	pickerTalon->Set(0.0);
}


