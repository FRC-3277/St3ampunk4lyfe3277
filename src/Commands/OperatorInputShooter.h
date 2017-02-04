#ifndef OperatorInputShooter_H
#define OperatorInputShooter_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputShooter : public Command {
private:
	double shooterSpeed = 0;

public:
	OperatorInputShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputShooter_H
