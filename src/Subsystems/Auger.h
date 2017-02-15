#ifndef AUGER_H
#define AUGER_H
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

public:
	Auger();
	void InitDefaultCommand();

	void AugerAllShesGotCaptain();
	void AugerStopScotty();
};

#endif
