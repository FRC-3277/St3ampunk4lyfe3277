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


OI::OI()
{
	xBoxControllerDriver.reset(new Joystick(DRIVER_CONTROLLER));
	xBoxControllerAlternate.reset(new Joystick(ALTERNATE_CONTROLLER));

	//Map out the xBox Controller buttons (Possible bug not allowing these to be comma separated?)
	//Driver Controller
	JoystickButton* buttonAllAheadFlank = new JoystickButton(xBoxControllerDriver.get(), ALL_AHEAD_FLANK);
	JoystickButton* buttonFullAstern = new JoystickButton(xBoxControllerDriver.get(), FULL_ASTERN);
	JoystickButton* buttonPortPropeller = new JoystickButton(xBoxControllerDriver.get(), PORT_PROPELLER);
	JoystickButton* buttonStarboardPropeller = new JoystickButton(xBoxControllerDriver.get(), STARBOARD_PROPELLER);
	JoystickButton* buttonToggleStatusShoota = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_SHOOTA);
	JoystickButton* buttonToggleStatusDeployGear = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_DEPLOY_GEAR);
	JoystickButton* buttonToggleStatusPicka = new JoystickButton(xBoxControllerDriver.get(), TOGGLE_STATUS_PICKA);
	JoystickButton* buttonDeployGear = new JoystickButton(xBoxControllerDriver.get(), DEPLOY_GEAR);

	//Alternate Controller
	JoystickButton* buttonEnableClimber = new JoystickButton(xBoxControllerAlternate.get(), ENABLE_CLIMBER);

	//Button trigger and command mappings
	//buttonO_Matic->WhenPressed(new Command());
	buttonEnableClimber->WhenPressed(new OperatorInputClimber());

    // SmartDashboard Buttons
    //SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

}

std::shared_ptr<Joystick> OI::getXBoxControllerDriver()
{
   return xBoxControllerDriver;
}

std::shared_ptr<Joystick> OI::getXBoxControllerAlternate()
{
	return xBoxControllerAlternate;
}
