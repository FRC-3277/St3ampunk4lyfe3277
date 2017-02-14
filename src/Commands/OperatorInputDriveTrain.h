#ifndef OperatorInputDriveTrain_H
#define OperatorInputDriveTrain_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputDriveTrain :  public Command {
public:
	OperatorInputDriveTrain();

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<LumberJack> lumberJack;

	double Clamp(double joystickRawAxis);
};

#endif  // OperatorInputDriveTrain_H
