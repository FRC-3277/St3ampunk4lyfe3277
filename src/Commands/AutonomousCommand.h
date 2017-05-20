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
	void AutonomousMoveForward(double tickGoal);
	void AutonomousMoveBackwards(double tickGoal);
	void AutonomousTurnRight(double turnGoal);
	void AutonomousTurnLeft(double turnGoal);
	void ResetPositions();
	void AutonomousShoota(int Color);
	void AutonomousAuger();
	void AutonomousAugerStop();
	void AutonomousReload(double timeDelay);
	void AutonomousAgitator();
	void AutonomousAgitatorStop();

private:
	std::shared_ptr<LumberJack> lumberJack;
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<float> elapsedTime;
	int numberSecondsElapsed = 0;

	double rightServoRed = 86;
	double leftServoRed = 86;

	double rightServoBlue = 90;
	double leftServoBlue = 90;

	bool hasRun = false;
	bool startShooting = false;
	bool stopAuto = false;
	double shooterSpeed = 0;
	double autoCommand = 0;
	double lastAutonomousValue = 0;
};

#endif
