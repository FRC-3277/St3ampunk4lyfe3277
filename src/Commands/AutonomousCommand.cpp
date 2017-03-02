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
	ResetPositions();
	//TODO: Add regressive functionality
	//Red team shoot and hopper
	if(autoCommand == 1)
	{
		AutonomousTurnRight(_90DegreeTurn);
		AutonomousShoota();
		AutonomousAuger();
		AutonomousDelayUntilEmpty();
		AutonomousAugerStop();
		AutonomousTurnLeft(_90DegreeTurn+_90DegreeTurn);
		AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel);
		AutonomousTurnRight(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+_90DegreeTurn);
		AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+_90DegreeTurn+OneRevolutionOfTheWheel);
	}
	//Red team shoot and gear
	else if(autoCommand == 2)
	{
		AutonomousTurnRight(_90DegreeTurn);
		AutonomousShoota();
		AutonomousAuger();
		AutonomousDelayUntilEmpty();
		AutonomousAugerStop();
		AutonomousTurnLeft(_90DegreeTurn+_90DegreeTurn);
		AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel);
		AutonomousTurnRight(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+(_90DegreeTurn*1.5));
		AutonomousMoveBackwards(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+(_90DegreeTurn*1.5)+OneRevolutionOfTheWheel);
	}
	//Red team gear and shoot
	else if(autoCommand == 3)
	{
		AutonomousMoveBackwards(OneRevolutionOfTheWheel);
		AutonomousDelayForGear();
		AutonomousMoveForward(OneRevolutionOfTheWheel+OneRevolutionOfTheWheel);
		AutonomousTurnLeft(OneRevolutionOfTheWheel+OneRevolutionOfTheWheel+(_90DegreeTurn*.75));
		AutonomousAuger();
		AutonomousShoota();
	}
	//Blue team shoot and hopper
	else if(autoCommand == 4)
	{
		AutonomousTurnLeft(_90DegreeTurn);
		AutonomousShoota();
		AutonomousAuger();
		AutonomousDelayUntilEmpty();
		AutonomousAugerStop();
		AutonomousTurnRight(_90DegreeTurn+_90DegreeTurn);
		AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel);
		AutonomousTurnLeft(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+_90DegreeTurn);
		AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+_90DegreeTurn+OneRevolutionOfTheWheel);
	}
	//Blue team shoot and gear
	else if(autoCommand == 5)
	{
		AutonomousTurnLeft(_90DegreeTurn);
		AutonomousShoota();
		AutonomousAuger();
		AutonomousDelayUntilEmpty();
		AutonomousAugerStop();
		AutonomousTurnRight(_90DegreeTurn+_90DegreeTurn);
		AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel);
		AutonomousTurnLeft(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+(_90DegreeTurn*1.5));
		AutonomousMoveBackwards(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+(_90DegreeTurn*1.5)+OneRevolutionOfTheWheel);
	}
	//Blue team gear and shoot
	else if(autoCommand == 6)
	{
		AutonomousMoveBackwards(OneRevolutionOfTheWheel);
		AutonomousDelayForGear();
		AutonomousMoveForward(OneRevolutionOfTheWheel+OneRevolutionOfTheWheel);
		AutonomousTurnRight(OneRevolutionOfTheWheel+OneRevolutionOfTheWheel+(_90DegreeTurn*.75));
		AutonomousShoota();
		AutonomousAuger();
	}
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
//	if (startShooting)
//	{
//		AutonomousShoota();
//	}
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
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < tickGoal)
	{
		Robot::driveTrain->SetTalonForward();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
}

void AutonomousCommand::AutonomousMoveBackwards(double tickGoal)
{
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < tickGoal)
	{
		Robot::driveTrain->SetTalonBackwards();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
}

void AutonomousCommand::AutonomousTurnRight(double turnGoal){
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < turnGoal)
	{
		Robot::driveTrain->TurnRight();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
}

void AutonomousCommand::AutonomousTurnLeft(double turnGoal){
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < turnGoal)
	{
		Robot::driveTrain->TurnLeft();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
	}
	Robot::driveTrain->SetTalonStop();
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

void AutonomousCommand::AutonomousDelayUntilEmpty(){
	Robot::driveTrain->DelayUntilEmpty();
}

void AutonomousCommand::AutonomousDelayForGear(){
	Robot::driveTrain->DelayForGear();
}
