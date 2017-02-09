#include "Auger.h"
#include "../RobotMap.h"


Auger::Auger() : Subsystem("Auger") {
	augerSpike = RobotMap::augerSpike;

}

void Auger::InitDefaultCommand() {

}

void Auger::AugerAllShesGotCaptain() {
	augerSpike.get()->Set(Relay::kOn);
}

void Auger::AugerStopScotty() {

	augerSpike.get()->Set(Relay::kOff);
}
