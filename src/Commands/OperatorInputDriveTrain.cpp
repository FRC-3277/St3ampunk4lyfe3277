#include "OperatorInputDriveTrain.h"
#include <algorithm>

OperatorInputDriveTrain::OperatorInputDriveTrain() {
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void OperatorInputDriveTrain::Initialize() {
	//TODO: It was noticed that when driving forward the motors don't achieve 100% maximum .999 or so value.  We need to add
	//a multiplier

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputDriveTrain::Execute() {
	if(DriverStation::GetInstance().IsOperatorControl()){
		double
			yPosPort = Robot::oi->getXBoxControllerDriver()->GetRawAxis(PORT_PROPELLER),
			yPosStarboard = Robot::oi->getXBoxControllerDriver()->GetRawAxis(STARBOARD_PROPELLER),
			//Needs to be the inverse
			posAllAheadFlank = Robot::oi->getXBoxControllerDriver()->GetRawAxis(ALL_AHEAD_FLANK)*-1,
			posFullAstern = Robot::oi->getXBoxControllerDriver()->GetRawAxis(FULL_ASTERN);

		//printf ("All Ahead: %f  Full Astern: %f\n", posAllAheadFlank, posFullAstern);

		//Prevent the Vanelllope effect
		yPosPort = Clamp(yPosPort);
		yPosStarboard = Clamp(yPosStarboard);
		//posAllAheadFlank = Clamp(posAllAheadFlank);
		//posFullAstern = Clamp(posFullAstern);

		//printf("Flank: %f Astern: %f\n", abs(posAllAheadFlank), abs(posFullAstern));
		if(fabs(posAllAheadFlank) >= (posFullAstern))
		{
			//If the trigger value exceeds either of the joystick values then it will supersede.
			if(fabs(posAllAheadFlank) > fabs(yPosPort) || fabs(posAllAheadFlank) > fabs(yPosStarboard))
			{
				yPosPort = posAllAheadFlank;
				yPosStarboard = posAllAheadFlank;
			}
		}
		else
		{
			//If the trigger value exceeds either of the joystick values then it will supersede.
			if(posFullAstern > fabs(yPosPort) || posFullAstern > fabs(yPosStarboard))
			{
				yPosPort = posFullAstern;
				yPosStarboard = posFullAstern;
			}
		}
		Robot::driveTrain.get()->controllerInputToSteamEngine(yPosPort, yPosStarboard);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputDriveTrain::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorInputDriveTrain::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputDriveTrain::Interrupted() {

}

double OperatorInputDriveTrain::Clamp(double joystickRawAxis)
{
	if(joystickRawAxis <= -1)
	{
		joystickRawAxis = -0.999;
	}
	else if(joystickRawAxis >= 1)
	{
		joystickRawAxis = 0.999;
	}

	return joystickRawAxis;
}

