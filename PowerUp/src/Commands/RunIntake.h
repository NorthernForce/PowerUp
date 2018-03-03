#ifndef RUNINTAKE_H
#define RUNINTAKE_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class RunIntake: public frc::Command {
public:
	RunIntake();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
};

#endif //RUNINTAKE_H
