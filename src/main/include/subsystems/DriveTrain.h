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
 public:
    DriveTrain();
    void InitDefaultCommand() override;
    void FactoryDefaultTalons();
    void Drive(double speed, double rotation);
    void SetSafetyEnabled(bool enabled);
    static std::shared_ptr<WPI_TalonSRX> m_primaryTalonLeft;
    static std::shared_ptr<WPI_TalonSRX> m_primaryTalonRight;
 private:
    std::shared_ptr<frc::DifferentialDrive> m_arcadeDrive;
    std::shared_ptr<WPI_TalonSRX> m_followerTalon1Left;
    std::shared_ptr<WPI_TalonSRX> m_followerTalon1Right;
    std::shared_ptr<WPI_TalonSRX> m_followerTalon2Left;
    std::shared_ptr<WPI_TalonSRX> m_followerTalon2Right;
 
};
