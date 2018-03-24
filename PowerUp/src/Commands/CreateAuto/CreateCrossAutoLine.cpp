/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CreateCrossAutoLine.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"

#include "WPILib.h"

#include "Commands/AutonomousCommands/ScaleFromLeft.h"
#include "Commands/AutonomousCommands/SwitchFromLeft.h"
#include "Commands/AutonomousCommands/CrossAutoLine.h"

CreateCrossAutoLine::CreateCrossAutoLine() {

}

void CreateCrossAutoLine::Initialize() {
	frc::Command* autonomousCommand = new CrossAutoLine();
	autonomousCommand->Start();
}

// Called repeatedly when this Command is scheduled to run
void CreateCrossAutoLine::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CreateCrossAutoLine::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CreateCrossAutoLine::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CreateCrossAutoLine::Interrupted() {

}

