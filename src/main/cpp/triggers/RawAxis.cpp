/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/RawAxis.h"

RawAxis::RawAxis(std::shared_ptr<frc::GenericHID> joystick, int axis, double lowerLimit, double upperLimit)
  :  m_joystick(joystick), m_axis(axis), m_lowerLimit(lowerLimit), m_upperLimit(upperLimit) {}

bool RawAxis::Get()
{
    double joystickAxisInputValue = m_joystick->GetRawAxis(m_axis);
    if (joystickAxisInputValue > m_upperLimit || joystickAxisInputValue < m_lowerLimit)
         return true;
    else return false;
}