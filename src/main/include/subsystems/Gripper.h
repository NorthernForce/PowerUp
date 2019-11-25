/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>

class Gripper : public frc::Subsystem {
 private:
    enum class State {
      Open, Closed
    };
    State m_gripperState;
    std::shared_ptr<frc::Solenoid> m_gripperSolenoid;
 public:
    Gripper();
    void SetOpen();
    void SetClosed();
    bool isClosed() const { return m_gripperState == State::Closed; }
    void InitDefaultCommand() override;
};
