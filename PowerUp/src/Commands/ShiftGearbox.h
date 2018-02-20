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
	ShiftGearbox(Gear setpoint)// : m_distance(distance)
	{
		Requires(Robot::driveTrainShifter.get());
	}

	void Execute() override
	{

//		if ( setpoint ==  Gear::High )
//			Robot::driveTrainShifter->ShiftHigh();
//		else if (setpoint == Gear::Low)
//			Robot::driveTrainShifter->ShiftLow();
	}

	bool IsFinished() override
	{
		return false;
	}

private:
};

#endif
