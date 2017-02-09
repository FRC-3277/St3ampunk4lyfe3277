#ifndef SHOOTER_H
#define SHOOTER_H
#include "CANTalon.h"

#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public Subsystem {
private:
	std::shared_ptr<CANTalon> shooterTalon;

	double shooterSpeed = 0;

public:
	Shooter();
	void InitDefaultCommand();

	void SetShooterSpeed(double speedControlValue);
	double GetShooterSpeed();
	void SpeedControlShooter(double speedControlValue);
};

#endif
