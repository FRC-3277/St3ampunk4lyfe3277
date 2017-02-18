#include "OperatorInputBallPicker.h"

OperatorInputBallPicker::OperatorInputBallPicker() {
	Requires(Robot::ballPicker.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void OperatorInputBallPicker::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputBallPicker::Execute() {

	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::ballPicker->FuelRiserBeltOn();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputBallPicker::IsFinished() {

	bool completedPicking = false;

	if(Robot::oi->getXBoxControllerDriver()->GetRawButton(TOGGLE_STATUS_PICKA) == false)
	{
		completedPicking = true;
	}


	return completedPicking;
}

// Called once after isFinished returns true
void OperatorInputBallPicker::End() {
	Robot::ballPicker->FuelRiserBeltOff();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputBallPicker::Interrupted() {

}
