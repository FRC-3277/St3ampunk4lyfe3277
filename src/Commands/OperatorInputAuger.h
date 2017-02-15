#ifndef OperatorInputAuger_H
#define OperatorInputAuger_H

#include "./LumberJack.h"
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

private:
	std::shared_ptr<LumberJack> lumberJack;
};

#endif  // OperatorInputAuger_H
