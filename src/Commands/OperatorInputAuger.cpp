#include "OperatorInputAuger.h"

OperatorInputAuger::OperatorInputAuger(int argDirection) {
	Requires(Robot::auger.get());
	lumberJack.reset(new LumberJack());
	pdp.reset(new PowerDistributionPanel(RobotMap::POWER_DISTRIBUTION_PANEL_DEVICE_ID));
	direction = argDirection;
}

// Called just before this Command runs the first time
void OperatorInputAuger::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputAuger::Execute() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		double current;
		if(direction == 1)
		{
			Robot::auger->AugerCleanAndSweepReverse();
		}
		else if(direction == 0)
		{
			Robot::auger->AugerAllShesGotCaptain();
		}

		current = pdp->GetCurrent(7);
		lumberJack->dashLogNumber("Current:", current);
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
