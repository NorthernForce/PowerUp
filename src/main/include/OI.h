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
  std::pair<double, double> GetDriveControls();
  enum class Xbox { 
    a_Button     = 1,
    b_Button     = 2, 
    x_Button     = 3, 
    y_Button     = 4, 
    rt_Bumper    = 5, 
    lt_Bumper    = 6, 
    rt_Trigger   = 7, 
    lt_Trigger   = 8 
  };
  
  enum class Joystick {
    /* handle buttons */
    trigger      = 1,
    button2      = 2,
    button3      = 3,
    button4      = 4,
    button5      = 5,
    /* base buttons */
    button6      = 6,
    button7      = 7,
    button8      = 8,
    button9      = 9,
    button10     =10,
    button11     =11
  };

 private:
  std::shared_ptr<frc::XboxController> m_driverController;
  std::shared_ptr<frc::Joystick> m_manipulatorJoystick;
};