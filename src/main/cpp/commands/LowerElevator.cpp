/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LowerElevator.h"
#include "subsystems/Elevator.h"
#include "Robot.h"

LowerElevator::LowerElevator() {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void LowerElevator::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LowerElevator::Execute()
{
  Robot::m_elevator->Move(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool LowerElevator::IsFinished() { return false; }

// Called once after isFinished returns true
void LowerElevator::End()
{
  Robot::m_elevator->Move(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerElevator::Interrupted() {}
