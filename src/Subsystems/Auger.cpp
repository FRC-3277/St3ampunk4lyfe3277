#include "Auger.h"
#include "../RobotMap.h"


Auger::Auger() : Subsystem("Auger") {
	if(RobotMap::AUGER_TALON_MOTOR_ENABLED)
	{
		augerTalon = RobotMap::augerTalon;

		augerTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
		augerTalon->SetControlMode(CANSpeedController::kPercentVbus);
		augerTalon->EnableControl();
		augerTalon->SetInverted(false);
		augerTalon->Set(RobotMap::ALL_STOP);
	}
	else
	{
		augerSpike = RobotMap::augerSpike;
	}

	lumberJack.reset(new LumberJack());

	startTime = std::chrono::system_clock::now();
}

void Auger::InitDefaultCommand() {

}

void Auger::AugerAllShesGotCaptain(double augerSpeed) {
	if(RobotMap::AUGER_TALON_MOTOR_ENABLED)
	{
		augerTalon->Set(augerSpeed);
	}
	else
	{
		augerSpike->Set(Relay::kReverse);
	}
}

void Auger::AutonomousAugerAllShesGotCaptain() {
	if(RobotMap::AUGER_TALON_MOTOR_ENABLED)
	{
		augerTalon->Set(augerAutonomousSpeed);
	}
}

void Auger::AugerCleanAndSweepReverse(){
	if(RobotMap::AUGER_TALON_MOTOR_ENABLED)
	{
		augerTalon->Set(augerBackwards);
	}
	else
	{
		augerSpike->Set(Relay::kForward);
	}
}

void Auger::AugerStopScotty() {
	if(RobotMap::AUGER_TALON_MOTOR_ENABLED)
	{
		augerTalon->Set(0);
		lumberJack->dLog("Hey There");
	}
	else
	{
		augerSpike->Set(Relay::kOff);
	}
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

//	Ramp up speed starting with minimum and up to maximum and then back down to minimum.  Rinse lather repeat.
void Auger::AugerWashingMachineWashingMachine(double maxSpeed, double minSpeed)
{
	if(augerCurrentSpeed < maxSpeed && augerCurrentSpeed < 1)
	{
		augerCurrentSpeed = augerCurrentSpeed + .005;
	}
	else
	{
		augerCurrentSpeed = minSpeed;
	}
	augerTalon->Set(augerCurrentSpeed);
}
