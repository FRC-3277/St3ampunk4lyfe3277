#ifndef AutonomousDriveForward_H
#define AutonomousDriveForward_H

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "WPILib.h"


class AutonomousDriveForward : public Command {
public:
	AutonomousDriveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float TimeCount = 0, TimeStop = 0;
};

#endif  // AutonomousDriveForward_H
