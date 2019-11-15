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

  k_primaryTalonLeft.reset(new WPI_TalonSRX (k_leftPrimaryTalon_id));
  k_primaryTalonRight.reset(new WPI_TalonSRX (k_rightPrimaryTalon_id));
  k_followerTalon1Left.reset(new WPI_TalonSRX (k_leftFollowerTalon1_id));
  k_followerTalon1Right.reset(new WPI_TalonSRX (k_rightFollowerTalon1_id));
  k_followerTalon2Left.reset(new WPI_TalonSRX (k_leftFollowerTalon2_id));
  k_followerTalon2Right.reset(new WPI_TalonSRX (k_rightFollowerTalon2_id));

  k_primaryTalonLeft->ConfigFactoryDefault();
  k_primaryTalonRight->ConfigFactoryDefault();
  k_followerTalon1Left->ConfigFactoryDefault();
  k_followerTalon1Right->ConfigFactoryDefault();
  k_followerTalon2Left->ConfigFactoryDefault();
  k_followerTalon2Right->ConfigFactoryDefault();

  k_primaryTalonLeft->ConfigOpenloopRamp(0.5);
  k_primaryTalonRight->ConfigOpenloopRamp(0.5);

  k_followerTalon1Left->Follow(*k_primaryTalonLeft);
  k_followerTalon1Right->Follow(*k_primaryTalonRight);
  k_followerTalon2Left->Follow(*k_primaryTalonLeft);
   k_followerTalon2Left->SetInverted(true);
  k_followerTalon2Right->Follow(*k_primaryTalonRight);
   k_followerTalon2Right->SetInverted(true);

  m_arcadeDrive = new frc::DifferentialDrive(*k_primaryTalonLeft, *k_primaryTalonRight);

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
