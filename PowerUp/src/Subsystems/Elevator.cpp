#include "ctre/Phoenix.h"

#include "Elevator.h"
#include "../RobotMap.h"

Elevator::Elevator() :
	frc::Subsystem("Elevator"),
	m_elevatorBrake(RobotMap::elevatorBrake),
	m_masterTalon(RobotMap::elevatorTalonSRX9),
	m_slaveTalon(RobotMap::elevatorTalonSRX7),
	m_telemetry({ m_masterTalon, m_slaveTalon}, pidIdx, std::chrono::milliseconds(20))
{
	m_masterTalon->ConfigPeakOutputForward(+1, timeoutMs);
	m_masterTalon->ConfigPeakOutputReverse(-1, timeoutMs);
	m_slaveTalon->ConfigPeakOutputForward(+1, timeoutMs);
	m_slaveTalon->ConfigPeakOutputReverse(-1, timeoutMs);

    ConfigureCurrentLimits(defaultPeakAmps, defaultContinuousCurrent, timeoutMs);
	m_masterTalon->ConfigNominalOutputForward(+0.0, timeoutMs);
	m_masterTalon->ConfigNominalOutputReverse(-0.0, timeoutMs);
	m_masterTalon->SelectProfileSlot(slotIdx, pidIdx);
	//TODO: change these for more power
	m_masterTalon->Config_kF(slotIdx, feedForwardGain, timeoutMs);
	m_masterTalon->Config_kP(slotIdx, pGain, timeoutMs);
	m_masterTalon->Config_kI(slotIdx, iGain, timeoutMs);
	m_masterTalon->ConfigMaxIntegralAccumulator(slotIdx, iLimit, timeoutMs);
	m_masterTalon->Config_kD(slotIdx, dGain, timeoutMs);
	m_masterTalon->ConfigMotionCruiseVelocity(maxSensorUnitsPer100ms, timeoutMs);
	m_masterTalon->ConfigMotionAcceleration(maxSensorUnitsPer100ms / timeToMaxSpeed, timeoutMs);
	m_masterTalon->ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);

	m_masterTalon->SetName("Elevator", "Elevator");
	m_masterTalon->SetNeutralMode(NeutralMode::Brake);
    m_slaveTalon->SetName("Elevator", "Elevator slave");
    m_slaveTalon->SetNeutralMode(NeutralMode::Brake);

    m_slaveTalon->Follow(*m_masterTalon);

   	SetHomePosition();
	ApplyBrake();
	m_telemetry.Start();
}

void Elevator::InitDefaultCommand()
{
	ApplyBrake();
}

void Elevator::Periodic()
{
}

void Elevator::SetPosition(int setpoint)
{
	ReleaseBrake();
	m_setpoint = setpoint;
	m_masterTalon->Set(ControlMode::MotionMagic, m_setpoint);
}

bool Elevator::AtSetpoint()
{
	return m_masterTalon->GetClosedLoopError(pidIdx) < 250;
}

void Elevator::ApplyBrake() {
	m_elevatorBrake->Set(false);
}

void Elevator::ReleaseBrake() {
	m_elevatorBrake->Set(true);
}

void Elevator::SetHomePosition()
{
	DriverStation::ReportWarning("Elevator home position reset");
	m_setpoint = 0;
	m_masterTalon->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
	m_masterTalon->Set(ControlMode::MotionMagic, m_setpoint);
}

void Elevator::Nudge(int distance)
{
	ReleaseBrake();
	m_setpoint = m_setpoint + distance;
	m_masterTalon->Set(ControlMode::MotionMagic, m_setpoint);
}

void Elevator::BeginClimb()
{
	ReleaseBrake();
	ConfigureCurrentLimits(30, 20, noTimeoutMs);
	m_masterTalon->Set(-1);
}

void Elevator::EndClimb()
{
	m_masterTalon->Set(0);
	ApplyBrake();
	ConfigureCurrentLimits(defaultPeakAmps, defaultContinuousCurrent, noTimeoutMs);
}

void Elevator::ConfigureCurrentLimits(int peakAmps, int continuousCurrent, int timeout)
{
	m_masterTalon->ConfigPeakCurrentLimit(peakAmps, timeout);
    m_masterTalon->ConfigContinuousCurrentLimit(continuousCurrent, timeout);
    m_masterTalon->ConfigPeakCurrentDuration(100, timeout);
    m_masterTalon->EnableCurrentLimit(true);
    m_slaveTalon->ConfigPeakCurrentLimit(peakAmps, timeout);
    m_slaveTalon->ConfigContinuousCurrentLimit(continuousCurrent, timeout);
    m_slaveTalon->ConfigPeakCurrentDuration(100, timeout);
    m_slaveTalon->EnableCurrentLimit(true);
}
