#include "DriveTrainShifter.h"
#include "../RobotMap.h"
#include "../Robot.h"

using Gear = DriveTrainShifter::Gear;

DriveTrainShifter::DriveTrainShifter() :
	frc::Subsystem("DriveTrainShifter"),
	m_shifter(RobotMap::driveTrainShifterDS),
	m_left(RobotMap::driveTrainTalonSRX1, std::chrono::milliseconds(10)),
	m_right(RobotMap::driveTrainTalonSRX2, std::chrono::milliseconds(10))
{
	BeginShift(frc::DoubleSolenoid::Value::kForward);
}

void DriveTrainShifter::Periodic()
{
	if (m_shiftCountdown > 0) {
		m_shiftCountdown -= 1;
	}
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
		Robot::driveTrain->SetSafetyEnabled(false);
	}
}
Gear DriveTrainShifter::GetGear()
{
	return m_currentGear;
}

void DriveTrainShifter::BeginShift(const DoubleSolenoid::Value value)
{
	m_shifter->Set(value);
	m_shiftCountdown = 5;
}

bool DriveTrainShifter::IsShiftDone() const
{
	return m_shiftCountdown <= 0;
}
