#include "AutonomousCommand.h"


AutonomousCommand::AutonomousCommand(): Command() {
	Requires(Robot::driveTrain.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void AutonomousCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousCommand::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void AutonomousCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousCommand::Interrupted() {

}

void AutonomousCommand::AutonomousMoveForward(){
	Robot::driveTrain->SetTalonStart();
	double encoderPositionStarboard = fabs(starboardTalon->GetEncPosition());
	double tickGoal = (848);

	while(encoderPositionStarboard < tickGoal)
	{
		encoderPositionStarboard = fabs(starboardTalon->GetEncPosition());
		portTalon->Set(-0.1);
		starboardTalon->Set(0.1);
	}

	portTalon->Set(0.0);
	starboardTalon->Set(0.0);
}
