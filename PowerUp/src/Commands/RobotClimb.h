#ifndef ElevatorClimb_H
#define ElevatorClimb_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class ElevatorClimb : public frc::Command {
public:
	ElevatorClimb();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // ElevatorClimb_H
