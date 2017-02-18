#include "OperatorInputCameraSwitch.h"

OperatorInputCameraSwitch::OperatorInputCameraSwitch() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void OperatorInputCameraSwitch::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorInputCameraSwitch::Execute() {
	Robot::cameraSwap->SwapCameraView();
	Robot::cameraSwap->GetCamera();
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorInputCameraSwitch::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorInputCameraSwitch::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorInputCameraSwitch::Interrupted() {

}
