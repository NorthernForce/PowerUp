/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetElevatorHomePosition.h"
#include "Robot.h"

SetElevatorHomePosition::SetElevatorHomePosition() : Command("SetElevatorHomePosition")
{
  SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void SetElevatorHomePosition::Initialize()
{
  Robot::m_elevator->SetHomePosition();
}

// Called repeatedly when this Command is scheduled to run
void SetElevatorHomePosition::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetElevatorHomePosition::IsFinished() { return true; }

// Called once after isFinished returns true
void SetElevatorHomePosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetElevatorHomePosition::Interrupted() {}
