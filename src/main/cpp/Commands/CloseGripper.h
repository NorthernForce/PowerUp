#ifndef CLOSEGRIPPER_H
#define CLOSEGRIPPER_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class CloseGripper: public frc::TimedCommand {
public:

	CloseGripper() : frc::TimedCommand(timeToClose) {
		Requires(Robot::gripper.get());
	}

	void Initialize() override {
		Robot::gripper->SetClosed();
	}

private:
	constexpr static double timeToClose { 0.5 };
};

#endif
