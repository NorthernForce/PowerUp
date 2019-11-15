/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/WPILib.h>

OI::OI()
{
  m_driverController.reset(new frc::XboxController(0));
}

void OI::arcDrive()
{
  double speed = m_driverController->GetY(frc::XboxController::JoystickHand::kLeftHand) * -1;
  double rotation = m_driverController->GetX(frc::XboxController::JoystickHand::kRightHand);
  Robot::m_driveTrain->Drive(speed, rotation);
  frc::DriverStation::ReportWarning("Speed: " + std::to_string(speed));
  frc::DriverStation::ReportWarning("Rotation: " + std::to_string(rotation));

}