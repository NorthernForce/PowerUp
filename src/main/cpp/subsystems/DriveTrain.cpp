/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "commands/DriveWithJoystick.h"

#include "RobotMap.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {

  Drive::m_primaryTalonLeft.reset(new WPI_TalonSRX (k_leftPrimaryTalon_id));
  Drive::m_primaryTalonRight.reset(new WPI_TalonSRX (k_rightPrimaryTalon_id));
  Drive::m_followerTalon1Left.reset(new WPI_TalonSRX (k_leftFollowerTalon1_id));
  Drive::m_followerTalon1Right.reset(new WPI_TalonSRX (k_rightFollowerTalon1_id));
  Drive::m_followerTalon2Left.reset(new WPI_TalonSRX (k_leftFollowerTalon2_id));
  Drive::m_followerTalon2Right.reset(new WPI_TalonSRX (k_rightFollowerTalon2_id));

  Drive::m_primaryTalonLeft->ConfigOpenloopRamp(0.5);
  Drive::m_primaryTalonRight->ConfigOpenloopRamp(0.5);

  Drive::m_primaryTalonLeft->ConfigFactoryDefault();
  Drive::m_primaryTalonRight->ConfigFactoryDefault();
  Drive::m_followerTalon1Left->ConfigFactoryDefault();
  Drive::m_followerTalon1Right->ConfigFactoryDefault();
  Drive::m_followerTalon2Left->ConfigFactoryDefault();
  Drive::m_followerTalon2Right->ConfigFactoryDefault();

  Drive::m_followerTalon1Left->Follow(*Drive::m_primaryTalonLeft);
  Drive::m_followerTalon1Right->Follow(*Drive::m_primaryTalonRight);
  Drive::m_followerTalon2Left->Follow(*Drive::m_primaryTalonLeft);
   Drive::m_followerTalon2Left->SetInverted(true);
  Drive::m_followerTalon2Right->Follow(*Drive::m_primaryTalonRight);
   Drive::m_followerTalon2Right->SetInverted(true);

  m_arcadeDrive = new frc::DifferentialDrive(*Drive::m_primaryTalonLeft, *Drive::m_primaryTalonRight);

}

void DriveTrain::InitDefaultCommand() {
  
  SetDefaultCommand(new DriveWithJoystick());

}

void DriveTrain::Drive(double speed, double rotation)
{
  m_arcadeDrive->ArcadeDrive(speed, rotation);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
