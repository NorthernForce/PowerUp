/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class DriveTrainShifter : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  enum class Gear
  {
    Low, High
  };

  DriveTrainShifter();
  void InitDefaultCommand() override;
  void Periodic() override;
	void Shift(Gear gear);
	Gear GetGear();
	bool IsShiftDone() const;

 private:
  void BeginShift(const frc::DoubleSolenoid::Value value);

	std::shared_ptr<frc::DoubleSolenoid> m_shifter;
  std::shared_ptr<WPI_TalonSRX> m_primaryTalonRight;
  std::shared_ptr<WPI_TalonSRX> m_primaryTalonLeft;
	Gear m_currentGear;
	mutable int m_shiftCountdown;
};
