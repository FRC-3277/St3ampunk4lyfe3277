#include "OperatorInputAuger.h"

OperatorInputAuger::OperatorInputAuger() {
	Requires(Robot::auger.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void OperatorInputAuger::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputAuger::Execute() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		if(Robot::oi->getXBoxControllerAlternate()->GetRawButton(TOGGLE_STATUS_AUGER_REVERSE) == true)
		{
			Robot::auger->AugerCleanAndSweepReverse();
		}
		else
		{
			Robot::auger->AugerForwardAndReverse();
		}
	}
}


// Make this return true when this Command no longer needs to run execute()
bool OperatorInputAuger::IsFinished() {

	return false;
}

// Called once after isFinished returns true
void OperatorInputAuger::End() {


}

void OperatorInputAuger::Interrupted() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::auger->AugerStopScotty();
	}
}
