#ifndef CLIMBER_H
#define CLIMBER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Climber: public Subsystem {
private:
	std::shared_ptr<CANTalon> climberTalon;

public:
	Climber();
	void InitDefaultCommand();

	void climberEngineAscend();
	void climberEngineStop();
};

#endif
