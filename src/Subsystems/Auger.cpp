#include "Auger.h"
#include "../RobotMap.h"


Auger::Auger() : Subsystem("Auger") {
	augerSpike = RobotMap::augerSpike;
	lumberJack.reset(new LumberJack());
	startTime = std::chrono::system_clock::now();
}

void Auger::InitDefaultCommand() {

}

void Auger::AugerAllShesGotCaptain() {
	augerSpike->Set(Relay::kReverse);
}

void Auger::AugerStopScotty() {

	augerSpike->Set(Relay::kOff);
}

void Auger::AugerForwardAndReverse() {
	endTime = std::chrono::system_clock::now();
	elapsedTime = endTime - startTime;
	auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsedTime);

	if(goForward)
	{
		augerSpike->Set(Relay::kReverse);
		if(f_secs.count() > goForwardNumberSeconds)
		{
			startTime = std::chrono::system_clock::now();
			goForward = false;
			goReverse = true;
		}
	}
	else if(goReverse)
	{
		augerSpike->Set(Relay::kForward);
		if(f_secs.count() > goBackwardsNumberSeconds)
		{
			startTime = std::chrono::system_clock::now();
			goForward = true;
			goReverse = false;
		}
	}

	lumberJack->dLog("Seconds: " + to_string(f_secs.count()));

}

void Auger::AugerDelay() {
	endTime = std::chrono::system_clock::now();
	elapsedTime = endTime - startTime;
	auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsedTime);

	if(goForward)
	{
		augerSpike->Set(Relay::kReverse);
		if(f_secs.count() > goForwardNumberSeconds)
		{
				startTime = std::chrono::system_clock::now();
				goForward = false;
				delayAuger = true;
		}
	}
	else if(delayAuger)
	{
		augerSpike->Set(Relay::kOff);
		if(f_secs.count() > delayAugerNumberSeconds)
		{
			startTime = std::chrono::system_clock::now();
			goForward = true;
			delayAuger = false;
		}
	}
}
