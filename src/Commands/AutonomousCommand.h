#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H
#include "./LumberJack.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutonomousCommand: public Command {
public:
	AutonomousCommand();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void AutonomousMoveForward();

private:
	std::shared_ptr<LumberJack> lumberJack;

};

#endif
