#ifndef RobotClimb_H
#define RobotClimb_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class RobotClimb : public frc::Command {
public:
	RobotClimb();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // RobotClimb_H
