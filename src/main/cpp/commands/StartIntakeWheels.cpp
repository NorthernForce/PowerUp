/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StartIntakeWheels.h"
#include "Robot.h"

StartIntakeWheels::StartIntakeWheels() : TimedCommand("StartIntakeWheels", m_duration)
{
  Requires(Robot::m_gripperIntake.get());
}

// Called just before this Command runs the first time
void StartIntakeWheels::Initialize()
{
  Robot::m_gripperIntake->RunIntakeWheels();
}

// Called repeatedly when this Command is scheduled to run
void StartIntakeWheels::Execute() {}

// Called once after command times out
void StartIntakeWheels::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StartIntakeWheels::Interrupted() {}
