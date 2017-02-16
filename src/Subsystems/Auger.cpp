#include "Auger.h"
#include "../RobotMap.h"


Auger::Auger() : Subsystem("Auger") {
	augerSpike = RobotMap::augerSpike;
	lumberJack.reset(new LumberJack());

}

void Auger::InitDefaultCommand() {

}

void Auger::AugerAllShesGotCaptain() {
	augerSpike.get()->Set(Relay::kReverse);
}

void Auger::AugerStopScotty() {

	augerSpike.get()->Set(Relay::kOff);
}

void Auger::AugerDelay() {
	endTime = std::chrono::system_clock::now();
	elapsedSeconds = endTime-startTime;

	if(goForward)
	{
		augerSpike.get()->Set(Relay::kReverse);
		if(elapsedSeconds > goForwardNumberSeconds)
		{
			startTime = std::chrono::system_clock::now();
			goForward = false;
			goReverse = true;
		}
	}
	if(goReverse)
	{
		augerSpike.get()->Set(Relay::kForward);
		if(elapsedSeconds > goBackwardsNumberSeconds)
		{
			startTime = std::chrono::system_clock::now();
			goForward = true;
			goReverse = false;
		}
	}
}
