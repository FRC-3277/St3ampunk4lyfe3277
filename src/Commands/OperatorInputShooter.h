#ifndef OperatorInputShooter_H
#define OperatorInputShooter_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputShooter : public Command {
private:
	double shooterSpeed = 0;
	double shooterServoPositionLeft = 0;
	double shooterServoPositionRight = 0;
	std::shared_ptr<LumberJack> lumberJack;

public:
	OperatorInputShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputShooter_H
