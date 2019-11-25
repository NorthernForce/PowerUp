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
    enum class Xbox;
    enum class XboxAxis;
    enum class XboxPOV;
    enum class Joystick;
    enum class JoystickAxis;
    std::pair<double, double> GetDriveControls();
 private:
    std::shared_ptr<frc::XboxController> m_driverController;
    std::shared_ptr<frc::Joystick> m_manipulatorJoystick;
};

enum class OI::Xbox { 
    A_button     = 1,
    B_button     = 2, 
    X_button     = 3, 
    Y_button     = 4, 
    rt_bumper    = 5, 
    lt_bumper    = 6, 
    menu_button  = 7, 
    view_button  = 8,
    lt_stick     = 9,
    rt_stick     = 10
};

enum class OI::XboxAxis {
    lt_X,
    lt_Y,
    lt_Trigger,
    rt_Trigger,
    rt_X,
    rt_Y
};

enum class OI::XboxPOV {
    up           = 0,
    up_right     = 45,
    right        = 90,
    down_right   = 135,
    down         = 180,
    down_left    = 225,
    left         = 270,
    left_up      = 315
};

enum class OI::Joystick {
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
    button11     =11,
};

enum class OI::JoystickAxis  {
    X,
    Y,
    Wheel
};