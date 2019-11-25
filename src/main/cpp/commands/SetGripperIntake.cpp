/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetGripperIntake.h"
#include "Robot.h"

SetGripperIntake::SetGripperIntake(GripperIntake::State intakeState) :
 TimedCommand("SetGripperIntake", m_duration) {
    Requires(Robot::m_gripperIntake.get());
    m_intakeState = intakeState;
}

// Called just before this Command runs the first time
void SetGripperIntake::Initialize() {
    Robot::m_gripperIntake->SetIntake(m_intakeState);
}

// Called repeatedly when this Command is scheduled to run
void SetGripperIntake::Execute() {}

// Called once after command times out
void SetGripperIntake::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetGripperIntake::Interrupted() {}
