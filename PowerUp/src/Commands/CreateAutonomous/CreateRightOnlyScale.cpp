/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CreateRightOnlyScale.h"
#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"

#include "WPILib.h"

#include "../AutonomousCommands/ScaleFromRight.h"
#include "../AutonomousCommands/FarScaleFromRight.h"
#include "../AutonomousCommands/GotoOtherSide.h"

CreateRightOnlyScale::CreateRightOnlyScale() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CreateRightOnlyScale::Initialize() {
	for (int time = 0; time <= 50; time++) {
			if (DriverStation::GetInstance().GetGameSpecificMessage() == "")
				break;
			Wait(0.01);
		}

		const auto& ds = DriverStation::GetInstance();
		const auto& message = ds.GetGameSpecificMessage();
		const FieldOrientation orientation(message);

		frc::CommandGroup* autonomousCommand = nullptr;
		if (orientation.GetScalePos() == Position::Left) {
			autonomousCommand = new FarScaleFromRight();
		}
		else if (orientation.GetScalePos() == Position::Right) {
			autonomousCommand = new ScaleFromRight();
		}
		else {
			autonomousCommand = new GotoOtherSide();
		}

		if (autonomousCommand != nullptr)
			autonomousCommand->Start();


}

// Called repeatedly when this Command is scheduled to run
void CreateRightOnlyScale::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CreateRightOnlyScale::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CreateRightOnlyScale::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CreateRightOnlyScale::Interrupted() {

}
