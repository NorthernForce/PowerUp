#include "ctre/Phoenix.h"

#include "Arm.h"
#include "../RobotMap.h"

Arm::Arm() :
	frc::Subsystem("Arm"),
	m_talonSRX(RobotMap::armTalonSRX8),
	m_telemetry(m_talonSRX, pidIdx, 5),
	m_delay(0)
{
	m_talonSRX->ConfigPeakOutputForward(+0.35, timeoutMs);
	m_talonSRX->ConfigPeakOutputReverse(-0.20, timeoutMs);
	m_talonSRX->ConfigNominalOutputForward(+0.00, timeoutMs);
	m_talonSRX->ConfigNominalOutputReverse(-0.00, timeoutMs);
	m_talonSRX->SelectProfileSlot(slotIdx, pidIdx);
	m_talonSRX->Config_kF(slotIdx, feedForwardGain, timeoutMs);
	m_talonSRX->Config_kP(slotIdx, pGain, timeoutMs);
	m_talonSRX->Config_kI(slotIdx, iGain, timeoutMs);
	m_talonSRX->Config_kD(slotIdx, dGain, timeoutMs);
	m_talonSRX->ConfigMotionCruiseVelocity(maxSensorUnitsPer100ms, timeoutMs);
	m_talonSRX->ConfigMotionAcceleration(maxSensorUnitsPer100ms / timeToMaxSpeed, timeoutMs);
	m_talonSRX->ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);
	m_talonSRX->SetNeutralMode(NeutralMode::Brake);
	m_talonSRX->SetName("Arm");
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
	if(m_delay > 0)
	{
		m_delay -= 1;
	}
	else
	{
		m_talonSRX->Set(ControlMode::MotionMagic, m_setpoint);
		m_telemetry.Periodic();
	}
}

void Arm::SetPosition(int setpoint, unsigned delay)
{
	ReleaseBrake();
	m_setpoint = setpoint;
	m_delay = delay;
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
	DriverStation::ReportWarning("Arm home position reset");
	m_setpoint = 0;
	m_talonSRX->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
}

void Arm::InitSendable(SendableBuilder& builder)
{
	Subsystem::InitSendable(builder);
	auto pos = builder.GetEntry("Encoder position").GetHandle();
	builder.SetUpdateTable([=]() {
		auto data = m_talonSRX->GetSensorCollection();
		nt::NetworkTableEntry(pos).SetDouble(data.GetQuadraturePosition());
	});
}
