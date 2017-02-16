#ifndef AUGER_H
#define AUGER_H
#include <chrono>

#include "./LumberJack.h"
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
	std::shared_ptr<LumberJack> lumberJack;
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<double> elapsedSeconds;
	int numberSecondsElapsed = 0;

	bool goReverse = false,
			goForward = true,
			delayAuger = false;

	double goForwardNumberSeconds = 2;
	double goBackwardsNumberSeconds = 0.25;
	double delayAugerNumberSeconds = 0.8;

	std::chrono::seconds sec(goForwardNumberSeconds);

public:
	Auger();
	void InitDefaultCommand();

	void AugerAllShesGotCaptain();
	void AugerStopScotty();
	void AugerForwardAndReverse();
	void AugerDelay();
};

#endif
