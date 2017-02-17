#include <iostream>
#include <string>

#include "CANTalon.h"
#include "CANSpeedController.h"

#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon = RobotMap::shooterTalon;

	lumberJack.reset(new LumberJack());

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
	//dumpEncoderLogging();
}

void Shooter::dumpEncoderLogging()
{
	try
	{
		double currentAmps = shooterTalon->GetOutputCurrent();
		double outputVolts = shooterTalon->GetOutputVoltage();
		double busVoltage = shooterTalon->GetBusVoltage();

		int quadEncoderPos = shooterTalon->GetEncPosition();
		int quadEncoderVelocity = shooterTalon->GetEncVel();

		int analogPos = shooterTalon->GetAnalogIn();
		int analogVelocity = shooterTalon->GetAnalogInVel();

		int selectedSensorPos = shooterTalon->GetPosition();
		int selectedSensorSpeed = shooterTalon->GetSpeed();

		int closedLoopErr = shooterTalon->GetClosedLoopError();

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
	catch (const std::exception& e)
	{
		lumberJack->dLog(e.what());
		printf("%s", e.what());
	}
}

