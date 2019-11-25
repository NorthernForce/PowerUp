/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>

class Elevator : public frc::Subsystem {
 public:
    Elevator();
    void ConfigureCurrentLimits(int peakAmps, int continuousCurrent, int timeout);
    void SetHomePosition();
    void SetPosition(int setPosition);
    bool AtSetPosition();
    void ApplyBrake();
    void ReleaseBrake();
    void Nudge(int distance);
    void Move(double speed);
    void StartClimb();
    void EndClimb();
    void InitDefaultCommand() override;
 private:
    std::shared_ptr<WPI_TalonSRX> m_elevatorTalon;
    std::shared_ptr<frc::Solenoid> m_elevatorBrake;
    int m_setPosition;
    int m_PidID = 0;
    int m_slotID = 0;
    int m_noTimeoutMs = 0;
    int m_timeoutMs = 10;
    int m_defaultContinuousCurrent = 12;
    int m_defaultPeakAmps = 15;
 
};
