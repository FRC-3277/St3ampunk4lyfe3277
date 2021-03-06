#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

#include "Commands/AutonomousCommand.h"
#include "Subsystems/Auger.h"
#include "Subsystems/BallPicker.h"
#include "Subsystems/Climber.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/CameraSwap.h"
#include "Subsystems/Agitator.h"

#include "LumberJack.h"
#include <thread>

#include "OI.h"

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
    static std::shared_ptr<DriveTrain> driveTrain;
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<BallPicker> ballPicker;
    static std::shared_ptr<Climber> climber;
    static std::shared_ptr<Auger> auger;
    static std::shared_ptr<LumberJack> lumberJack;
    static std::shared_ptr<CameraSwap> cameraSwap;
    static std::shared_ptr<Agitator> agitator;

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
};
#endif
