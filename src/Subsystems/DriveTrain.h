#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include <chrono>

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./RobotMap.h"
#include "LumberJack.h"

class DriveTrain: public Subsystem {
private:
	std::shared_ptr<CANTalon> portTalon;
	std::shared_ptr<CANTalon> starboardTalon;
	std::shared_ptr<RobotDrive> steamEngineRobotDrive;
	std::shared_ptr<LumberJack> lumberJack;

	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<float> elapsedTime;
	int numberSecondsElapsed = 0;

	double delayDriveTrainUntilEmpty = 11.5;
	double delayDriveTrainGear = 2;

	// Localized versions of talon calibration
	const float FULL_SPEED_FROM_TALONS=	RobotMap::FULL_SPEED_FROM_TALONS_BASE;
	const float TALON_FTERM_L = 		RobotMap::TALON_FTERM_L_BASE;
	const float TALON_PTERM_L = 		RobotMap::TALON_PTERM_L_BASE;
	const float TALON_ITERM_L = 		RobotMap::TALON_ITERM_L_BASE;
	const float TALON_DTERM_L = 		RobotMap::TALON_DTERM_L_BASE;
	const float TALON_FTERM_R = 		RobotMap::TALON_FTERM_R_BASE;
	const float TALON_PTERM_R = 		RobotMap::TALON_PTERM_R_BASE;
	const float TALON_ITERM_R = 		RobotMap::TALON_ITERM_R_BASE;
	const float TALON_DTERM_R = 		RobotMap::TALON_DTERM_R_BASE;
	const float TALON_MAXRAMP =			RobotMap::TALON_MAXRAMP_BASE;
	const float TALON_IZONE	=			RobotMap::TALON_IZONE_BASE;
	const float TALON_COUNTS_PER_REV =	RobotMap::TALON_COUNTS_PER_REV_BASE;
	const float REVS_PER_FOOT = 		RobotMap::REVS_PER_FOOT_BASE;
	const double METERS_PER_COUNT = 	RobotMap::METERS_PER_COUNT_BASE;

	void dumpEncoderLogging(std::shared_ptr<CANTalon> argTalon);

public:
	DriveTrain();
	void InitDefaultCommand();

	double autoCommand;

	void controllerInputToSteamEngine(double speedPort, double speedStarboard);
	void SetTalonStartPosition();
	void SetTalonForward();
	void SetTalonBackwards();
	void SetTalonStop();
	void TurnRight();
	void TurnLeft();
	void DelayUntilEmpty();
	void DelayForGear();
	double GetDashboard();
	double GetStarboardTalonEncoderPosition();
};

#endif
