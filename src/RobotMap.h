// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


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
	// DriveTrain
	static const int PORT_PROPELLER_LEFT_MOTOR = 2;
	static const int STARBOARD_PROPELLER_RIGHT_MOTOR = 3;

	static std::shared_ptr<CANTalon> driveTrainPortTalon;
	static std::shared_ptr<CANTalon> driveTrainStarboardTalon;
	static std::shared_ptr<RobotDrive> driveTrainSteamEngineRobotDrive;

	//Picker
	static const int PICKA_RELAY = 0;
	static std::shared_ptr<Relay> pickerSpike;

	//Auger
	static const int HOPPA_AUGA_RELAY = 1;
	static std::shared_ptr<Relay> augerSpike;


	//Climber
	static const int CLIMBA_MOTOR = 25;
	static const int CLIMBER_SPEED = 0.4;

	static std::shared_ptr<CANTalon> climberTalon;

	//Shooter
	static const int SHOOTA_MOTOR = 24;
	static constexpr double SHOOTA_STARTING_SPEED = 0.2;

	static std::shared_ptr<CANTalon> shooterTalon;

	//Vision
	static const int VISION_TRACKA_RELAY = 2;
	static std::shared_ptr<Relay> visionSpike;

	//All
	static const bool
		isInfoLoggingEnabled = false,
		isDebugLoggingEnabled = true,
		isErrorLoggingEnabled = true,
		isWarningLoggingEnabled = false,
		isFatalLoggingEnabled = true,
		isTraceLoggingEnabled = false;

	static const int STOP_SPEED = 0;

	static void init();
};
#endif
