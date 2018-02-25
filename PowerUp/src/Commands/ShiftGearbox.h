#ifndef SHIFTGEARBOX_H
#define SHIFTGEARBOX_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class ShiftGearbox : public frc::Command
{
public:
	using Gear = DriveTrainShifter::Gear;

	ShiftGearbox(Gear gear) :
		m_gear(gear)
	{
		Requires(Robot::driveTrainShifter.get());
		Requires(Robot::driveTrain.get());
		strcpy(m_logMessage, m_gear == Gear::Low ? "Shift to low" : "Shift to high");
	}

	void Initialize() override
	{
		DriverStation::ReportWarning(m_logMessage);
//		Robot::driveTrainShifter->Shift(m_gear);
	}

	bool IsFinished() override
	{
		return true;
//		return Robot::driveTrainShifter->IsShiftDone();
	}

	void End() override
	{
//		Robot::driveTrainShifter->FinishShift();
	}

private:
	Gear m_gear;
	char m_logMessage[32];
};

#endif
