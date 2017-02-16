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

	bool goReverse = false,
			goForward = true;

	double goForwardNumberSeconds = 2;
	double goBackwardsNumberSeconds = 0.25;

public:
	Auger();
	void InitDefaultCommand();

	void AugerAllShesGotCaptain();
	void AugerStopScotty();
	void AugerDelay();
};

#endif
