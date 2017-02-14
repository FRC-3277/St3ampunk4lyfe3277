#ifndef OperatorInputBallPicker_H
#define OperatorInputBallPicker_H

#include "./LumberJack.h"
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

private:
	std::shared_ptr<LumberJack> lumberJack;

};

#endif  // OperatorInputBallPicker_H
