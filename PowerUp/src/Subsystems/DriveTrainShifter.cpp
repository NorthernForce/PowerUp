#include "DriveTrainShifter.h"
#include "../RobotMap.h"

using Gear = DriveTrainShifter::Gear;

DriveTrainShifter::DriveTrainShifter() :
	frc::Subsystem("DriveTrainShifter"),
	m_left(RobotMap::driveTrainTalonSRX1, std::chrono::milliseconds(10)),
	m_right(RobotMap::driveTrainTalonSRX2, std::chrono::milliseconds(10))
{
    shifter = RobotMap::driveTrainShifterDS;
	BeginShift(frc::DoubleSolenoid::Value::kForward);
}

void DriveTrainShifter::Periodic()
{
}

void DriveTrainShifter::Shift(Gear gear)
{
	if(gear != m_currentGear)
	{
		m_currentGear = gear;
		if(m_currentGear == Gear::High)
		{
			BeginShift(frc::DoubleSolenoid::Value::kReverse);
			RobotMap::driveTrainTalonSRX1->Set(0);
			RobotMap::driveTrainTalonSRX2->Set(0);
		}
		else
		{
			BeginShift(frc::DoubleSolenoid::Value::kForward);
			const auto speed1 = RobotMap::driveTrainTalonSRX1->GetSensorCollection().GetQuadratureVelocity();
			const auto speed2 = RobotMap::driveTrainTalonSRX2->GetSensorCollection().GetQuadratureVelocity();
			if(abs(speed1) + abs(speed2) > 100)
			{
				RobotMap::driveTrainTalonSRX1->Set(speed1 > 0 ? 1 : -1);
				RobotMap::driveTrainTalonSRX2->Set(speed2 > 0 ? 1 : -1);
			}
		}
	}
}
Gear DriveTrainShifter::GetGear()
{
	return m_currentGear;
}

void DriveTrainShifter::BeginShift(const DoubleSolenoid::Value value)
{
	DriverStation::ReportError("Shift called");
//	m_left.Start();
//	m_right.Start();
	shifter->Set(value);
	m_shiftCountdown = 10;
}

bool DriveTrainShifter::IsShiftDone() const
{
	return --m_shiftCountdown < 0;
}

void DriveTrainShifter::FinishShift()
{
//	m_left.Stop();
//	m_right.Stop();
}
