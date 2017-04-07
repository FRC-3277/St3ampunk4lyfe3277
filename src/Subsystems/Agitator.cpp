#include "Agitator.h"
#include "../RobotMap.h"

Agitator::Agitator() : Subsystem("Agitator") {
	agitatorSpike = RobotMap::agitatorSpike;
	lumberJack.reset(new LumberJack());
}

void Agitator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Agitator::AgitatorAllShesGot() {
	agitatorSpike->Set(Relay::kOn);
}

void Agitator::AgitatorFullStop() {
	agitatorSpike->Set(Relay::kOff);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
