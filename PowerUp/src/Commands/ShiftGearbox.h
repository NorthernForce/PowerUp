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

	ShiftGearbox(Gear setpoint) :
		m_gear(setpoint)
	{
		Requires(Robot::driveTrainShifter.get());
		Requires(Robot::driveTrain.get());
		strcpy(m_logMessage, setpoint == Gear::Low ? "Shift to low" : "Shift to high");
	}

	void Initialize() override
	{
		DriverStation::ReportWarning(m_logMessage);
		if ( m_gear ==  Gear::High )
			Robot::driveTrainShifter->ShiftHigh();
		else if (m_gear == Gear::Low)
			Robot::driveTrainShifter->ShiftLow();
	}

	bool IsFinished() override
	{
		return Robot::driveTrainShifter->IsShiftDone();
	}

	void End() override
	{
		Robot::driveTrainShifter->FinishShift();
	}

private:
	Gear m_gear;
	char m_logMessage[32];
};

#endif
