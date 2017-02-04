#include "OperatorInputClimber.h"

OperatorInputClimber::OperatorInputClimber() {
	Requires(Robot::climber.get());
}

// Called just before this Command runs the first time
void OperatorInputClimber::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputClimber::Execute() {
	printf("Climber\n");
	//The button was pressed which got us here so just enable the climber.
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::climber->climberEngineAscend();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputClimber::IsFinished() {
	//The button is released so disable the climber
	if(Robot::oi->getXBoxControllerAlternate()->GetRawButton(TOGGLE_CLIMBER)==false &&
	   DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::climber->climberEngineStop();
	}
	return false;
}

// Called once after isFinished returns true
void OperatorInputClimber::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputClimber::Interrupted() {

}
