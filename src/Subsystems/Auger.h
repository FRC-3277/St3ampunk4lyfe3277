#ifndef AUGER_H
#define AUGER_H
#include <chrono>

#include "./LumberJack.h"
#include "./Robot.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Auger: public Subsystem {
private:
	std::shared_ptr<Relay> augerSpike;
	std::shared_ptr<CANTalon> augerTalon;
	std::shared_ptr<LumberJack> lumberJack;
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<float> elapsedTime;
	int numberSecondsElapsed = 0;

	bool goReverse = false,
			goForward = true,
			delayAuger = false,
			delayAugerForShooter = true,
			augerStop = false;

	double previousVelocity = 0;
	double nowVelocity = 0;

	double goForwardNumberSeconds = 1;
	double goBackwardsNumberSeconds = 0.15;
	double delayAugerNumberSeconds = 0.8;
	double augerSpeed = 0.70;
	double augerBackwards = -0.5;
	double augerAutonomousSpeed = 0.7;

public:
	Auger();
	void InitDefaultCommand();

	void AugerAllShesGotCaptain();
	void AutonomousAugerAllShesGotCaptain();
	void AugerCleanAndSweepReverse();
	void AugerStopScotty();
	void AugerForwardAndReverse();
	void AugerDelay();
	void AugerShooterDelay();
};

#endif
