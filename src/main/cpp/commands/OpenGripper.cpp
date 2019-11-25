/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/OpenGripper.h"
#include "Robot.h"

OpenGripper::OpenGripper() :
 TimedCommand("OpenGripper", m_timeToOpen) {
    Requires(Robot::m_gripper.get());
}

// Called just before this Command runs the first time
void OpenGripper::Initialize() {
    Robot::m_gripper->SetOpen();
}

// Called repeatedly when this Command is scheduled to run
void OpenGripper::Execute() {}

// Called once after command times out
void OpenGripper::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OpenGripper::Interrupted() {}
