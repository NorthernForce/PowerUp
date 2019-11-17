/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "frc/DriverStation.h"
#include "commands/ShiftGear.h"
#include "Robot.h"

ShiftGear::ShiftGear(Gear gear) : Command("ShiftGear"), m_gear(gear)
{
  Requires(Robot::m_driveTrainShifter.get());
		Requires(Robot::m_driveTrain.get());
		strcpy(m_logMessage, m_gear == Gear::Low ? "Shift to low" : "Shift to high");
}

// Called just before this Command runs the first time
void ShiftGear::Initialize()
{
  frc::DriverStation::ReportWarning(m_logMessage);
	Robot::m_driveTrainShifter->Shift(m_gear);
}

// Called repeatedly when this Command is scheduled to run
void ShiftGear::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ShiftGear::IsFinished() { return Robot::m_driveTrainShifter->IsShiftDone(); }

// Called once after isFinished returns true
void ShiftGear::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShiftGear::Interrupted() {}
