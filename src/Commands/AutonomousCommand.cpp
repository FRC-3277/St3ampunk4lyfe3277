#include "AutonomousCommand.h"


AutonomousCommand::AutonomousCommand(): Command() {
	Requires(Robot::driveTrain.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
//TODO: Currently the position isn't resetting correctly. We must increase the number... I'm not sure why the ENC POS won't reset
//In order to chain the drivetrain commands, continue to add to the tickGoals. Hopefully we can change that
void AutonomousCommand::Initialize() {
	Robot::driveTrain->SetStartTime();
	hasRun = false;
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
	if(DriverStation::GetInstance().IsAutonomous() &&
			hasRun == false)
	{
		hasRun = true;

		int _90DegreeTurn = 1000;
		int OneRevolutionOfTheWheel = 848;
		int ColorRed = 1;
		int ColorBlue = 0;

		autoCommand = Robot::driveTrain->GetDashboard();
		shooterSpeed = Robot::shooter->GetShootaStartingSpeed();
		ResetPositions();
		//TODO: Add regressive functionality
		//Red team shoot and hopper
		if(autoCommand == 1)
		{
			AutonomousShoota(ColorRed);
			AutonomousAuger();
			AutonomousReload(7);
			AutonomousAugerStop();
			Robot::driveTrain->SetStartTime();
			AutonomousReload(2);
			AutonomousAuger();
		}
		//Red team shoot and gear
		else if(autoCommand == 2)
		{
			AutonomousTurnRight(_90DegreeTurn);
			AutonomousShoota(ColorRed);
			AutonomousAuger();
			AutonomousReload(5);
			AutonomousAugerStop();
			AutonomousTurnLeft(_90DegreeTurn+_90DegreeTurn);
			AutonomousMoveForward(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel);
			AutonomousTurnRight(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+(_90DegreeTurn*1.5));
			AutonomousMoveBackwards(_90DegreeTurn+_90DegreeTurn+OneRevolutionOfTheWheel+(_90DegreeTurn*1.5)+OneRevolutionOfTheWheel);
		}
		//Red team gear and shoot
		else if(autoCommand == 3)
		{
			AutonomousMoveBackwards(2000);
			AutonomousReload(5);
			AutonomousMoveForward(1000);
			AutonomousTurnLeft(1000);
			AutonomousMoveForward(2000);
			AutonomousTurnRight(500);
			AutonomousShoota(ColorRed);
			AutonomousAuger();
		}
		//Blue team shoot and hopper
		else if(autoCommand == 4)
		{
			AutonomousShoota(ColorBlue);
			AutonomousAuger();
			AutonomousReload(7);
			AutonomousAugerStop();
			Robot::driveTrain->SetStartTime();
			AutonomousReload(2);
			AutonomousAuger();
		}
		//Blue team shoot and gear
		else if(autoCommand == 5)
		{
			AutonomousTurnLeft(_90DegreeTurn);
			AutonomousShoota(ColorBlue);
			AutonomousAuger();
			AutonomousReload(5);
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
			AutonomousReload(5);
			AutonomousMoveForward(OneRevolutionOfTheWheel+OneRevolutionOfTheWheel);
			AutonomousTurnRight(OneRevolutionOfTheWheel+OneRevolutionOfTheWheel+(_90DegreeTurn*.75));
			AutonomousShoota(ColorBlue);
			AutonomousAuger();
		}
		//Testing autocommands
		else if(autoCommand == 7)
		{
			AutonomousShoota(ColorRed);
			AutonomousAuger();
			AutonomousReload(7);
			AutonomousAugerStop();
			Robot::driveTrain->SetStartTime();
			AutonomousReload(2);
			AutonomousAuger();
		}
		stopAuto = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousCommand::IsFinished() {
	return stopAuto;
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
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < tickGoal)
	{
		Robot::driveTrain->SetTalonForward();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
		if(DriverStation::GetInstance().IsOperatorControl())
		{
			break;
		}
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
		if(DriverStation::GetInstance().IsOperatorControl())
		{
			break;
		}
	}
	Robot::driveTrain->SetTalonStop();
}

void AutonomousCommand::AutonomousTurnRight(double turnGoal){
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < turnGoal)
	{
		Robot::driveTrain->TurnRight();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
		if(DriverStation::GetInstance().IsOperatorControl())
		{
			break;
		}
	}
	Robot::driveTrain->SetTalonStop();
}

void AutonomousCommand::AutonomousTurnLeft(double turnGoal){
	double encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());

	while(encoderPositionStarboard < turnGoal)
	{
		Robot::driveTrain->TurnLeft();
		encoderPositionStarboard = (Robot::driveTrain->GetStarboardTalonEncoderPosition());
		if(DriverStation::GetInstance().IsOperatorControl())
		{
			break;
		}
	}
	Robot::driveTrain->SetTalonStop();
}

void AutonomousCommand::ResetPositions(){
	Robot::driveTrain->SetTalonStartPosition();
}

void AutonomousCommand::AutonomousShoota(int Color){
		double visionSuggestedSpeed = shooterSpeed;
		//TODO: Get feedback from vision computer and adjust the speed.
		//This does nothing right now obviously... Needs the return from vision.
		visionSuggestedSpeed = visionSuggestedSpeed*1;
		Robot::shooter->SetShooterSpeed(visionSuggestedSpeed);

		//TODO: Get the current speed of the motor from the encoder and adjust.
		shooterSpeed = Robot::shooter->GetAutonomousShootaStartingSpeed();

		Robot::shooter->AutonomousSpeedControlShooter(shooterSpeed, Color);
}

void AutonomousCommand::AutonomousAuger(){
	Robot::auger->AutonomousAugerAllShesGotCaptain();
}

void AutonomousCommand::AutonomousAugerStop(){
	Robot::auger->AugerStopScotty();
}

void AutonomousCommand::AutonomousReload(double timeDelay){
	Robot::driveTrain->DelayUntilEmpty(timeDelay);
}
