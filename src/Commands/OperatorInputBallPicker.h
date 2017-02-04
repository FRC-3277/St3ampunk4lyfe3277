#ifndef OperatorInputBallPicker_H
#define OperatorInputBallPicker_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputBallPicker : public Command {
public:
	OperatorInputBallPicker();

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputBallPicker_H
