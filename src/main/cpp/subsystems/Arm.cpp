/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Arm.h"
#include "frc/DriverStation.h"
#include "RobotMap.h"

Arm::Arm() :
 Subsystem("Arm") {
  	m_armTalon.reset(new WPI_TalonSRX (RobotMap::ArmAssemblyTalons::k_armTalon_id));
	m_armTalon->SetName("Arm");
	m_armTalon->SelectProfileSlot(m_slotIdx, m_PidID);
	m_armTalon->ConfigMaxIntegralAccumulator(m_slotIdx, iLimit, m_timeoutMs);
	m_armTalon->SetNeutralMode(NeutralMode::Brake);
	SetPID();
	ConfigureOutputPower();
    ConfigureCurrentLimits();
	SetupEncoder();
	SetHomePosition();
}

void Arm::InitDefaultCommand() {}

void Arm::Periodic() {
	if (m_delay > 0)
		m_delay -= 1;
	else {
		m_armTalon->Set(ControlMode::MotionMagic, m_setPosition);
		m_delay = 10;
	}
}

void Arm::SetPID() {
	m_armTalon->Config_kP(m_slotIdx, pGain, m_timeoutMs);
	m_armTalon->Config_kI(m_slotIdx, iGain, m_timeoutMs);
	m_armTalon->Config_kD(m_slotIdx, dGain, m_timeoutMs);
	m_armTalon->Config_kF(m_slotIdx, feedForwardGain, m_timeoutMs);
}

void Arm::ConfigureOutputPower() {
	m_armTalon->ConfigPeakOutputForward(+0.50, m_timeoutMs);
	m_armTalon->ConfigPeakOutputReverse(-0.50, m_timeoutMs);
	m_armTalon->ConfigNominalOutputForward(+0.00, m_timeoutMs);
	m_armTalon->ConfigNominalOutputReverse(-0.00, m_timeoutMs);
}

void Arm::ConfigureCurrentLimits() {
	m_armTalon->ConfigPeakCurrentLimit(10, m_timeoutMs);
    m_armTalon->ConfigPeakCurrentDuration(100, m_timeoutMs);
    m_armTalon->ConfigContinuousCurrentLimit(4, m_timeoutMs);
    m_armTalon->EnableCurrentLimit(true);
}

void Arm::SetupEncoder() {
	m_armTalon->ConfigMotionCruiseVelocity(maxSensorUnitsPer100ms, m_timeoutMs);
	m_armTalon->ConfigMotionAcceleration(maxSensorUnitsPer100ms / timeToMaxSpeed, m_timeoutMs);
	m_armTalon->ConfigSelectedFeedbackSensor(QuadEncoder, m_PidID, m_timeoutMs);
}

void Arm::SetHomePosition() {
	frc::DriverStation::ReportWarning("Arm home position reset");
	m_setPosition = 0;
	m_armTalon->SetSelectedSensorPosition(m_setPosition, m_PidID, m_timeoutMs);
	m_armTalon->Set(ControlMode::MotionMagic, m_setPosition);
}

void Arm::SetPosition(int setPosition, unsigned delay) {
	m_setPosition = setPosition;
	m_delay = delay;
	m_armTalon->ConfigPeakOutputForward(+0.40, 0);
	m_armTalon->ConfigPeakOutputReverse(-0.40, 0);
}

bool Arm::AtSetPosition() {
	return m_armTalon->GetClosedLoopError(m_PidID) < 50;
}

void Arm::Nudge(int distance) {
	m_setPosition = m_setPosition + distance;
	m_armTalon->Set(ControlMode::MotionMagic, m_setPosition);
}

void Arm::Move(int speed) {
	if (speed < -1)
        speed = -1;
	else if (speed > 1)
        speed = 1;
	m_armTalon->Set(speed);
}

void Arm::ReducePowerForClimb() {
	m_armTalon->ConfigPeakOutputForward(+0.10, m_timeoutMs);
	m_armTalon->ConfigPeakOutputReverse(-0.10, m_timeoutMs);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
