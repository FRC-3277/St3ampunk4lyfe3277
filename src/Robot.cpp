#include "Robot.h"
#include "LumberJack.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<BallPicker> Robot::ballPicker;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Auger> Robot::auger;
std::shared_ptr<VisionLumination> Robot::vision;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
	LumberJack logger;

	logger.iLog("RobotInit Test Log");
	RobotMap::init();
    driveTrain.reset(new DriveTrain());
    shooter.reset(new Shooter());
    ballPicker.reset(new BallPicker());
    climber.reset(new Climber());
    auger.reset(new Auger());
    vision.reset(new VisionLumination());
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	autonomousCommand.reset(new AutonomousCommand());
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

