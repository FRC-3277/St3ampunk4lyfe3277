#ifndef OperatorInputClimber_H
#define OperatorInputClimber_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "../OI.h"

class OperatorInputClimber :  public Command {
public:
	OperatorInputClimber();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<LumberJack> lumberJack;
};

#endif  // OperatorInputClimber_H
