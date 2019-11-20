/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/buttons/Trigger.h>

class ComboControl : public frc::Trigger {
 public:
  ComboControl(frc::Trigger* control1, frc::Trigger* control2);
  bool Get() override;
 private:
  frc::Trigger *m_control1;
  frc::Trigger *m_control2;
};
