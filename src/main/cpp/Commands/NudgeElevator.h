#ifndef NUDGEELEVATOR_H
#define NUDGEELEVATOR_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class NudgeElevator : public frc::Command {
public:
	NudgeElevator(int distance) : m_distance(distance) {
		Requires(Robot::elevator.get());
	}

	void Execute() override {
		Robot::elevator->Nudge(m_distance);
	}

	bool IsFinished() override {
		return false;
	}

private:
	const int m_distance;
};

#endif
