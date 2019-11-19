/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/NudgeArm.h"
#include "frc/commands/Subsystem.h"
#include "Robot.h"

NudgeArm::NudgeArm(int distance) : Command("NudgeArm"), m_controller(nullptr), m_distance(distance)
{
  Requires(Robot::m_arm.get());
}

NudgeArm::NudgeArm(frc::GenericHID* controller) : m_controller(controller), m_distance(0) {}

// Called just before this Command runs the first time
void NudgeArm::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void NudgeArm::Execute()
{
  if (m_controller)
  {
	auto distance = m_controller->GetY() * 4;
	Robot::m_arm->NudgeArm(distance);
  } 
  else
  {
	Robot::m_arm->NudgeArm(m_distance);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool NudgeArm::IsFinished() { return false; }

// Called once after isFinished returns true
void NudgeArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void NudgeArm::Interrupted() {}
