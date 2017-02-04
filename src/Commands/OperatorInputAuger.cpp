#include "OperatorInputAuger.h"

OperatorInputAuger::OperatorInputAuger() {
	Requires(Robot::auger.get());
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void OperatorInputAuger::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputAuger::Execute() {
//	if(Robot::auger->GetButtonState() == false)
//	{
//		Robot::auger->SetButtonState(true);
//	}
//	else
//	{
//		Robot::auger->SetButtonState(false);
//	}

	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::auger->RivetOn();
	}
}


// Make this return true when this Command no longer needs to run execute()
bool OperatorInputAuger::IsFinished() {

	return false;
}

// Called once after isFinished returns true
void OperatorInputAuger::End() {


}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputAuger::Interrupted() {
	if(DriverStation::GetInstance().IsOperatorControl())
	{
		Robot::auger->RivetOff();
	}
}
