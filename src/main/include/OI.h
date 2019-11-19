/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/XboxController.h>
#include <frc/Joystick.h>

class OI {
 public:
  OI();
  std::pair<double, double> driveControls();
  enum class XboxButtons { 
    a_Button      = 1,
    b_Button      = 2, 
    x_Button      = 3, 
    y_Button      = 4, 
    rt_Bumper     = 5, 
    lt_Bumper     = 6, 
    rt_Trigger    = 7, 
    lt_Trigger    = 8 
  };
  
  enum class JoystickButtons { 
    Trigger       = 9 
  };

 private:
  std::shared_ptr<frc::XboxController> m_driverController;
  std::shared_ptr<frc::Joystick> m_manipulatorJoystick;
};