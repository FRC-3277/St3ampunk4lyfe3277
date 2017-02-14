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

//Climber
std::shared_ptr<CANTalon> RobotMap::climberTalon;

//Shooter
std::shared_ptr<CANTalon> RobotMap::shooterTalon;

//Vision Light Control
std::shared_ptr<Relay> RobotMap::visionSpike;

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
	augerSpike.reset(new Relay(HOPPA_AUGA_RELAY, Relay::kReverseOnly));
	lw->AddActuator("Auger", "Auger", augerSpike);

	//Climber
	climberTalon.reset(new CANTalon(CLIMBA_MOTOR));
	lw->AddActuator("Climber", "Climber", climberTalon);

	//Shooter
	shooterTalon.reset(new CANTalon(SHOOTA_MOTOR));
	lw->AddActuator("Shooter", "Shooter", shooterTalon);

	//Vision Light Control
	visionSpike.reset(new Relay(VISION_TRACKA_RELAY, Relay::kForwardOnly));
	lw->AddActuator("Vision", "Vision", visionSpike);
}
