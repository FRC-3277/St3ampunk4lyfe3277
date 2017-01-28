#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
//#include "Commands/Subsystem.h"
#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "Subsystems/Motor.h"

class DriveTrain: public Subsystem {
private:
	std::shared_ptr<Motor> leftMotor;
	std::shared_ptr<Motor> rightMotor;
	std::shared_ptr<RobotDrive> motorRobotDrive25;

public:
	DriveTrain();
	void InitDefaultCommand();

	void setdrive(float speedleft, float speedright);
	void openmotors();

#endif
