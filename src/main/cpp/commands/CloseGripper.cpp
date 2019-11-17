/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CloseGripper.h"
#include "Robot.h"

CloseGripper::CloseGripper() : TimedCommand("CloseGripper", timeToClose)
{
  Requires(Robot::m_gripper.get());
}

// Called just before this Command runs the first time
void CloseGripper::Initialize() { Robot::m_gripper->SetClosed(); }

// Called repeatedly when this Command is scheduled to run
void CloseGripper::Execute() {}

// Called once after command times out
void CloseGripper::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CloseGripper::Interrupted() {}
