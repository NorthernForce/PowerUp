/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IMU.h"
#include "../RobotMap.h"

IMU::IMU() :
	Subsystem("IMU"),
	m_AngleRate(0),
	m_SetAngle(0),
	m_ahrs(RobotMap::ahrs)

{
//m_TurnControl = std::make_shared<frc::PIDController>(kP, kI, kD, m_ahrs.get(), this);
//	m_TurnControl->SetInputRange(-180.0, 180.0);
//	m_TurnControl->SetOutputRange(-1.0, 1.0);
//	m_TurnControl->SetAbsoluteTolerance(kToleranceDegrees);
//	m_TurnControl->SetContinuous(true);
}

void IMU::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}


double IMU::GetAngle()
{
	return m_ahrs->GetAngle();
}


void IMU::SetAngle(double degAngle)
{
	m_SetAngle = degAngle;
}

void IMU::SetAngleOffset(double degAngle)
{
	m_ahrs->ZeroYaw();
}


void IMU::TurnTo(double degAngle)
{
	m_SetAngle = degAngle;
	ExecuteTurn();
}


void IMU::EnableTurn()
{
	m_TurnControl->Enable();
}


void IMU::DisableTurn()
{
	m_TurnControl->Disable();
}


void IMU::ExecuteTurn()
{

}
