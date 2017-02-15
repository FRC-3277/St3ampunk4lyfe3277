#include "AutonomousDriveForward.h"

AutonomousDriveForward::AutonomousDriveForward() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

}

// Called just before this Command runs the first time
void AutonomousDriveForward::Initialize() {

	DriveTrain::portTalon->Set(0.0f);

	DriveTrain::starboardTalon->Set(0.0f);

}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveForward::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveForward::IsFinished() {

}

// Called once after isFinished returns true
void AutonomousDriveForward::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveForward::Interrupted() {

}
