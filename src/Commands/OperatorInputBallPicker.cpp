#include "OperatorInputBallPicker.h"

OperatorInputBallPicker::OperatorInputBallPicker() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::ballPicker.get());
	printf("CONSTRUCTOR");
}

// Called just before this Command runs the first time
void OperatorInputBallPicker::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputBallPicker::Execute() {

	if(Robot::ballPicker->GetButtonState() == false)
	{
		Robot::ballPicker->SetButtonState(true);
		printf("BallPicker\n");
	}
	else
	{
		Robot::ballPicker->SetButtonState(false);
	}

	if(DriverStation::GetInstance().IsOperatorControl() &&
			Robot::ballPicker->GetButtonState())
	{
		Robot::ballPicker->FuelRiserBeltOn();
	}

	if(DriverStation::GetInstance().IsOperatorControl() &&
				Robot::ballPicker->GetButtonState())
		{
			Robot::ballPicker->FuelRiserBeltOff();
		}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputBallPicker::IsFinished() {

	return false;
}

// Called once after isFinished returns true
void OperatorInputBallPicker::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputBallPicker::Interrupted() {

}
