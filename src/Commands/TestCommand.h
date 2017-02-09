#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H
#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TestCommand: public Command {
public:
	TestCommand();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
