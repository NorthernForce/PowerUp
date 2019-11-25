/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class GripperIntake : public frc::Subsystem {
 private:
    bool isRunning;
	std::shared_ptr<frc::Solenoid> m_gripperIntakeSolenoid;
	std::shared_ptr<WPI_TalonSRX> m_gripperIntakeTalon;
 public:
    enum class State { 
    Raised, Lowered
    };
    GripperIntake();
    void RunIntakeWheels();
    void StopIntakeWheels();
    void SetIntake(State state);
    bool IsDown();
    bool IsRunning();
    void InitDefaultCommand() override;
};
