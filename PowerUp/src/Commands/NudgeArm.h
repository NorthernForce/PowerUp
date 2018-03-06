#ifndef NUDGEARM_H
#define NUDGEARM_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class NudgeArm : public frc::Command {
public:
	NudgeArm(int distance) : m_controller(nullptr), m_distance(distance) {
		Requires(Robot::arm.get());
	}

	NudgeArm(GenericHID* controller) : m_controller(controller), m_distance(0) {

	}

	void Execute() override {
		if (m_controller) {
			auto distance = m_controller->GetY() * 4;
			Robot::arm->NudgeArm(distance);
		} else {
			Robot::arm->NudgeArm(m_distance);
		}
	}

	bool IsFinished() override {
		return false;
	}

private:
	GenericHID* const m_controller;
	const int m_distance;
};

#endif
