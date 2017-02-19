#ifndef AutonomousDriveForward_H
#define AutonomousDriveForward_H

#include "Commands/Subsystem.h"
#include "../Robot.h"


class AutonomousDriveForward : public Command {
public:
	AutonomousDriveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double wheelDiameter;
	double StarboardRevolutions;
	double PortRevolutions;
};

#endif  // AutonomousDriveForward_H
