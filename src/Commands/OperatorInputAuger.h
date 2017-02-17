#ifndef OperatorInputAuger_H
#define OperatorInputAuger_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputAuger : public Command {
public:
	OperatorInputAuger(int argDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<LumberJack> lumberJack;
	// 0 forward, 1 reverse
	int direction = 0;
};

#endif  // OperatorInputAuger_H
