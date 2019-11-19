/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "commands/DriveWithJoystick.h"

#include "RobotMap.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain")
{
  m_primaryTalonLeft.reset(new WPI_TalonSRX (k_primaryTalonLeft_id));
  m_primaryTalonRight.reset(new WPI_TalonSRX (k_primaryTalonRight_id));
  m_followerTalon1Left.reset(new WPI_TalonSRX (k_followerTalon1Left_id));
  m_followerTalon1Right.reset(new WPI_TalonSRX (k_followerTalon1Right_id));
  m_followerTalon2Left.reset(new WPI_TalonSRX (k_followerTalon2Left_id));
  m_followerTalon2Right.reset(new WPI_TalonSRX (k_followerTalon2Right_id));

  m_primaryTalonLeft->ConfigFactoryDefault();
  m_primaryTalonRight->ConfigFactoryDefault();
  m_followerTalon1Left->ConfigFactoryDefault();
  m_followerTalon1Right->ConfigFactoryDefault();
  m_followerTalon2Left->ConfigFactoryDefault();
  m_followerTalon2Right->ConfigFactoryDefault();

  m_primaryTalonLeft->ConfigOpenloopRamp(0.5);   // Sets a basic ramp for motors of 0.5
  m_primaryTalonRight->ConfigOpenloopRamp(0.5);  // seconds so acceleration is not jerky

  m_followerTalon1Left->Follow(*m_primaryTalonLeft);
  m_followerTalon1Right->Follow(*m_primaryTalonRight);
  m_followerTalon2Left->Follow(*m_primaryTalonLeft);
   m_followerTalon2Left->SetInverted(true);               // motors 5 and 6 are "backwards" in the gearbox
  m_followerTalon2Right->Follow(*m_primaryTalonRight);
   m_followerTalon2Right->SetInverted(true);

  SetupShift();

  m_arcadeDrive.reset(new frc::DifferentialDrive(*m_primaryTalonLeft, *m_primaryTalonRight));

}

void DriveTrain::InitDefaultCommand() {
  
  SetDefaultCommand(new DriveWithJoystick());

}

void DriveTrain::Drive(double speed, double rotation)
{
  m_arcadeDrive->ArcadeDrive(speed, rotation);
}

void DriveTrain::SetSafetyEnabled(bool enabled)
{
	m_arcadeDrive->SetSafetyEnabled(enabled);
}

void DriveTrain::SetupShift()
{
  // Copies settings from private to public talons 
  // for use in DriveTrainShifter subsystem
  m_primaryTalonLeftShift = m_primaryTalonLeft;
  m_primaryTalonRightShift = m_primaryTalonRight;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
