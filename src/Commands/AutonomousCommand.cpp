#include "AutonomousCommand.h"


AutonomousCommand::AutonomousCommand(): Command() {
	Requires(Robot::driveTrain.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
//TODO: Currently the position isn't resetting correctly. We must increase the number... I'm not sure why the ENC POS won't reset
//In order to chain the drivetrain commands, continue to add to the tickGoals. Hopefully we can change that
void AutonomousCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
	if(DriverStation::GetInstance().IsAutonomous())
	{
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
	//		AutonomousDelayUntilEmpty();
	//		AutonomousAugerStop();
			lumberJack->dLog("ENC POSITION 1 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousMoveBackwards(500);
			lumberJack->dLog("ENC POSITION 2 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousTurnLeft(900);
			lumberJack->dLog("ENC POSITION 3 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousMoveForward(3300);
			lumberJack->dLog("ENC POSITION 4 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousTurnRight(5000);
	//		AutonomousMoveForward(7000);
			lumberJack->dLog("ENC POSITION 5 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
		}
		//Red team shoot and gear
		else if(autoCommand == 2)
		{
			AutonomousTurnRight(_90DegreeTurn);
			AutonomousShoota(ColorRed);
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
			AutonomousMoveBackwards(2000);
			AutonomousDelayForGear();
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
	//		AutonomousDelayUntilEmpty();
	//		AutonomousAugerStop();
	//		AutonomousMoveBackwards(700);
			lumberJack->dLog("ENC POSITION 1 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousTurnRight(2000);
			lumberJack->dLog("ENC POSITION 2 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousMoveForward(3500);
			lumberJack->dLog("ENC POSITION 3 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousTurnLeft(1000);
			lumberJack->dLog("ENC POSITION 4 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
	//		AutonomousMoveForward(2000);
			lumberJack->dLog("ENC POSITION 5 " +to_string(Robot::driveTrain->GetStarboardTalonEncoderPosition()));
		}
		//Blue team shoot and gear
		else if(autoCommand == 5)
		{
			AutonomousTurnLeft(_90DegreeTurn);
			AutonomousShoota(ColorBlue);
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
			AutonomousShoota(ColorBlue);
			AutonomousAuger();
		}
		//Testing autocommands
		else if(autoCommand == 7)
		{
			//AutonomousTurnLeft(865);

			//AutonomousTurnRight(lastAutonomousValue+500);
	//		AutonomousTurnLeft(lastAutonomousValue+775);
	//		AutonomousTurnRight(lastAutonomousValue+775);
	//		AutonomousTurnLeft(lastAutonomousValue+1000);
	//		AutonomousTurnRight(lastAutonomousValue+1000);
			AutonomousMoveForward(1000);
	//		AutonomousMoveForward(lastAutonomousValue+1000);
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
		shooterSpeed = Robot::shooter->GetShooterSpeed();

		Robot::shooter->AutonomousSpeedControlShooter(shooterSpeed, Color);
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
