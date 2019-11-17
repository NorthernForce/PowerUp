/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/TimedCommand.h>

class OpenGripper : public frc::TimedCommand {
 public:
  OpenGripper();
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  constexpr static double m_timeToOpen { 0.5 };
};
