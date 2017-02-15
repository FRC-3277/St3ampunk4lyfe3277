#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "CANTalon.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:

	// All
	static const bool ALTERNATE_CONTROLLER_ENABLED = true;

	static const bool
		isInfoLoggingEnabled = false,
		isDebugLoggingEnabled = false,
		isErrorLoggingEnabled = true,
		isWarningLoggingEnabled = false,
		isFatalLoggingEnabled = true,
		isTraceLoggingEnabled = false;

	static const int STOP_SPEED = 0;
	static constexpr float ALL_STOP = 0.0f;

	// Talon and Encoder
	//TODO: Adjust these values http://www.ctr-electronics.com/downloads/pdf/Talon%20SRX%20Software%20Reference%20Manual.pdf
	static constexpr float FULL_SPEED_FROM_TALONS_BASE = 	0.0;	// measured on the robot in RPMs
	static constexpr float TALON_FTERM_L_BASE = 		0.0;	// From CTRE manual, section 12.4
	static constexpr float TALON_PTERM_L_BASE = 		(TALON_FTERM_L_BASE / 5.0);
	static constexpr float TALON_ITERM_L_BASE = 		(TALON_PTERM_L_BASE / 10.0);
	static constexpr float TALON_DTERM_L_BASE = 		(TALON_PTERM_L_BASE / 5.0);
	static constexpr float TALON_FTERM_R_BASE = 		0.0;	// From CTRE manual, section 12.4
	static constexpr float TALON_PTERM_R_BASE = 		(TALON_FTERM_R_BASE / 5.0);
	static constexpr float TALON_ITERM_R_BASE = 		(TALON_PTERM_R_BASE / 10.0);
	static constexpr float TALON_DTERM_R_BASE = 		(TALON_PTERM_R_BASE / 5.0);
	//TODO: Confirm ms
	static constexpr float TALON_MAXRAMP_BASE =			60;		// volts per second 0% to 100% in 200-250?ms
	static constexpr float TALON_IZONE_BASE	=			128;
	static constexpr float TALON_COUNTS_PER_REV_BASE =	20;  //Configure how many codes per revolution are generated by your encoder.
	static constexpr float REVS_PER_FOOT_BASE = 		(3.141519 * 6.0 / 12.0);
	static constexpr double METERS_PER_COUNT_BASE = 	(REVS_PER_FOOT_BASE * 0.3048 / (double)TALON_COUNTS_PER_REV_BASE);
	static const int CLOSED_LOOP_GAIN = 				0; //one or zero depending on which slot caller wants. Closed loop gains in slot0.

	// DriveTrain
	static const int PORT_PROPELLER_LEFT_MOTOR = 1;
	static const int STARBOARD_PROPELLER_RIGHT_MOTOR = 2;

	static std::shared_ptr<CANTalon> driveTrainPortTalon;
	static std::shared_ptr<CANTalon> driveTrainStarboardTalon;
	static std::shared_ptr<RobotDrive> driveTrainSteamEngineRobotDrive;

	//Picker
	static const int PICKA_MOTOR = 4;
	static constexpr double BALL_PICKA_SPEED = 0.6;
	static std::shared_ptr<CANTalon> pickerTalon;

	//Auger
	static const int HOPPA_AUGA_RELAY = 0;
	static std::shared_ptr<Relay> augerSpike;

	//Climber
	static const int CLIMBA_MOTOR = 3;
	static constexpr double CLIMBER_SPEED = 1.0;

	static std::shared_ptr<CANTalon> climberTalon;

	//Shooter
	static const int SHOOTA_MOTOR = 6;
	static constexpr double SHOOTA_STARTING_SPEED = 0.375;

	static std::shared_ptr<CANTalon> shooterTalon;

	//Vision
	static const int VISION_TRACKA_RELAY = 2;
	static std::shared_ptr<Relay> visionSpike;

	static void init();
};
#endif
