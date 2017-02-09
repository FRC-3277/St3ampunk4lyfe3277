#include "Auger.h"
#include "../RobotMap.h"


Auger::Auger() : Subsystem("Auger") {
	augerSpike = RobotMap::augerSpike;

}

void Auger::InitDefaultCommand() {

}

void Auger::RivetOn() {
	augerSpike.get()->Set(Relay::kOn);
}

void Auger::RivetOff() {

	augerSpike.get()->Set(Relay::kOff);
}
