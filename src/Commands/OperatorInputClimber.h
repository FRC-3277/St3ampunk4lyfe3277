#ifndef OperatorInputClimber_H
#define OperatorInputClimber_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputClimber :  public Command {
public:
	OperatorInputClimber();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputClimber_H
