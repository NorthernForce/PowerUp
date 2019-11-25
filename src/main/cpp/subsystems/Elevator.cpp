/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include <frc/DriverStation.h>

#include "RobotMap.h"

Elevator::Elevator() :
 Subsystem("Elevator") {
    m_elevatorTalon.reset(new WPI_TalonSRX (RobotMap::ArmAssemblyTalons::k_elevatorTalon_id));
    m_elevatorTalon->ConfigFactoryDefault();
    m_elevatorTalon->SetInverted(true);
    m_elevatorTalon->ConfigOpenloopRamp(0.2);
    ConfigureCurrentLimits(m_defaultPeakAmps, m_defaultContinuousCurrent, m_timeoutMs);
    m_elevatorTalon->SelectProfileSlot(m_slotID, m_PidID);
    m_elevatorTalon->SetName("Elevator", "Elevator");
	m_elevatorTalon->SetNeutralMode(NeutralMode::Brake);
    SetHomePosition();
    // ApplyBrake();
}

void Elevator::ConfigureCurrentLimits(int peakAmps, int continuousCurrent, int timeout) {
	m_elevatorTalon->ConfigPeakCurrentLimit(peakAmps, timeout);
    m_elevatorTalon->ConfigContinuousCurrentLimit(continuousCurrent, timeout);
    m_elevatorTalon->ConfigPeakCurrentDuration(100, timeout);
    m_elevatorTalon->EnableCurrentLimit(true);
}

void Elevator::SetHomePosition() {
	frc::DriverStation::ReportWarning("Elevator home position initial reset");
	m_setPosition = 0;
	m_elevatorTalon->SetSelectedSensorPosition(m_setPosition, m_PidID, m_timeoutMs);
	m_elevatorTalon->Set(ControlMode::MotionMagic, m_setPosition);
}

void Elevator::SetPosition(int setPosition) {
    ReleaseBrake();
    m_setPosition = setPosition;
    m_elevatorTalon->Set(ControlMode::MotionMagic, m_setPosition);
}

bool Elevator::AtSetPosition() {
    return m_elevatorTalon->GetClosedLoopError(m_PidID) < 250;
}

void Elevator::ApplyBrake() {
    m_elevatorBrake->Set(false);
}

void Elevator::ReleaseBrake() {
    m_elevatorBrake->Set(true);
}

void Elevator::Nudge(int distance) {
	ReleaseBrake();
	m_setPosition = m_setPosition + distance;
	m_elevatorTalon->Set(ControlMode::MotionMagic, m_setPosition);
}

void Elevator::Move(double speed) {
    if (speed < -1) speed = -1;
    else if (speed > 1) speed = 1;

    m_elevatorTalon->Set(speed);
}

void Elevator::StartClimb() {
	ReleaseBrake();
	ConfigureCurrentLimits(30, 20, m_noTimeoutMs);
	m_elevatorTalon->Set(-1);
}

void Elevator::EndClimb() {
	m_elevatorTalon->Set(0);
	ApplyBrake();
	ConfigureCurrentLimits(m_defaultPeakAmps, m_defaultContinuousCurrent, m_noTimeoutMs);
}

void Elevator::InitDefaultCommand() {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
