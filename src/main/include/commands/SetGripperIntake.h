/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/TimedCommand.h>
#include "subsystems/GripperIntake.h"

class SetGripperIntake : public frc::TimedCommand {
 public:
  SetGripperIntake(GripperIntake::State intakeState);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  GripperIntake::State m_intakeState;
	constexpr static double m_duration { 1.0 };
};
