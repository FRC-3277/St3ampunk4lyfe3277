#include <iostream>
#include <string>

#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon = RobotMap::shooterTalon;
	shooterServoLeft.reset(new Servo(RobotMap::SHOOTA_SERVO_PWM_CHANNEL_LEFT));
	shooterServoRight.reset(new Servo(RobotMap::SHOOTA_SERVO_PWM_CHANNEL_RIGHT));
	lumberJack.reset(new LumberJack());

	// Clear these for use with Autonomous mode
	SmartDashboard::PutString("DB/String 0", "");
	SmartDashboard::PutString("DB/String 1", "");
	SmartDashboard::PutString("DB/String 2", "");
	SmartDashboard::PutString("DB/String 3", "");

	if(RobotMap::SHOOTA_PID_SYSTEM)
	{
		SHOOTA_STARTING_SPEED = 2300;
		SHOOTA_AUTONOMOUS_SPEED = 2350.281;
		SHOOTA_MAX_CALIBRATION_SPEED = 2900;
		MIN_SHOOTA_SPEED_BEFORE_CUTOUT = 500;
		p = 16;
		i = 0;
		d = 1;
		f = 0;
		izone = 300;
		ramprate = 70;
		profile = 1;
	}
	else
	{
		SHOOTA_STARTING_SPEED = 0.375;
	}

	if(RobotMap::SHOOTA_PID_SYSTEM)
	{
		SmartDashboard::PutString("DB/String 0", to_string(p));
		SmartDashboard::PutString("DB/String 1", to_string(i));
		SmartDashboard::PutString("DB/String 2", to_string(d));
		SmartDashboard::PutString("DB/String 3", to_string(f));

		shooterTalon->SetControlMode(CANSpeedController::kSpeed);

		shooterTalon->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 20);

		//Encoder
		// See 12.4.1 and 12.4.2 of TALON SRX Software Reference Manual
		shooterTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
		shooterTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
		shooterTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
		shooterTalon->SetSensorDirection(true);

		shooterTalon->ConfigNominalOutputVoltage(0.0f, 0.0f);
		shooterTalon->ConfigPeakOutputVoltage(12.0f, -12.0f);

		//Everything else
		shooterTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

		shooterTalon->SelectProfileSlot(profile);
		shooterTalon->SetPID(p, i, d, f);
		shooterTalon->SetIzone(izone);
		shooterTalon->SetCloseLoopRampRate(ramprate);

		//Motion Magic Closed-Loop... unsupported with CANTalon... or it seems so.
		shooterTalon->SetMotionMagicCruiseVelocity(SHOOTA_STARTING_SPEED); // In RPMs
		shooterTalon->SetMotionMagicAcceleration(2000); // In RPMs per sec until cruise velocity
	}
	else
	{
		shooterTalon->SetControlMode(CANSpeedController::kPercentVbus);
	}
	shooterTalon->SetInverted(false);
	shooterTalon->SetPosition(0);
	shooterTalon->EnableControl();
	shooterTalon->Set(RobotMap::ALL_STOP);
}

void Shooter::InitDefaultCommand() {
}

void Shooter::SetShooterSpeed(double argShooterSpeed)
{
	shooterSpeed = fabs(argShooterSpeed);
}

double Shooter::GetShooterSpeed()
{
	return fabs(shooterSpeed);
}

double Shooter::GetShootaStartingSpeed()
{
	return SHOOTA_STARTING_SPEED;
}

double Shooter::GetAutonomousShootaStartingSpeed()
{
	return SHOOTA_AUTONOMOUS_SPEED;
}

double Shooter::GetShootaMaxCalibrationSpeed()
{
	return SHOOTA_MAX_CALIBRATION_SPEED;
}

void Shooter::SpeedControlShooter(double speedControlValue)
{
	speedControlValue = fabs(speedControlValue);
	if(RobotMap::SHOOTA_ENABLE_PIDF_CALIBRATION)
	{
		p = std::stod(SmartDashboard::GetString("DB/String 0", to_string(p)));
		i = std::stod(SmartDashboard::GetString("DB/String 1", to_string(i)));
		d = std::stod(SmartDashboard::GetString("DB/String 2", to_string(d)));
		f = std::stod(SmartDashboard::GetString("DB/String 3", to_string(f)));

		shooterTalon->SetPID(p, i, d, f);

		//Motion Magic Closed-Loop... unsupported with CANTalon... or it seems so.
		shooterTalon->SetMotionMagicCruiseVelocity(1000); // In RPMs
		shooterTalon->SetMotionMagicAcceleration(2000); // In RPMs per sec until cruise velocity
	}

	double quadEncoderPos = shooterTalon->GetEncPosition();
	double quadEncoderVelocity = shooterTalon->GetEncVel();

	lumberJack->dashLogNumber("Shooter Position", quadEncoderPos);
	lumberJack->dashLogNumber("Shooter Velocity", quadEncoderVelocity);
	lumberJack->dashLogNumber("Shooter Speed Desired", speedControlValue);

	// Prevent the belt from jumping and the motor from hunting for zero.
	if(RobotMap::SHOOTA_PID_SYSTEM &&
		speedControlValue < MIN_SHOOTA_SPEED_BEFORE_CUTOUT)
	{
		shooterTalon->SetControlMode(CANSpeedController::kPercentVbus);
	}
	else
	{
		shooterTalon->SetControlMode(CANSpeedController::kSpeed);
	}

	testingSpeed = shooterTalon->GetSpeed();
	//lumberJack->dLog("Testing Speed" +to_string(testingSpeed));

	shooterTalon->Set(speedControlValue);

	//dumpEncoderLogging();
}

