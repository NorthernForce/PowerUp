// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #include "CreateLeftOnlyScale.h"
// #include "DriverStation.h"
// #include "Utilities/FieldOrientation.h"

// #include "WPILib.h"

// #include "../AutonomousCommands/ScaleFromLeft.h"
// #include "../AutonomousCommands/FarScaleFromLeft.h"
// #include "../AutonomousCommands/GotoOtherSide.h"

// CreateLeftOnlyScale::CreateLeftOnlyScale() {
// 	// Use Requires() here to declare subsystem dependencies
// 	// eg. Requires(Robot::chassis.get());
// }

// // Called just before this Command runs the first time
// void CreateLeftOnlyScale::Initialize() {
// 	for (int time = 0; time <= 50; time++) {
// 			if (frc::DriverStation::GetInstance().GetGameSpecificMessage() == "")
// 				break;
// 			frc::Wait(0.01);
// 		}

// 		const auto& ds = frc::DriverStation::GetInstance();
// 		const auto& message = ds.GetGameSpecificMessage();
// 		const FieldOrientation orientation(message);

// 		frc::CommandGroup* autonomousCommand = nullptr;
// 		if (orientation.GetScalePos() == Position::Left) {
// 			autonomousCommand = new ScaleFromLeft();
// 		}
// 		else if (orientation.GetScalePos() == Position::Right) {
// 			printf("hey im here");
// 			autonomousCommand = new FarScaleFromLeft();
// 		}
// 		else {
// 			autonomousCommand = new GotoOtherSide();
// 		}

// 		if (autonomousCommand != nullptr)
// 			autonomousCommand->Start();


// }

// // Called repeatedly when this Command is scheduled to run
// void CreateLeftOnlyScale::Execute() {

// }

// // Make this return true when this Command no longer needs to run execute()
// bool CreateLeftOnlyScale::IsFinished() {
// 	return false;
// }

// // Called once after isFinished returns true
// void CreateLeftOnlyScale::End() {

// }

// // Called when another command which requires one or more of the same
// // subsystems is scheduled to run
// void CreateLeftOnlyScale::Interrupted() {

// }
