#include "OperatorInputAuger.h"

OperatorInputAuger::OperatorInputAuger(int argDirection) {
	Requires(Robot::auger.get());
	lumberJack.reset(new LumberJack());
	direction = argDirection;
}

// Called just before this Command runs the first time
void OperatorInputAuger::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputAuger::Execute() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		if(direction == 1)
		{
			Robot::auger->AugerCleanAndSweepReverse();
		}
		else if(direction == 0)
		{
			AugerShooterDelay();
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

void OperatorInputAuger::AugerShooterDelay() {
	if (delayAugerForShooter)
	{
		nowVelocity = Robot::shooter->GetShootaVelocity();
		previousVelocity = Robot::shooter->GetShootaVelocity();
		delayAugerForShooter = false;
	}
	else
	{
		nowVelocity = Robot::shooter->GetShootaVelocity();
		delayAugerForShooter = true;
	}

	if(previousVelocity > nowVelocity &&
			nowVelocity > Robot::shooter->GetShootaDesiredSpeed())
	{
		Robot::auger->AugerStopScotty();
		lumberJack->dLog("IT WORKED");
	}
	else
	{
		Robot::auger->AugerAllShesGotCaptain();
	}
	lumberJack->dashLogNumber("Previous Velocity", previousVelocity);
	lumberJack->dashLogNumber("Now Velocity", nowVelocity);
}
