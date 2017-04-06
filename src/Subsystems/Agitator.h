#ifndef Agitator_H
#define Agitator_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Agitator : public Subsystem {
private:
	std::shared_ptr<Relay> agitatorSpike;
	std::shared_ptr<LumberJack> lumberJack;

public:
	Agitator();
	void InitDefaultCommand();
	void AgitatorAllShesGot();
	void AgitatorFullStop();
};

#endif  // Agitator_H
