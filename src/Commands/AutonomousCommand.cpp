#include "AutonomousCommand.h"


AutonomousCommand::AutonomousCommand(): Command() {
	Requires(Robot::driveTrain.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
//TODO: Currently the position isn't resetting correctly. We must increase the number... I'm not sure why the ENC POS won't reset
void AutonomousCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousCommand::IsFinished() {
    return false;
}

// Called once after IsFinished returns true
void AutonomousCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousCommand::Interrupted() {

}

//Every 848 ticks is one full rotation of the wheel. It will move 6 Pi in distance for each rotation
void AutonomousCommand::AutonomousMoveForward(double tickGoal){
	Robot::driveTrain->SetTalonStartPosition();
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < tickGoal)
	{
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
		Robot::driveTrain->SetTalonForward();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::AutonomousMoveBackwards(double tickGoal)
{
	Robot::driveTrain->SetTalonStartPosition();
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < tickGoal)
	{
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
		Robot::driveTrain->SetTalonBackwards();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::AutonomousTurnRight(double turnGoal){
	Robot::driveTrain->SetTalonStartPosition();
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < turnGoal)
	{
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
		Robot::driveTrain->TurnRight();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::ResetPositions(){
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::AutonomousShoota(){

}

void AutonomousCommand::AutonomousAuger(){
	Robot::auger->AugerAllShesGotCaptain();
}
