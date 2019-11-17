/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RobotClimb.h"
#include "Robot.h"

RobotClimb::RobotClimb() : Command("RaiseElevator")
{
  Requires(Robot::m_elevator.get());
  Requires(Robot::m_arm.get());
}

// Called just before this Command runs the first time
void RobotClimb::Initialize()
{
  Robot::m_elevator->StartClimb();
  Robot::m_arm->ReducePowerForClimb();
}

// Called repeatedly when this Command is scheduled to run
void RobotClimb::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool RobotClimb::IsFinished() { return false; }

// Called once after isFinished returns true
void RobotClimb::End()
{
  Robot::m_elevator->EndClimb();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RobotClimb::Interrupted()
{
  Robot::m_elevator->EndClimb();
}
