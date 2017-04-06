#ifndef OperatorInputAgitator_H
#define OperatorInputAgitator_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputAgitator : public Command {
public:
	OperatorInputAgitator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputAgitator_H
