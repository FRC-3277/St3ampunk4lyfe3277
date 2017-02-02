#ifndef OperatorInputDriveTrain_H
#define OperatorInputDriveTrain_H

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
	static std::shared_ptr<bool> isOperatorControlOperatorInput;
};

#endif  // OperatorInputDriveTrain_H
