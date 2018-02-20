#ifndef SHIFTGEARBOX_H
#define SHIFTGEARBOX_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class ShiftGearbox : public frc::Command
{
public:
	enum class Gear {
		Low,
		High
	};
	ShiftGearbox(Gear setpoint) : m_setpoint(setpoint)
	{
		Requires(Robot::driveTrainShifter.get());
	}

	void Execute() override
	{

		if ( m_setpoint ==  Gear::High )
			Robot::driveTrainShifter->ShiftHigh();
		else if (m_setpoint == Gear::Low)
			Robot::driveTrainShifter->ShiftLow();
	}

	bool IsFinished() override
	{
		return false;
	}

private:
	Gear m_setpoint;
};

#endif
