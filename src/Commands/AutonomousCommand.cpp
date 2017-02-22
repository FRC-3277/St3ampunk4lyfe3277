#include "AutonomousCommand.h"


AutonomousCommand::AutonomousCommand(): Command() {
	Requires(Robot::driveTrain.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
//TODO: Currently the position isn't resetting correctly. We must increase the number... I'm not sure why the ENC POS won't reset
//In order to chain the drivetrain commands, continue to add to the tickGoals. Hopefully we can change that
void AutonomousCommand::Initialize() {
	//This is possibly needed. I was rushed to get the shooter running in auto so there may be a more elegant way
	shooterSpeed = Robot::shooter->GetShootaStartingSpeed();
	//AutonomousTurnRight(775);
	//AutonomousMoveForward(1623);
	//AutonomousAuger();

}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
	AutonomousShoota();
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
	shooterSpeed = 0;
	Robot::shooter->SpeedControlShooter(shooterSpeed);
}

//Every 848 ticks is one full rotation of the wheel. It will move 6 Pi in distance for each rotation
void AutonomousCommand::AutonomousMoveForward(double tickGoal){
	Robot::driveTrain->SetTalonStartPosition();
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < tickGoal)
	{
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
		Robot::driveTrain->TurnRight();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::AutonomousTurnLeft(double turnGoal){
	Robot::driveTrain->SetTalonStartPosition();
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < turnGoal)
	{
		Robot::driveTrain->TurnLeft();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::ResetPositions(){
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::AutonomousShoota(){
	if(RobotMap::SHOOTA_CALIBRATION_CONTROLLER_ENABLED)
	{
		/*
		 * This is strictly for use off the field and calibrating with a joystick controller with a slider.
		 */
		double desiredSpeed = 0;

		// Controller input is 0 - 1; Talon in speed mode expects RPM.
		desiredSpeed = fabs(Robot::oi->getLogitechExtreme()->GetRawAxis(SHOOTA_CALIBRATION_SLIDER) * Robot::shooter->GetShootaMaxCalibrationSpeed());
		Robot::shooter->SpeedControlShooter(desiredSpeed);
	}
	else
	{
		double visionSuggestedSpeed = shooterSpeed;
		//TODO: Get feedback from vision computer and adjust the speed.
		//This does nothing right now obviously... Needs the return from vision.
		visionSuggestedSpeed = visionSuggestedSpeed*1;
		Robot::shooter->SetShooterSpeed(visionSuggestedSpeed);

		//TODO: Get the current speed of the motor from the encoder and adjust.
		shooterSpeed = Robot::shooter->GetShooterSpeed();

		Robot::shooter->SpeedControlShooter(shooterSpeed);
	}
}

void AutonomousCommand::AutonomousAuger(){
	Robot::auger->AugerAllShesGotCaptain();
}
