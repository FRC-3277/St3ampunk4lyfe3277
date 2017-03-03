#include "OperatorInputClimber.h"

OperatorInputClimber::OperatorInputClimber() {
	Requires(Robot::climber.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void OperatorInputClimber::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputClimber::Execute() {
	//The button was pressed which got us here so just enable the climber.
	if(DriverStation::GetInstance().IsOperatorControl())
	{
//	{
//		if(RobotMap::ALTERNATE_CONTROLLER_ENABLED)
//		{
//			if(Robot::oi->getXBoxControllerAlternate()->GetRawButton(TOGGLE_CLIMBER_DOWN) == true)
//			{
//				Robot::climber->climberEngineDescend();
//			}
//			else
//			{
//				Robot::climber->climberEngineAscend();
//			}
//		}
//		else
//		{
			Robot::climber->climberEngineAscend();
//		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputClimber::IsFinished()
{
//Commented out due to them wanting this to become a toggle. If it needs to be switched back to a hold, this can be used.

	bool completedClimbing = false;

	if(RobotMap::ALTERNATE_CONTROLLER_ENABLED)
	{
		if(Robot::oi->getXBoxControllerAlternate()->GetRawButton(TOGGLE_CLIMBER_DOWN) == false &&
				Robot::oi->getXBoxControllerDriver()->GetRawButton(TOGGLE_CLIMBER_UP) == false)
		{
			//The button is released so disable the climber
			completedClimbing = true;
		}
	}
	else
	{
		if(Robot::oi->getXBoxControllerDriver()->GetRawButton(TOGGLE_CLIMBER_UP) == false)
		{
			completedClimbing = true;
		}
	}

	return completedClimbing;
}

// Called once after isFinished returns true
void OperatorInputClimber::End() {
	Robot::climber->climberEngineStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputClimber::Interrupted() {
//	if(DriverStation::GetInstance().IsOperatorControl())
//		{
//			Robot::climber->climberEngineStop();
//		}
}
