/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CreateScaleFromRight.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"

#include "WPILib.h"

#include "Commands/AutonomousCommands/ScaleFromRight.h"
#include "Commands/AutonomousCommands/SwitchFromRight.h"
#include "Commands/AutonomousCommands/CrossAutoLine.h"

CreateScaleFromRight::CreateScaleFromRight() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CreateScaleFromRight::Initialize() {
	for (int time = 0; time <= 50; time++) {
		if (DriverStation::GetInstance().GetGameSpecificMessage() == "")
			break;
		Wait(0.01);
	}

	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const FieldOrientation orientation(message);

	frc::CommandGroup* autonomousCommand = nullptr;
	if (orientation.GetScalePos() == Position::Right) {
		autonomousCommand = new ScaleFromRight();
	}
	else if (orientation.GetSwitchPos() == Position::Right) {
		autonomousCommand = new SwitchFromRight();
	}
	else {
		autonomousCommand = new CrossAutoLine();
	}

	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

// Called repeatedly when this Command is scheduled to run
void CreateScaleFromRight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CreateScaleFromRight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CreateScaleFromRight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CreateScaleFromRight::Interrupted() {

}
