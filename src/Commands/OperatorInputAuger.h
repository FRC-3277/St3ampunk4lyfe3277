#ifndef OperatorInputAuger_H
#define OperatorInputAuger_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputAuger : public Command {
public:
	OperatorInputAuger();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputAuger_H
