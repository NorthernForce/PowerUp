/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveElevator.h"
#include "subsystems/Elevator.h"
#include "Robot.h"

MoveElevator::MoveElevator(int speed) : frc::Command("MoveElevator"), m_speed(speed)
{
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void MoveElevator::Initialize()
{
  Robot::m_elevator->Move(m_speed);
}

// Called repeatedly when this Command is scheduled to run
void MoveElevator::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool MoveElevator::IsFinished() { return true; }

// Called once after isFinished returns true
void MoveElevator::End() { Robot::m_elevator->Move(0); }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveElevator::Interrupted() {}
