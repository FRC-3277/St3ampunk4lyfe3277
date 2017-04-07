#include "OperatorInputAgitator.h"

OperatorInputAgitator::OperatorInputAgitator() {
	Requires(Robot::auger.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void OperatorInputAgitator::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputAgitator::Execute() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::agitator->AgitatorAllShesGot();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputAgitator::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorInputAgitator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputAgitator::Interrupted() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::agitator->AgitatorFullStop();
	}
}
