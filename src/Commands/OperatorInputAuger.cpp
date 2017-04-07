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
		if(Robot::oi->getAirforceOne()->GetRawButton(REVERSE_AUGER) == true)
		{
			direction = 1;
		}
		else
		{
			direction = 0;
		}

		if(direction == 1)
		{
			Robot::auger->AugerCleanAndSweepReverse();
		}
		else if(direction == 0)
		{
			augerMinSpeed = augerBaseSpeed + (((Robot::oi->getAirforceOne()->GetRawAxis(AUGER_SPEED) * -1) + 1) * .425);
			augerMaxSpeed = augerMinSpeed + augerSpeedScale;
			//Robot::auger->AugerAllShesGotCaptain(augerMinSpeed + .1);
			Robot::auger->AugerWashingMachineWashingMachine(augerMaxSpeed, augerMinSpeed);
			shooterSpeed = Robot::shooter->GetShootaStartingSpeed();
			Robot::shooter->SpeedControlShooter(shooterSpeed);
			Robot::agitator->AgitatorAllShesGot();
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
		Robot::shooter->SpeedControlShooter(RobotMap::STOP_SPEED);
		Robot::agitator->AgitatorFullStop();
	}

}
