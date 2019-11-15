/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "commands/RaiseElevator.h"

Elevator::Elevator() : Subsystem("Elevator")
{
  m_elevatorTalon.reset(new WPI_TalonSRX(9));
  m_elevatorTalon->ConfigFactoryDefault();
  m_elevatorTalon->SetInverted(true);
  m_elevatorTalon->ConfigOpenloopRamp(0.2);
}

void Elevator::InitDefaultCommand() {}

void Elevator::Move(double speed)
{
  if (speed < -1) speed = -1;
   else if (speed > 1) speed = 1;

  m_elevatorTalon->Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
