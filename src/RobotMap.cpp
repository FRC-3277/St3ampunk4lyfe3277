// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<SpeedController> RobotMap::motorSpeedController1;
std::shared_ptr<SpeedController> RobotMap::motorSpeedController2;
std::shared_ptr<RobotDrive> RobotMap::motorRobotDrive21;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    motorSpeedController1.reset(new Talon(0));
    lw->AddActuator("Motor", "Speed Controller 1", std::static_pointer_cast<Talon>(motorSpeedController1));
    
    motorSpeedController2.reset(new Talon(1));
    lw->AddActuator("Motor", "Speed Controller 2", std::static_pointer_cast<Talon>(motorSpeedController2));
    
    motorRobotDrive21.reset(new RobotDrive(motorSpeedController1, motorSpeedController2));
    
    motorRobotDrive21->SetSafetyEnabled(true);
        motorRobotDrive21->SetExpiration(0.1);
        motorRobotDrive21->SetSensitivity(0.5);
        motorRobotDrive21->SetMaxOutput(1.0);
        motorRobotDrive21->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
