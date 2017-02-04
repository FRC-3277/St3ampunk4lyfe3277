// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "CANTalon.h"

//Drivetrain
std::shared_ptr<CANTalon> RobotMap::driveTrainPortTalon;
std::shared_ptr<CANTalon> RobotMap::driveTrainStarboardTalon;
std::shared_ptr<RobotDrive> RobotMap::driveTrainSteamEngineRobotDrive;

//Picker
std::shared_ptr<Relay> RobotMap::pickerSpike;

//Auger
std::shared_ptr<Relay> RobotMap::augerSpike;

//Climber
std::shared_ptr<CANTalon> RobotMap::climberTalon;

//Shooter
//TODO: Uses Talon

//Vision Light Control
//TODO: Uses Spike

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();
    //Drivetrain
    driveTrainPortTalon.reset(new CANTalon(PORT_PROPELLER_LEFT_MOTOR));
    lw->AddActuator("DriveTrain", "PortTalon", driveTrainPortTalon);
    
    driveTrainStarboardTalon.reset(new CANTalon(STARBOARD_PROPELLER_RIGHT_MOTOR));
    lw->AddActuator("DriveTrain", "StarboardTalon", driveTrainStarboardTalon);
    
    driveTrainSteamEngineRobotDrive.reset(new RobotDrive(driveTrainPortTalon, driveTrainStarboardTalon));
    
    driveTrainSteamEngineRobotDrive->SetSafetyEnabled(false);
	driveTrainSteamEngineRobotDrive->SetExpiration(0.5);
	driveTrainSteamEngineRobotDrive->SetSensitivity(0.5);
	driveTrainSteamEngineRobotDrive->SetMaxOutput(1.0);
	driveTrainSteamEngineRobotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	driveTrainSteamEngineRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

	//Picker
	pickerSpike.reset(new Relay(PICKA_RELAY, Relay::kForwardOnly));
	lw->AddActuator("Picker", "Picker", pickerSpike);

	//Auger
	augerSpike.reset(new Relay(HOPPA_AUGA_RELAY, Relay::kForwardOnly));
	lw->AddActuator("Auger", "Auger", augerSpike);

	//Climber
	climberTalon.reset(new CANTalon(CLIMBA_MOTOR));
	lw->AddActuator("Climber", "Climber", climberTalon);

	//Shooter

	//Vision Light Control
}
