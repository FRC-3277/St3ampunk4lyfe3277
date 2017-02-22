#ifndef CLIMBER_H
#define CLIMBER_H
#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "./RobotMap.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Climber: public Subsystem {
private:
	std::shared_ptr<CANTalon> climberTalon;
	std::shared_ptr<LumberJack> lumberJack;


public:
	Climber();
	void InitDefaultCommand();

	void climberEngineAscend();
	void climberEngineDescend();
	void climberEngineStop();
};

#endif
