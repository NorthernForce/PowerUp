#ifndef AutonomousWait_H
#define AutonomousWait_H

#include "Commands/Command.h"

class AutonomousWait: public frc::Command {
public:
	AutonomousWait(int timeToWaitMs);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	int counter;
	int duration;
};

#endif  // AutonomousWait_H
