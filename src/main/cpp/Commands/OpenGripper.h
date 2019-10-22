#ifndef OPENGRIPPER_H
#define OPENGRIPPER_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class OpenGripper: public frc::TimedCommand {
public:

	OpenGripper() : frc::TimedCommand(timeToOpen) {
		Requires(Robot::gripper.get());
	}

	void Initialize() override {
		Robot::gripper->SetOpen();
	}

private:
	constexpr static double timeToOpen { 0.5 };
};

#endif
