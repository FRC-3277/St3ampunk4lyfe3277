#include "OperatorInputClimber.h"

OperatorInputClimber::OperatorInputClimber() {
	Requires(Robot::climber.get());
}

// Called just before this Command runs the first time
void OperatorInputClimber::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputClimber::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputClimber::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorInputClimber::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputClimber::Interrupted() {

}
