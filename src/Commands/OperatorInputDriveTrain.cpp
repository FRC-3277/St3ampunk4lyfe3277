#include "OperatorInputDriveTrain.h"

OperatorInputDriveTrain::OperatorInputDriveTrain() {
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void OperatorInputDriveTrain::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputDriveTrain::Execute() {
	if(DriverStation::GetInstance().IsOperatorControl()){
		double
			yPosPort = Robot::oi->getXBoxControllerDriver()->GetRawAxis(PORT_PROPELLER),
			yPosStarboard = Robot::oi->getXBoxControllerDriver()->GetRawAxis(STARBOARD_PROPELLER),
			posAllAheadFlank = Robot::oi->getXBoxControllerDriver()->GetRawAxis(ALL_AHEAD_FLANK),
			posFullAstern = Robot::oi->getXBoxControllerDriver()->GetRawAxis(FULL_ASTERN);

		if(posAllAheadFlank >= posFullAstern)
		{
			//If the trigger value exceeds either of the joystick values then it will supersede.
			if(posAllAheadFlank > abs(yPosPort) || posAllAheadFlank > abs(yPosStarboard))
			{
				yPosPort = posAllAheadFlank;
				yPosStarboard = posAllAheadFlank;
			}
		}
		else
		{
			//If the trigger value exceeds either of the joystick values then it will supersede.
			if(posFullAstern > abs(yPosPort) || posFullAstern > abs(yPosStarboard))
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
