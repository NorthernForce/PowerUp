/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Gripper.h"
#include "RobotMap.h"

Gripper::Gripper() : Subsystem("Gripper")
{
  m_gripperSolenoid.reset(new frc::Solenoid(RobotMap::PCM::k_gripperSolenoid_id));
  m_gripperState = State::Closed;
}

void Gripper::SetOpen()
{
  m_gripperSolenoid->Set(true);
  m_gripperState = State::Open;
}

void Gripper::SetClosed()
{
  m_gripperSolenoid->Set(false);
  m_gripperState = State::Closed;
}

void Gripper::InitDefaultCommand() {}