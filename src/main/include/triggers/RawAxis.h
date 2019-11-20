/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/buttons/Trigger.h>
#include <frc/GenericHID.h>

class RawAxis : public frc::Trigger {
 public:
  RawAxis(std::shared_ptr<frc::GenericHID> joystick, int axis, double lowerLimit=0.5, double upperLimit=1.0);
  bool Get() override;
 private:
  std::shared_ptr<frc::GenericHID> m_joystick;
  int m_axis;
  double m_lowerLimit;
  double m_upperLimit;
};
