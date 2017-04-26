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
	double shooterSpeed = 0;

	double augerSpeedScale = 0.2;
	double augerBaseSpeed = 0.2;
	double augerMinSpeed = augerBaseSpeed;
	double augerMaxSpeed = augerMinSpeed + augerSpeedScale;
};

#endif  // OperatorInputAuger_H
