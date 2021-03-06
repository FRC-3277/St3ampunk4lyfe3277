#include <iostream>
#include <string>

#include "CANTalon.h"
#include "CANSpeedController.h"

#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/OperatorInputDriveTrain.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	lumberJack.reset(new LumberJack());

	//startTime = std::chrono::system_clock::now();

	autoCommand = autoCommand*1;

    portTalon = RobotMap::driveTrainPortTalon;
    starboardTalon = RobotMap::driveTrainStarboardTalon;
    steamEngineRobotDrive = RobotMap::driveTrainSteamEngineRobotDrive;

//  SmartDashboard::PutNumber("DB/Slider 0", 0.3);
//	SmartDashboard::PutNumber("DB/Slider 1", 0.003);
//	SmartDashboard::PutNumber("DB/Slider 2", 3);
//	SmartDashboard::PutNumber("DB/Slider 3", 0.0003);

//	portTalon->SetControlMode(CANSpeedController::kSpeed);
//	starboardTalon->SetControlMode(CANSpeedController::kSpeed);

    //Encoder portTalon
    portTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
    portTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
    portTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
    portTalon->SetSensorDirection(true);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
//    portTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
//    portTalon->SetIzone(TALON_IZONE);
//    portTalon->SetCloseLoopRampRate(TALON_MAXRAMP);

	//Encoder starboardTalon
    starboardTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
    starboardTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
    starboardTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	starboardTalon->SetSensorDirection(true);
    /*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
//    starboardTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
//    starboardTalon->SetIzone(TALON_IZONE);
//    starboardTalon->SetCloseLoopRampRate(TALON_MAXRAMP);
	portTalon->ConfigNominalOutputVoltage(0.0f, 0.0f);
	portTalon->ConfigPeakOutputVoltage(12.0f, -12.0f);

	starboardTalon->ConfigNominalOutputVoltage(0.0f, 0.0f);
	starboardTalon->ConfigPeakOutputVoltage(12.0f, -12.0f);


//    portTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    portTalon->SetControlMode(CANSpeedController::kPercentVbus);
    portTalon->EnableControl();
    portTalon->Set(RobotMap::ALL_STOP);
	portTalon->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 20);

//    starboardTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    starboardTalon->SetControlMode(CANSpeedController::kPercentVbus);
    starboardTalon->EnableControl();
    starboardTalon->Set(RobotMap::ALL_STOP);
	starboardTalon->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 20);

    steamEngineRobotDrive->SetSafetyEnabled(false);
    steamEngineRobotDrive->SetExpiration(0.1);
    steamEngineRobotDrive->SetSensitivity(0.5);
    steamEngineRobotDrive->SetMaxOutput(1.0);
    steamEngineRobotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
    steamEngineRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new OperatorInputDriveTrain());
}

/********* BEGIN METHODS CALLED BY COMMANDS **********/
void DriveTrain::controllerInputToSteamEngine(double speedPort, double speedStarboard){
	string left = "DriveTrain - Left: " + to_string(speedPort),
			right = "\tRight: " + to_string(speedStarboard);
	//lumberJack->dLog(left + right);
	steamEngineRobotDrive->TankDrive(speedPort, speedStarboard);
}

void DriveTrain::SetTalonStartPosition()
{
	portTalon->SetEncPosition(0.0);
	starboardTalon->SetEncPosition(0.0);
}

void DriveTrain::SetTalonForward()
{
	portTalon->Set(-0.45);
	starboardTalon->Set(0.45);
}

void DriveTrain::SetTalonBackwards()
{
	portTalon->Set(0.45);
	starboardTalon->Set(-0.45);
}

void DriveTrain::SetTalonStop()
{
	portTalon->Set(0.0);
	starboardTalon->Set(0.0);
}

double DriveTrain::GetStarboardTalonEncoderPosition()
{
	return fabs(starboardTalon->GetEncPosition());

}

void DriveTrain::TurnLeft()
{
	portTalon->Set(0.35);
	starboardTalon->Set(0.35);
}

void DriveTrain::TurnRight()
{
	portTalon->Set(-0.35);
	starboardTalon->Set(-0.35);
}

void DriveTrain::DelayUntilEmpty(double delayTime)
{
	lumberJack->dLog("Begin");
	while (true)
	{
		endTime = std::chrono::system_clock::now();
		elapsedTime = endTime - startTime;
		auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsedTime);
		if (f_secs.count() > delayTime)
		{
			lumberJack->dLog("End");
			break;
		}
	}
}

void DriveTrain::SetStartTime()
{
	startTime = std::chrono::system_clock::now();
}

//void DriveTrain::DelayForGear()
//{
//	endTime = std::chrono::system_clock::now();
//	elapsedTime = endTime - startTime;
//	auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsedTime);
//	while (f_secs.count() < delayDriveTrainGear)
//	{
//		endTime = std::chrono::system_clock::now();
//		elapsedTime = endTime - startTime;
//		auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsedTime);
//	}
//}

double DriveTrain::GetDashboard()
{
	autoCommand = std::stod(SmartDashboard::GetString("DB/String 5", to_string(autoCommand)));
	return autoCommand;
}

void DriveTrain::dumpEncoderLogging(std::shared_ptr<CANTalon> argTalon)
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
