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
#define TOGGLE_STATUS_AUGER_FORWARD XBOX_X_BUTTON
#define TOGGLE_STATUS_PICKA XBOX_RIGHT_SHOLDER_BUTTON
#define TOGGLE_CLIMBER_UP XBOX_LEFT_SHOLDER_BUTTON
//#define TOGGLE_CAMERA_VIEW XBOX_RIGHT_SHOLDER_BUTTON
#define TOGGLE_STATUS_AUGER_REVERSE XBOX_B_BUTTON

// Alternate Controller
//#define TOGGLE_STATUS_AUGER_REVERSE XBOX_X_BUTTON
#define TOGGLE_CLIMBER_DOWN XBOX_B_BUTTON

// Logitech Extreme 3D Pro
#define SHOOTA_ANGLA_ZERA 0
#define SHOOTA_CALIBRATION_SLIDER 3
#define AUGA_SPEED_UP 11
#define AUGA_SPEED_DOWN 10

class OI {
private:
	std::shared_ptr<Joystick> xBoxControllerDriver;
	std::shared_ptr<Joystick> xBoxControllerAlternate;
	std::shared_ptr<Joystick> logitechExtreme;

public:
	OI();
	std::shared_ptr<Joystick> getXBoxControllerDriver();
	std::shared_ptr<Joystick> getXBoxControllerAlternate();
	std::shared_ptr<Joystick> getLogitechExtreme();

};

#endif
