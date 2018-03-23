/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CreateScaleFromLeft.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"

#include "WPILib.h"

#include "Commands/AutonomousCommands/ScaleFromLeft.h"
#include "Commands/AutonomousCommands/SwitchFromLeft.h"
#include "Commands/AutonomousCommands/CrossAutoLine.h"

CreateScaleFromLeft::CreateScaleFromLeft() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CreateScaleFromLeft::Initialize() {
	for (int time = 0; time <= 50; time++) {
		if (DriverStation::GetInstance().GetGameSpecificMessage() == "")
			break;
		Wait(0.01);
	}

	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const FieldOrientation orientation(message);

	frc::CommandGroup* mode = new CrossAutoLine();
	if (orientation.GetScalePos() == Position::Left) {
		mode = new ScaleFromLeft();
	}
	else if (orientation.GetSwitchPos() == Position::Left) {
		mode = new SwitchFromLeft();
	}

	mode->Start();

}

// Called repeatedly when this Command is scheduled to run
void CreateScaleFromLeft::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CreateScaleFromLeft::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CreateScaleFromLeft::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CreateScaleFromLeft::Interrupted() {

}
