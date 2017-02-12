#include <iostream>
#include <string>

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

void Shooter::dumpEncoderLogging(std::shared_ptr<CANTalon> argTalon)
{
	double currentAmps = argTalon->GetOutputCurrent();
	double outputVolts = argTalon->GetOutputVoltage();
	double busVoltage = argTalon->GetBusVoltage();

	int quadEncoderPos = argTalon->GetEncPosition();
	int quadEncoderVelocity = argTalon->GetEncVel();

	int analogPos = argTalon->GetAnalogIn();
	int analogVelocity = argTalon->GetAnalogInVel();

	int selectedSensorPos = argTalon->GetPosition();
	int selectedSensorSpeed = argTalon->GetSpeed();

	int closedLoopErr = argTalon->GetClosedLoopError();

	lumberJack->dLog("Current Amps: " + to_string(currentAmps));
	lumberJack->dLog("Output Volts: " + to_string(outputVolts));
	lumberJack->dLog("Bus Voltage: " + to_string(busVoltage));
	lumberJack->dLog("Quad Encoder Pos: " + to_string(quadEncoderPos));
	lumberJack->dLog("Quad Encoder Velocity: " + to_string(quadEncoderVelocity));
	lumberJack->dLog("Analog Pos: " + to_string(analogPos));
	lumberJack->dLog("Analog Velocity: " + to_string(analogVelocity));
	lumberJack->dLog("Selected Sensor Pos: " + to_string(selectedSensorPos));
	lumberJack->dLog("Selected Sensor Speed: " + to_string(selectedSensorSpeed));
	lumberJack->dLog("Closed Loop Err: " + to_string(closedLoopErr));
}

