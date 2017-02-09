#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "LumberJack.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem {
private:
	std::shared_ptr<CANTalon> portTalon;
	std::shared_ptr<CANTalon> starboardTalon;
	std::shared_ptr<RobotDrive> steamEngineRobotDrive;

	LumberJack lumberJack;

public:
	DriveTrain();
	void InitDefaultCommand();

	void controllerInputToSteamEngine(double speedPort, double speedStarboard);
};

#endif
