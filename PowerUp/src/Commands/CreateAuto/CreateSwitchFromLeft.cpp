/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CreateSwitchFromLeft.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"

#include "WPILib.h"

#include "Commands/AutonomousCommands/SwitchFromLeft.h"
#include "Commands/AutonomousCommands/ScaleFromLeft.h"
#include "Commands/AutonomousCommands/CrossAutoLine.h"

CreateSwitchFromLeft::CreateSwitchFromLeft() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CreateSwitchFromLeft::Initialize() {
	for (int time = 0; time <= 50; time++) {
		if (DriverStation::GetInstance().GetGameSpecificMessage() == "")
			break;
		Wait(0.01);
	}

	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const FieldOrientation orientation(message);

	frc::CommandGroup* autonomousCommand = nullptr;
	if (orientation.GetSwitchPos() == Position::Left) {
		autonomousCommand = new SwitchFromLeft();
	}
	else if (orientation.GetScalePos() == Position::Left) {
		autonomousCommand = new ScaleFromLeft();
	}
	else {
		autonomousCommand = new CrossAutoLine();
	}

	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

// Called repeatedly when this Command is scheduled to run
void CreateSwitchFromLeft::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CreateSwitchFromLeft::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CreateSwitchFromLeft::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CreateSwitchFromLeft::Interrupted() {

}
