#ifndef NUDGEARM_H
#define NUDGEARM_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class NudgeArm : public frc::Command
{
public:
	NudgeArm(int distance) : m_distance(distance)
	{
		Requires(Robot::arm.get());
	}

	void Execute() override
	{
		Robot::arm->Nudge(m_distance);
	}

	bool IsFinished() override
	{
		return false;
	}

private:
	const int m_distance;
};

#endif
