#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
//#include "Commands/Subsystem.h"
#include <Commands/Subsystem.h>
#include "WPILib.h"

class DriveTrain: public Subsystem {
private:
	std::shared_ptr<SpeedController> portMotor;
	std::shared_ptr<SpeedController> starboardMotor;
	std::shared_ptr<RobotDrive> motorRobotDrive25;

public:
	DriveTrain();
	void InitDefaultCommand();

	void setdrive(float speedleft, float speedright);
	void openmotors();
};

#endif
