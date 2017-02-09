#include "CANTalon.h"
#include "CANSpeedController.h"

#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon = RobotMap::shooterTalon;

	shooterTalon->SetControlMode(CANSpeedController::kPercentVbus);
	shooterTalon->EnableControl();
	shooterTalon->SetInverted(true);
	shooterTalon->Set(RobotMap::ALL_STOP);
}

void Shooter::InitDefaultCommand() {
	//SetDefaultCommand(new OperatorInputShooter());
}

void Shooter::SetShooterSpeed(double argShooterSpeed)
{
	shooterSpeed = argShooterSpeed;
}

double Shooter::GetShooterSpeed()
{
	return shooterSpeed;
}

void Shooter::SpeedControlShooter(double speedControlValue)
{
	shooterTalon->Set(speedControlValue);
}

