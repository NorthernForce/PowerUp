/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CreateSwitchFromCenter.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"

#include "WPILib.h"

#include "Commands/AutonomousCommands/SwitchFromCenter.h"

CreateSwitchFromCenter::CreateSwitchFromCenter() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CreateSwitchFromCenter::Initialize() {
	for (int time = 0; time <= 50; time++) {
		if (DriverStation::GetInstance().GetGameSpecificMessage() == "")
			break;
		Wait(0.01);
	}

	frc::CommandGroup* mode = new SwitchFromCenter();
	mode->Start();
}

// Called repeatedly when this Command is scheduled to run
void CreateSwitchFromCenter::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CreateSwitchFromCenter::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CreateSwitchFromCenter::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CreateSwitchFromCenter::Interrupted() {

}
