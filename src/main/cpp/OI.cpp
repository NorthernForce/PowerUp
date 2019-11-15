/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/WPILib.h>
#include <frc/buttons/JoystickButton.h>
#include "commands/RaiseElevator.h"
#include "commands/LowerElevator.h"

namespace {
	void WhenPressed(const std::shared_ptr<frc::GenericHID>& joystick, int button, frc::Command* command) {
		auto joystickButton = new frc::JoystickButton(joystick.get(), button);
		joystickButton->WhenPressed(command);
	}

	void WhenReleased(const std::shared_ptr<frc::GenericHID>& joystick, int button, frc::Command* command) {
		auto joystickButton = new frc::JoystickButton(joystick.get(), button);
		joystickButton->WhenReleased(command);
	}

	void WhileHeld(const std::shared_ptr<frc::GenericHID>& joystick, int button, frc::Command* command) {
		auto joystickButton = new frc::JoystickButton(joystick.get(), button);
		joystickButton->WhileHeld(command);
	}
}

OI::OI()
{
  m_driverController.reset(new frc::XboxController(0));
  m_manipulatorController.reset(new frc::XboxController(1));
  frc::SmartDashboard::PutNumber("Drive Speed", 1);
  /* Commented out elevator controls for safety because encoder not setup yet */
  /* TODO: change to Y-axis of a thumbstick or use presets                    */
  // WhileHeld(m_manipulatorController, 1, new LowerElevator());
  // WhileHeld(m_manipulatorController, 4, new RaiseElevator());
}

void OI::arcDrive()
{
  double speed = m_driverController->GetY(frc::XboxController::JoystickHand::kLeftHand) * -1;
  double rotation = m_driverController->GetX(frc::XboxController::JoystickHand::kRightHand);
  double driveMultiplier = frc::SmartDashboard::GetNumber("Drive Speed", 1);

  if (driveMultiplier < 0) driveMultiplier = 0;
   else if (driveMultiplier > 1) driveMultiplier = 1;

  Robot::m_driveTrain->Drive(speed * driveMultiplier, rotation * driveMultiplier);
}