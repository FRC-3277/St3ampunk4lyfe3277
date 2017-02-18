#ifndef OperatorInputCameraSwitch_H
#define OperatorInputCameraSwitch_H

#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class OperatorInputCameraSwitch : public Command {
public:
	OperatorInputCameraSwitch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorInputCameraSwitch_H
