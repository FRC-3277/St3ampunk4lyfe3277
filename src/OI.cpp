// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// See http://wpilib.screenstepslive.com/s/4485/m/13810/l/241904-running-commands-on-joystick-input for examples.

#include "OI.h"
#include <Buttons/JoystickButton.h>

#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/OperatorInputClimber.h"
#include "Commands/OperatorInputBallPicker.h"
#include "Commands/OperatorInputAuger.h"
#include "Commands/OperatorInputShooter.h"
#include "Commands/OperatorInputCameraSwitch.h"

OI::OI()
{
	xBoxControllerDriver.reset(new Joystick(DRIVER_CONTROLLER));
	if(RobotMap::ALTERNATE_CONTROLLER_ENABLED)
	{
		xBoxControllerAlternate.reset(new Joystick(ALTERNATE_CONTROLLER));

		//Alternate Controller
		JoystickButton* buttonEnableClimberDown = new JoystickButton(xBoxControllerAlternate.get(), TOGGLE_CLIMBER_DOWN);

		buttonEnableClimberDown->WhenPressed(new OperatorInputClimber());
	}
	else if(RobotMap::SHOOTA_CALIBRATION_CONTROLLER_ENABLED)
	{
		logitechExtreme.reset(new Joystick(ALTERNATE_CONTROLLER));
	}

	//Map out the xBox Controller buttons (Possible bug not allowing these to be comma separated?)
	//Driver Controller
	JoystickButton* buttonToggleStatusShoota = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_SHOOTA);
	JoystickButton* buttonToggleStatusPicka = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_PICKA);
	JoystickButton* buttonEnableClimberUp = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_CLIMBER_UP);
	JoystickButton* buttonToggleStatusAugerForward = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_AUGER_FORWARD);
	//JoystickButton* buttonToggleCamera = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_CAMERA_VIEW);
	//JoystickButton* buttonEnableClimberDown = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_CLIMBER_DOWN);
	JoystickButton* buttonToggleStatusAugerReverse = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_AUGER_REVERSE);

	//Button trigger and command mappings
	buttonEnableClimberUp->ToggleWhenPressed(new OperatorInputClimber());
	buttonToggleStatusPicka->WhenPressed(new OperatorInputBallPicker());
	buttonToggleStatusAugerForward->ToggleWhenPressed(new OperatorInputAuger(RobotMap::DIRECTION_FORWARD));
	//buttonToggleCamera->WhenPressed(new OperatorInputCameraSwitch());
	buttonToggleStatusAugerReverse->ToggleWhenPressed(new OperatorInputAuger(RobotMap::DIRECTION_REVERSE));

	/*The shooter is enabled manually by the operator.  This enables
	  both the shooter motor and also the vision tracking feedback helper
	  functions which positions the robot and sets the speed of the
	  motor.
	*/
	buttonToggleStatusShoota->ToggleWhenPressed(new OperatorInputShooter());

    // SmartDashboard Buttons
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

}

std::shared_ptr<Joystick> OI::getXBoxControllerDriver()
{
   return xBoxControllerDriver;
}

std::shared_ptr<Joystick> OI::getXBoxControllerAlternate()
{
	return xBoxControllerAlternate;
}

std::shared_ptr<Joystick> OI::getLogitechExtreme()
{
	return logitechExtreme;
}

