#include <iostream>
#include <string>

#include "CANTalon.h"
#include "CANSpeedController.h"

#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/OperatorInputDriveTrain.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	lumberJack.reset(new LumberJack());

    portTalon = RobotMap::driveTrainPortTalon;
    starboardTalon = RobotMap::driveTrainStarboardTalon;
    steamEngineRobotDrive = RobotMap::driveTrainSteamEngineRobotDrive;

    //Encoder portTalon
    portTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
    portTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
    portTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
    portTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
    portTalon->SetIzone(TALON_IZONE);
    portTalon->SetCloseLoopRampRate(TALON_MAXRAMP);

	//Encoder starboardTalon
    starboardTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
    starboardTalon->ConfigEncoderCodesPerRev(TALON_COUNTS_PER_REV);
    starboardTalon->SelectProfileSlot(RobotMap::CLOSED_LOOP_GAIN);
	/*
	 * Sets control values for closed loop control.
	 * p Proportional constant,i Integration constant,d	Differential constant,f	Feedforward constant.
	 */
    starboardTalon->SetPID(TALON_PTERM_L, TALON_ITERM_L, TALON_DTERM_L, TALON_FTERM_L);
    starboardTalon->SetIzone(TALON_IZONE);
    starboardTalon->SetCloseLoopRampRate(TALON_MAXRAMP);

    portTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    portTalon->SetControlMode(CANSpeedController::kPercentVbus);
    portTalon->EnableControl();
    portTalon->Set(RobotMap::ALL_STOP);

    starboardTalon->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    starboardTalon->SetControlMode(CANSpeedController::kPercentVbus);
    starboardTalon->EnableControl();
    starboardTalon->Set(RobotMap::ALL_STOP);

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
	lumberJack->dLog(left + right);
	steamEngineRobotDrive->TankDrive(speedPort, speedStarboard);
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
