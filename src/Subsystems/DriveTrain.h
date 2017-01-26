#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem {
private:
	std::shared_ptr<Motor> leftMotor;
	std::shared_ptr<Motor> rightMotor;
	std::shared_ptr<RobotDrive> robotDrive21;
public:
	DriveTrain();
	void InitDefaultCommand();

	void setdrive(float speedleft, float speedright);
	void openmotors();

#endif
