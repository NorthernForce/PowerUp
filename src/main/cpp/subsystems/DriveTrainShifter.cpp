/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainShifter.h"
#include "Robot.h"
#include "RobotMap.h"

using Gear = DriveTrainShifter::Gear;

// Shared pointers that inherit all properties of primary talons 
// (in the DriveTrain subsystem) but these are obviously used for shifting
std::shared_ptr<WPI_TalonSRX> DriveTrain::m_primaryTalonLeftShift;
std::shared_ptr<WPI_TalonSRX> DriveTrain::m_primaryTalonRightShift;

DriveTrainShifter::DriveTrainShifter() :
    Subsystem("DriveTrainShifter"),
    m_primaryTalonLeft(DriveTrain::m_primaryTalonLeftShift),
    m_primaryTalonRight(DriveTrain::m_primaryTalonRightShift)
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
			m_primaryTalonLeft->Set(0);
			m_primaryTalonRight->Set(0);
		}
		else
		{
			BeginShift(frc::DoubleSolenoid::Value::kForward);
			const auto speed1 = m_primaryTalonLeft->GetSensorCollection().GetQuadratureVelocity();
			const auto speed2 = m_primaryTalonRight->GetSensorCollection().GetQuadratureVelocity();
			if(abs(speed1) + abs(speed2) > 100)
			{
				m_primaryTalonLeft->Set((speed1 > 0) ? 1 : -1);
				m_primaryTalonRight->Set((speed2 > 0) ? 1 : -1);
			}
		}
		Robot::m_driveTrain->SetSafetyEnabled(false);
	}
}

Gear DriveTrainShifter::GetGear()
{
	return m_currentGear;
}

void DriveTrainShifter::BeginShift(const frc::DoubleSolenoid::Value value)
{
	m_shifter->Set(value);
	m_shiftCountdown = 5;
}

bool DriveTrainShifter::IsShiftDone() const
{
	return m_shiftCountdown <= 0;
}


void DriveTrainShifter::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
