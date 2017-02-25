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
	//775 is about a 90 degree turn ; 848 is about 1 revolution of the wheel

	int _90DegreeTurn = 775;
	int OneRevolutionOfTheWheel = 848;

	autoCommand = Robot::driveTrain->GetDashboard();
	shooterSpeed = Robot::shooter->GetShootaStartingSpeed();
	//Red team shoot and hopper
	if(autoCommand == 1)
	{
		startShooting = true;
		AutonomousTurnLeft(_90DegreeTurn);
		AutonomousAuger();
		//Add when it should continue
		AutonomousTurnRight(_90DegreeTurn*2);
	}
	//Red team shoot and gear
	else if(autoCommand == 2)
	{
		startShooting = true;
		AutonomousMoveForward(OneRevolutionOfTheWheel);
		AutonomousTurnRight(_90DegreeTurn*2);
		AutonomousAuger();
		AutonomousMoveForward(OneRevolutionOfTheWheel);

	}
	//Red team gear and shoot
	else if(autoCommand == 3)
	{

	}
	//Blue team shoot and hopper
	else if(autoCommand == 4)
	{
		startShooting = true;
		AutonomousMoveForward(OneRevolutionOfTheWheel);
		AutonomousAuger();
	}
	//Blue team shoot and gear
	else if(autoCommand == 5)
	{

	}
	//Blue team gear and shoot
	else if(autoCommand == 6)
	{

	}
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
	if (startShooting)
	{
		AutonomousShoota();
	}
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
	AutonomousAugerStop();
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

void AutonomousCommand::AutonomousAugerStop(){
	Robot::auger->AugerStopScotty();
}
