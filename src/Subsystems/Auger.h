#ifndef AUGER_H
#define AUGER_H
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

public:
	Auger();
	void InitDefaultCommand();

	void AugerAllShesGotCaptain();
	void AugerStopScotty();
};

#endif