void Shooter::GetShooterSpeedForDelay()
{
	testingSpeed = shooterTalon->GetSpeed();
}

void Shooter::AutonomousSpeedControlShooter(double speedControlValue, int Color)
{
	speedControlValue = fabs(speedControlValue);
	if(RobotMap::SHOOTA_ENABLE_PIDF_CALIBRATION)
	{
		p = std::stod(SmartDashboard::GetString("DB/String 0", to_string(p)));
		i = std::stod(SmartDashboard::GetString("DB/String 1", to_string(i)));
		d = std::stod(SmartDashboard::GetString("DB/String 2", to_string(d)));
		f = std::stod(SmartDashboard::GetString("DB/String 3", to_string(f)));

		shooterTalon->SetPID(p, i, d, f);

		//Motion Magic Closed-Loop... unsupported with CANTalon... or it seems so.
		shooterTalon->SetMotionMagicCruiseVelocity(1000); // In RPMs
		shooterTalon->SetMotionMagicAcceleration(2000); // In RPMs per sec until cruise velocity
	}

	double quadEncoderPos = shooterTalon->GetEncPosition();
	double quadEncoderVelocity = shooterTalon->GetEncVel();

	lumberJack->dashLogNumber("Shooter Position", quadEncoderPos);
	lumberJack->dashLogNumber("Shooter Velocity", quadEncoderVelocity);
	lumberJack->dashLogNumber("Shooter Speed Desired", speedControlValue);

	// Prevent the belt from jumping and the motor from hunting for zero.
	if(RobotMap::SHOOTA_PID_SYSTEM &&
		speedControlValue < MIN_SHOOTA_SPEED_BEFORE_CUTOUT)
	{
		shooterTalon->SetControlMode(CANSpeedController::kPercentVbus);
	}
	else
	{
		shooterTalon->SetControlMode(CANSpeedController::kSpeed);
	}
	// Red
	if (Color == 1)
	{
		shooterTalon->Set(speedControlValue+35);
	}
	// Blue
	else if(Color == 0)
	{
		shooterTalon->Set(speedControlValue-8);
	}
	else if(Color == 2)
	{
		shooterTalon->Set(speedControlValue+1200);
	}
	else if(Color == 3)
	{
		shooterTalon->Set(speedControlValue+1430);
	}
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

void Shooter::ZeroServoShooterLeft()
{
	shooterServoLeft->SetAngle(servoZeroPositionLeft);
	servoLeftCurrentPosition = servoZeroPositionLeft;
}

void Shooter::ZeroServoShooterRight()
{
	shooterServoRight->SetAngle(servoZeroPositionRight);
	servoRightCurrentPosition = servoZeroPositionRight;
}

void Shooter::AdjustServoShooterLeft(double adjustmentValue)
{
	if(adjustmentValue < shooterMinHardStop)
	{
		adjustmentValue = shooterMinHardStop;
	}
	else if(adjustmentValue > shooterMaxHardStop)
	{
		adjustmentValue = shooterMaxHardStop;
	}

	shooterServoLeft->SetAngle(102 - adjustmentValue);
	servoLeftCurrentPosition = adjustmentValue;
}

void Shooter::AdjustServoShooterRight(double adjustmentValue)
{
	if(adjustmentValue < shooterMinHardStop)
	{
		adjustmentValue = shooterMinHardStop;
	}
	else if(adjustmentValue > shooterMaxHardStop)
	{
		adjustmentValue = shooterMaxHardStop;
	}

	shooterServoRight->SetAngle(adjustmentValue);
	servoRightCurrentPosition = adjustmentValue;
}

void Shooter::SetShooterAllStop()
{
	shooterTalon->SetControlMode(CANSpeedController::kPercentVbus);
	shooterTalon->Set(RobotMap::ALL_STOP);
}

double Shooter::GetCurrentServoPositionLeft()
{
	return servoLeftCurrentPosition;
}

double Shooter::GetCurrentServoPositionRight()
{
	return servoRightCurrentPosition;
}
