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

	//All
	static const bool ALTERNATE_CONTROLLER_ENABLED = true;

	static const bool
		isInfoLoggingEnabled = false,
		isDebugLoggingEnabled = true,
		isErrorLoggingEnabled = true,
		isWarningLoggingEnabled = false,
		isFatalLoggingEnabled = true,
		isTraceLoggingEnabled = false;

	static const int STOP_SPEED = 0;
	static constexpr float ALL_STOP = 0.0f;


	// DriveTrain
	static const int PORT_PROPELLER_LEFT_MOTOR = 1;
	static const int STARBOARD_PROPELLER_RIGHT_MOTOR = 2;

	static std::shared_ptr<CANTalon> driveTrainPortTalon;
	static std::shared_ptr<CANTalon> driveTrainStarboardTalon;
	static std::shared_ptr<RobotDrive> driveTrainSteamEngineRobotDrive;

	//Picker
	static const int PICKA_MOTOR = 4;
	static constexpr double BALL_PICKA_SPEED = 0.375;
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
	static constexpr double SHOOTA_STARTING_SPEED = 0.3;

	static std::shared_ptr<CANTalon> shooterTalon;

	//Vision
	static const int VISION_TRACKA_RELAY = 2;
	static std::shared_ptr<Relay> visionSpike;

	static void init();
};
#endif
