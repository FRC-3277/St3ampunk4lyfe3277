#include "Robot.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<BallPicker> Robot::ballPicker;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Auger> Robot::auger;
std::shared_ptr<VisionLumination> Robot::vision;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<LumberJack> Robot::lumberJack;
std::shared_ptr<CameraSwap> Robot::cameraSwap;

void Robot::RobotInit() {
	RobotMap::init();
    driveTrain.reset(new DriveTrain());
    shooter.reset(new Shooter());
    ballPicker.reset(new BallPicker());
    climber.reset(new Climber());
    auger.reset(new Auger());
    vision.reset(new VisionLumination());
    //cameraSwap.reset(new CameraSwap());

    // This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	//Is required to be used twice in order to use both cameras
	//This is camera use switched via the driver station. No button mappings are used here.
	//To get to the code written for button mapped camera switching, go to the camera switching subsystem and associated command
	CameraServer::GetInstance()->StartAutomaticCapture();

	//Commented out due to lack of second camera
	//CameraServer::GetInstance()->StartAutomaticCapture();

	//Same as above. However, it might be able to specify which camera is called
	//cs::UsbCamera cam0 = CameraServer::GetInstance()->StartAutomaticCapture(0);
	//cs::UsbCamera cam1 = CameraServer::GetInstance()->StartAutomaticCapture(1);

	lumberJack.reset(new LumberJack());

	// instantiate the command used for the autonomous period
	autonomousCommand.reset(new AutonomousCommand());

	//std::thread visionThread(&CameraSwap::GetCamera, cameraSwap);
	//visionThread.detach();

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
	lumberJack->dLog("Begin Autonomous");
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	lumberJack->dLog("Begin Teleop");
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

