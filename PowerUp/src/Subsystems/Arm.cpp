#include "ctre/Phoenix.h"

#include "Arm.h"
#include "../RobotMap.h"

Arm::Arm() :
	frc::Subsystem("Arm"),
	m_talonSRX(RobotMap::armTalonSRX8),
	m_telemetry(m_talonSRX, pidIdx, 5)
{
	m_talonSRX->ConfigPeakOutputForward(+0.25, timeoutMs);
	m_talonSRX->ConfigPeakOutputReverse(-0.25, timeoutMs);
	m_talonSRX->ConfigNominalOutputForward(+0.0, timeoutMs);
	m_talonSRX->ConfigNominalOutputReverse(-0.0, timeoutMs);
	m_talonSRX->ConfigAllowableClosedloopError(slotIdx, sensorUnitsPerRev, timeoutMs);
	m_talonSRX->SelectProfileSlot(slotIdx, pidIdx);
	m_talonSRX->Config_kF(slotIdx, feedForwardGain, timeoutMs);
	m_talonSRX->Config_kP(slotIdx, pGain, timeoutMs);
	m_talonSRX->Config_kI(slotIdx, iGain, timeoutMs);
	m_talonSRX->Config_kD(slotIdx, dGain, timeoutMs);
	m_talonSRX->ConfigMotionCruiseVelocity(maxSensorUnitsPer100ms, timeoutMs);
	m_talonSRX->ConfigMotionAcceleration(maxSensorUnitsPer100ms / timeToMaxSpeed, timeoutMs);
	m_talonSRX->ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);
	SetHomePosition();
	ApplyBrake();
	m_telemetry.Start();
}

void Arm::InitDefaultCommand()
{
	ApplyBrake();
}

void Arm::Periodic()
{
	m_talonSRX->Set(ControlMode::MotionMagic, m_setpoint);
	m_telemetry.Periodic();
}

void Arm::SetPosition(int setpoint)
{
	ReleaseBrake();
	m_setpoint = setpoint;
}

bool Arm::AtSetpoint()
{
	return false;
}

void Arm::ApplyBrake()
{
}

void Arm::ReleaseBrake()
{
}

void Arm::SetHomePosition()
{
	m_setpoint = 0;
	m_talonSRX->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
}
