#include "OperatorInputShooter.h"

/*
The shooter is enabled manually by the operator.  This enables
both the shooter motor and also the vision tracking feedback helper
functions which positions the robot and sets the speed of the
motor.
*/
OperatorInputShooter::OperatorInputShooter() {
	Requires(Robot::shooter.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void OperatorInputShooter::Initialize() {
	//Begin with this speed and go from there
	shooterSpeed = Robot::shooter->GetShootaStartingSpeed();
	Robot::shooter->ZeroServoShooter();
	shooterServoPosition = Robot::shooter->GetCurrentServoPosition();
}

// Called repeatedly when this Command is scheduled to run
void OperatorInputShooter::Execute() {
	// Keep in sync
	shooterServoPosition = Robot::shooter->GetCurrentServoPosition();
	double desiredServoAngleAdjustment = Robot::oi->getLogitechExtreme()->GetY();
	// The allowed will be reflected on the desired.
	double allowedServoAngleAdjustment = 0.5;

	// Get more!
	if(fabs(desiredServoAngleAdjustment) > 0.3)
	{
		allowedServoAngleAdjustment = 2;
	}
	else if(fabs(desiredServoAngleAdjustment) > 0.6)
	{
		allowedServoAngleAdjustment = 4;
	}

	//TODO: Adjust this to match actual behavior.
	//TODO: Implement offline period to allow servo to adjust for requested postion based on angle calculated from spec sheet so the servo
	// is not overwhelmed with adjustments every 20 ms.  This may not be important if the WPILIB is handling this.  Testing will reveal!
	if(desiredServoAngleAdjustment > 0)
	{
		Robot::shooter->AdjustServoShooter(shooterServoPosition + allowedServoAngleAdjustment);
	}
	else if(desiredServoAngleAdjustment < 0)
	{
		Robot::shooter->AdjustServoShooter(shooterServoPosition - allowedServoAngleAdjustment);
	}

	if(Robot::oi->getLogitechExtreme()->GetRawButton(SHOOTA_ANGLA_ZERA) == true)
	{
		Robot::shooter->ZeroServoShooter();
	}

	// Keep in sync
	shooterServoPosition = Robot::shooter->GetCurrentServoPosition();

	if(RobotMap::SHOOTA_CALIBRATION_CONTROLLER_ENABLED)
	{
		/*
		 * This is strictly for use off the field and calibrating with a joystick controller with a slider.
		 */
		double desiredSpeed = Robot::shooter->GetShootaStartingSpeed();
		double speedAdjustment = 0;

		// Controller input is 0 - 1; Talon in speed mode expects RPM.
		speedAdjustment = Robot::oi->getLogitechExtreme()->GetRawAxis(SHOOTA_CALIBRATION_SLIDER)*-0.12;
		if (speedAdjustment > 0 || speedAdjustment < 0)
		{
			desiredSpeed = desiredSpeed+(desiredSpeed*speedAdjustment);
		}
		else if (speedAdjustment == 0)
		{
			desiredSpeed = Robot::shooter->GetShootaStartingSpeed();
		}
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
	Robot::shooter->ZeroServoShooter();
	Robot::shooter->SpeedControlShooter(RobotMap::STOP_SPEED);
}
