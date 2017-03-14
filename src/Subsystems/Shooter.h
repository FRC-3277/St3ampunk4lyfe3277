#ifndef SHOOTER_H
#define SHOOTER_H
#include "CANTalon.h"
#include "CANSpeedController.h"

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./RobotMap.h"
#include "LumberJack.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public Subsystem {
private:
	std::shared_ptr<CANTalon> shooterTalon;
	std::shared_ptr<Servo> shooterServo;
	std::shared_ptr<LumberJack> lumberJack;

	// The speed that it starts at, or perhaps suggests
	double SHOOTA_STARTING_SPEED;
	double SHOOTA_AUTONOMOUS_SPEED;
	// Calibration speed from Joystick slider
	double SHOOTA_MAX_CALIBRATION_SPEED;
	// Prevent the shooter from jumping the belt.
	double MIN_SHOOTA_SPEED_BEFORE_CUTOUT;

	// Requires calibration
	int servoZeroPosition = 10;
	int servoCurrentPosition = servoZeroPosition;

	double testingSpeed = 0;

	double shooterSpeed = 0;
	double p;
	double i;
	double d;
	double f;
	double izone = 300;
	/*
	 * Limits the rate at which the throttle will change.
	 * Only affects position and speed closed loop modes.
	 */
	double ramprate = 70;
	int profile = 1;

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

	void dumpEncoderLogging();

public:

	Shooter();
	void InitDefaultCommand();

	void SetShooterSpeed(double speedControlValue);
	double GetShooterSpeed();
	double GetAutonomousShootaStartingSpeed();
	void SpeedControlShooter(double speedControlValue);
	void AutonomousSpeedControlShooter(double speedControlValue, int Color);
	double GetShootaStartingSpeed();
	double GetShootaMaxCalibrationSpeed();
	void GetShooterSpeedForDelay();
	void ZeroServoShooter();
	void AdjustServoShooter(int adjustmentValue);
	int GetCurrentServoPosition();
};

#endif
