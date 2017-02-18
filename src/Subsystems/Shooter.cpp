#include <iostream>
#include <string>

#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon = RobotMap::shooterTalon;

	lumberJack.reset(new LumberJack());

	SmartDashboard::PutNumber("DB/Slider 0", 0.3);
	SmartDashboard::PutNumber("DB/Slider 1", 0.003);
	SmartDashboard::PutNumber("DB/Slider 2", 3);
	SmartDashboard::PutNumber("DB/Slider 3", 0.0003);

	shooterTalon->SetControlMode(CANSpeedController::kSpeed);

	//Encoder
	// See 12.4.1 and 12.4.2 of TALON SRX Software Reference Manual
	shooterTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
	shooterTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
	shooterTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	shooterTalon->SetSensorDirection(true);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
	//shooterTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
	//shooterTalon->SetIzone(TALON_IZONE);
	//shooterTalon->SetPID(0.6, 0.03, 0.03, 0);
	//shooterTalon->SetIzone(300);
	/*
	 * Limits the rate at which the throttle will change.
     * Only affects position and speed closed loop modes.
	 */
	//shooterTalon->SetCloseLoopRampRate(TALON_MAXRAMP);
	shooterTalon->ConfigNominalOutputVoltage(0.0f, 0.0f);
	shooterTalon->ConfigPeakOutputVoltage(12.0f, -12.0f);

	//Motion Magic Closed-Loop... unsupported with CANTalon... or it seems so.
	//shooterTalon->SetMotionMagicCruiseVelocity(1000); // In RPMs
	//shooterTalon->SetMotionMagicAcceleration(2000); // In RPMs per sec until cruise velocity

	//Everything else
	//shooterTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
	//shooterTalon->SetControlMode(CANSpeedController::kPercentVbus);

	double p = 0.3, i = 0.003, d = 3, f = 0.0003;
	double izone = 300;
	double ramprate = 48;
	int profile = 1;

	shooterTalon->SelectProfileSlot(profile);
	shooterTalon->SetPID(p, i, d, f);
	shooterTalon->SetIzone(izone);
	shooterTalon->SetCloseLoopRampRate(ramprate);

	shooterTalon->SetInverted(true);
	shooterTalon->SetPosition(0);
	shooterTalon->EnableControl();
	shooterTalon->Set(RobotMap::ALL_STOP);
}

void Shooter::InitDefaultCommand() {
	//SetDefaultCommand(new OperatorInputShooter());
}

void Shooter::SetShooterSpeed(double argShooterSpeed)
{
	shooterSpeed = fabs(argShooterSpeed);
}

double Shooter::GetShooterSpeed()
{
	return fabs(shooterSpeed);
}

void Shooter::SpeedControlShooter(double speedControlValue)
{
	speedControlValue = fabs(speedControlValue);
	if(RobotMap::SHOOTA_ENABLE_PIDF_CALIBRATION)
	{
		double p = 0, i = 0, d = 0, f = 0;

		p = SmartDashboard::GetNumber("DB/Slider 0", 0.3);
		i = SmartDashboard::GetNumber("DB/Slider 1", 0.003);
		d = SmartDashboard::GetNumber("DB/Slider 2", 3);
		f = SmartDashboard::GetNumber("DB/Slider 3", 0.0003);

		shooterTalon->SetPID(p, i, d, f);
	}

	double quadEncoderPos = shooterTalon->GetEncPosition();
	double quadEncoderVelocity = shooterTalon->GetEncVel();

	lumberJack->dashLogNumber("Shooter Position", quadEncoderPos);
	lumberJack->dashLogNumber("Shooter Velocity", quadEncoderVelocity);
	lumberJack->dashLogNumber("Shooter Speed Desired", speedControlValue);

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

