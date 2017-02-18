#include "AutonomousDriveForward.h", 0

void AutonomousDriveForward::AutonomousDriveForward() {
	 Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void AutonomousDriveForward::Initialize() {

	StarboardRevolutions = 0;
	PortRevolutions = 0;
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveForward::Execute() {

	Robot::driveTrain.get()->controllerInputToSteamEngine(-0.5, -0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveForward::IsFinished() {
	bool needToStop = false;

	if (StarboardRevolutions = 50 && PortRevolutions = 50)
	{
		needToStop = true;
	}

	return needToStop;

}

// Called once after isFinished returns true
void AutonomousDriveForward::End() {

	Robot::driveTrain.get()->controllerInputToSteamEngine(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveForward::Interrupted() {

}
