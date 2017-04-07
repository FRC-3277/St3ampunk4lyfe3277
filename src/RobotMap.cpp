#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "CANTalon.h"

//Drivetrain
std::shared_ptr<CANTalon> RobotMap::driveTrainPortTalon;
std::shared_ptr<CANTalon> RobotMap::driveTrainStarboardTalon;
std::shared_ptr<RobotDrive> RobotMap::driveTrainSteamEngineRobotDrive;

//Picker
std::shared_ptr<CANTalon> RobotMap::pickerTalon;

//Auger
std::shared_ptr<Relay> RobotMap::augerSpike;
std::shared_ptr<CANTalon> RobotMap::augerTalon;

//Climber
std::shared_ptr<CANTalon> RobotMap::climberTalon;

//Shooter
std::shared_ptr<CANTalon> RobotMap::shooterTalon;

//Agitator
std::shared_ptr<Relay> RobotMap::agitatorSpike;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();
    //Drivetrain
    driveTrainPortTalon.reset(new CANTalon(PORT_PROPELLER_LEFT_MOTOR));
    lw->AddActuator("DriveTrain", "PortTalon", driveTrainPortTalon);
    
    driveTrainStarboardTalon.reset(new CANTalon(STARBOARD_PROPELLER_RIGHT_MOTOR));
    lw->AddActuator("DriveTrain", "StarboardTalon", driveTrainStarboardTalon);
    
    driveTrainSteamEngineRobotDrive.reset(new RobotDrive(driveTrainPortTalon, driveTrainStarboardTalon));

	//Picker
	pickerTalon.reset(new CANTalon(PICKA_MOTOR));
	lw->AddActuator("Picker", "Picker", pickerTalon);

	//Auger
	//Reverse travel is toward the shoota.
	if(AUGER_TALON_MOTOR_ENABLED)
	{
	augerTalon.reset(new CANTalon(HOPPA_AUGA_TALON));
	lw->AddActuator("Auger", "Auger", augerTalon);
	}
	else
	{
	augerSpike.reset(new Relay(HOPPA_AUGA_RELAY, Relay::kBothDirections));
	lw->AddActuator("Auger", "Auger", augerSpike);
	}


	//Climber
	climberTalon.reset(new CANTalon(CLIMBA_MOTOR));
	lw->AddActuator("Climber", "Climber", climberTalon);

	//Shooter
	shooterTalon.reset(new CANTalon(SHOOTA_MOTOR));
	lw->AddActuator("Shooter", "Shooter", shooterTalon);

	//Agitator
	agitatorSpike.reset(new Relay(AGITATA_SPIKE, Relay::kForwardOnly));
}
