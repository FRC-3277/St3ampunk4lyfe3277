#include "CANTalon.h"
#include "CANSpeedController.h"

#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon = RobotMap::shooterTalon;

	//Encoder
	shooterTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
	shooterTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
	shooterTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
	shooterTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
	shooterTalon->SetIzone(TALON_IZONE);
	shooterTalon->SetCloseLoopRampRate(TALON_MAXRAMP);

	//Everything else
	shooterTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
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

