#include "ctre/Phoenix.h"

#include "Elevator.h"
#include "../RobotMap.h"

Elevator::Elevator() :
	frc::Subsystem("Elevator"),
	m_elevatorBrake(RobotMap::elevatorBrake),
	m_masterTalon(RobotMap::elevatorTalonSRX9),
	m_slaveTalon(RobotMap::elevatorTalonSRX7),
	m_telemetry({ m_masterTalon, m_slaveTalon}, pidIdx, std::chrono::milliseconds(100))
{
	ConfigurePower(+0.9, -0.5, timeoutMs);
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
	m_masterTalon->ConfigPeakCurrentLimit(10, timeoutMs);
    m_masterTalon->ConfigPeakCurrentDuration(100, timeoutMs);
    m_masterTalon->ConfigContinuousCurrentLimit(8, timeoutMs);
    m_masterTalon->EnableCurrentLimit(true);
    m_slaveTalon->SetName("Elevator", "Elevator slave");
    m_slaveTalon->SetNeutralMode(NeutralMode::Brake);
    m_slaveTalon->ConfigPeakCurrentLimit(10, timeoutMs);
    m_slaveTalon->ConfigPeakCurrentDuration(100, timeoutMs);
    m_slaveTalon->ConfigContinuousCurrentLimit(8, timeoutMs);
    m_slaveTalon->EnableCurrentLimit(true);
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
	ConfigurePower(+0.9, -0.5, noTimeoutMs);

	ReleaseBrake();
	m_setpoint = setpoint;
	m_masterTalon->Set(ControlMode::MotionMagic, m_setpoint);
}

bool Elevator::AtSetpoint()
{
	return false;
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
	ConfigurePower(+1, -1, noTimeoutMs);
	m_masterTalon->ConfigPeakCurrentLimit(30, timeoutMs);
    m_masterTalon->ConfigContinuousCurrentLimit(20, timeoutMs);
    m_slaveTalon->ConfigPeakCurrentLimit(30, timeoutMs);
    m_slaveTalon->ConfigContinuousCurrentLimit(20, timeoutMs);
	m_masterTalon->Set(-1);
}

void Elevator::EndClimb()
{
	m_masterTalon->Set(0);
	ApplyBrake();
	m_masterTalon->ConfigPeakCurrentLimit(10, timeoutMs);
    m_masterTalon->ConfigContinuousCurrentLimit(8, timeoutMs);
    m_slaveTalon->ConfigPeakCurrentLimit(10, timeoutMs);
    m_slaveTalon->ConfigContinuousCurrentLimit(8, timeoutMs);
}

void Elevator::ConfigurePower(double forward, double reverse, int timeout)
{
	m_masterTalon->ConfigPeakOutputForward(forward, timeout);
	m_masterTalon->ConfigPeakOutputReverse(reverse, timeout);
	m_slaveTalon->ConfigPeakOutputForward(forward, timeout);
	m_slaveTalon->ConfigPeakOutputReverse(reverse, timeout);
}
