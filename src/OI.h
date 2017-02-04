// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef OI_H
#define OI_H

#include "WPILib.h"

/* Definitions */
#define XBOX_A_BUTTON 1
#define XBOX_B_BUTTON 2
#define XBOX_X_BUTTON 3
#define XBOX_Y_BUTTON 4
#define XBOX_LEFT_SHOLDER_BUTTON 5
#define XBOX_RIGHT_SHOLDER_BUTTON 6
#define XBOX_BACK_BUTTON 7
#define XBOX_START_BUTTON 8
#define XBOX_LEFT_INDEX_TRIGGER 9
#define XBOX_RIGHT_INDEX_TRIGGER 10

#define XBOX_LEFT_STICK_X_AXIS 0
#define XBOX_LEFT_STICK_Y_AXIS 1
#define XBOX_LEFT_TRIGGER_AXIS 2
#define XBOX_RIGHT_TRIGGER_AXIS 3
#define XBOX_RIGHT_STICK_X_AXIS 4
#define XBOX_RIGHT_STICK_Y_AXIS 5

#define DRIVER_CONTROLLER 0
#define ALTERNATE_CONTROLLER 1

/* Team Named Human Friendly Buttons Steam Punk Style */
// Driver Controller
#define ALL_AHEAD_FLANK XBOX_RIGHT_TRIGGER_AXIS
#define FULL_ASTERN XBOX_LEFT_TRIGGER_AXIS
#define PORT_PROPELLER XBOX_LEFT_STICK_Y_AXIS//Left motor solo
#define STARBOARD_PROPELLER XBOX_RIGHT_STICK_Y_AXIS//Right motor solo
#define TOGGLE_STATUS_SHOOTA XBOX_Y_BUTTON
#define TOGGLE_STATUS_DEPLOY_GEAR XBOX_X_BUTTON
#define TOGGLE_STATUS_PICKA XBOX_A_BUTTON
#define DEPLOY_GEAR XBOX_B_BUTTON

// Alternate Controller
#define ENABLE_CLIMBER XBOX_B_BUTTON

class OI {
private:
	std::shared_ptr<Joystick> xBoxControllerDriver;
	std::shared_ptr<Joystick> xBoxControllerAlternate;

public:
	OI();
	std::shared_ptr<Joystick> getXBoxControllerDriver();
	std::shared_ptr<Joystick> getXBoxControllerAlternate();

};

#endif
