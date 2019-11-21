/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "subsystems/DriveTrain.h"
#include "subsystems/DriveTrainShifter.h"
#include "subsystems/Elevator.h"
#include "subsystems/PCM.h"
#include "subsystems/Arm.h"
#include "subsystems/Gripper.h"
#include "subsystems/GripperIntake.h"

#include "OI.h"


class Robot : public frc::TimedRobot {
 public:

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  static std::shared_ptr<OI> m_oi;
  static std::shared_ptr<DriveTrain> m_driveTrain;
  // static std::shared_ptr<DriveTrainShifter> m_driveTrainShifter;
  static std::shared_ptr<Elevator> m_elevator;
  static std::shared_ptr<Arm> m_arm;
  static std::shared_ptr<PCM> m_pcm;
  static std::shared_ptr<Gripper> m_gripper;
  static std::shared_ptr<GripperIntake> m_gripperIntake;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::Command* m_autonomousCommand = nullptr;
  frc::SendableChooser<frc::Command*> m_chooser;
};
