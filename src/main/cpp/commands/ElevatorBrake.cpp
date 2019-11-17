/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorBrake.h"
#include "Robot.h"

ElevatorBrake::ElevatorBrake(State state) : Command("ElevatorBrake"), m_state(state)
{
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorBrake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorBrake::Execute()
{
  if (m_state == State::BrakeOn) Robot::m_elevator->ApplyBrake();
   else Robot::m_elevator->ReleaseBrake();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorBrake::IsFinished() { return true; }

// Called once after isFinished returns true
void ElevatorBrake::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorBrake::Interrupted() {}
