#include "OperatorInputShooter.h"
/*
The shooter is enabled manually by the operator.  This enables
both the shooter motor and also the vision tracking feedback helper
functions which positions the robot and sets the speed of the
motor.
*/
OperatorInputShooter::OperatorInputShooter() {
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void OperatorInputShooter::Initialize() {
	//Begin with this speed and go from there
	shooterSpeed = RobotMap::SHOOTA_STARTING_SPEED;
}

// Called repeatedly when this Command is scheduled to run
void OperatorInputShooter::Execute() {
	double visionSuggestedSpeed = shooterSpeed;
	//TODO: Get feedback from vision computer and adjust the speed.
	//This does nothing right now obviously... Needs the return from vision.
	visionSuggestedSpeed = visionSuggestedSpeed*1;
	Robot::shooter->SetShooterSpeed(visionSuggestedSpeed);

	//TODO: Get the current speed of the motor from the encoder and adjust.
	shooterSpeed = Robot::shooter->GetShooterSpeed();

	Robot::shooter->SpeedControlShooter(shooterSpeed);

}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputShooter::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorInputShooter::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputShooter::Interrupted() {
	Robot::shooter->SpeedControlShooter(RobotMap::STOP_SPEED);
}
