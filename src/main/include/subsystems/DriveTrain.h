/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc/WPILib.h"
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

class DriveTrain : public frc::Subsystem {
 private:
  frc::DifferentialDrive *m_arcadeDrive;

 public:
  DriveTrain();
  void Drive(double speed, double rotation);
  void InitDefaultCommand() override;
};
