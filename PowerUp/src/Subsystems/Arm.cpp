#include "ctre/Phoenix.h"

#include "Arm.h"
#include "../RobotMap.h"

Arm::Arm() :
	frc::Subsystem("Arm"),
	m_talonSRX(RobotMap::armTalonSRX8),
	m_telemetry(m_talonSRX, pidIdx, std::chrono::milliseconds(20)),
	m_delay(0)
{
	m_talonSRX->ConfigPeakOutputForward(+0.50, timeoutMs);
	m_talonSRX->ConfigPeakOutputReverse(-0.50, timeoutMs);
	m_talonSRX->ConfigNominalOutputForward(+0.00, timeoutMs);
	m_talonSRX->ConfigNominalOutputReverse(-0.00, timeoutMs);
	m_talonSRX->SelectProfileSlot(slotIdx, pidIdx);
	m_talonSRX->Config_kF(slotIdx, feedForwardGain, timeoutMs);
	m_talonSRX->Config_kP(slotIdx, pGain, timeoutMs);
	m_talonSRX->Config_kI(slotIdx, iGain, timeoutMs);
	m_talonSRX->ConfigMaxIntegralAccumulator(slotIdx, iLimit, timeoutMs);
	m_talonSRX->Config_kD(slotIdx, dGain, timeoutMs);
	m_talonSRX->ConfigMotionCruiseVelocity(maxSensorUnitsPer100ms, timeoutMs);
	m_talonSRX->ConfigMotionAcceleration(maxSensorUnitsPer100ms / timeToMaxSpeed, timeoutMs);
	m_talonSRX->ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);
	m_talonSRX->SetNeutralMode(NeutralMode::Brake);
	m_talonSRX->SetName("Arm");
    m_talonSRX->ConfigPeakCurrentLimit(10, timeoutMs);
    m_talonSRX->ConfigPeakCurrentDuration(100, timeoutMs);
    m_talonSRX->ConfigContinuousCurrentLimit(4, timeoutMs);
    m_talonSRX->EnableCurrentLimit(true);
    m_talonSRX->EnableVoltageCompensation(true);
    m_talonSRX->ConfigVoltageCompSaturation(11, timeoutMs);
	SetHomePosition();
	m_telemetry.Start();
}

void Arm::InitDefaultCommand() {
}

void Arm::Periodic() {
	DriverStation::ReportWarning("Arm Current: " + std::to_string(m_talonSRX->GetOutputCurrent()));
	const double armCurrent = m_talonSRX->GetOutputCurrent();
	const double armVelocity = m_talonSRX->GetSensorCollection().GetQuadratureVelocity();
	const double armStallCurrent = 5.0;
	const double armStallVelocity = 10.0;
	if (armCurrent > armStallCurrent && (std::abs(armVelocity) < armStallVelocity)) {
		numTimesArmStalled++;
		DriverStation::ReportWarning("arm stall detected");
	} else {
		numTimesSinceLastArmStall++;
	}
	if (numTimesArmStalled >= 1) {
		isArmStalled = true;
	} else {
		isArmStalled = false;
		if (numTimesSinceLastArmStall >= 100) {
			numTimesArmStalled = 0;
		}
	}
	if (isArmStalled) {
		DriverStation::ReportWarning("Arm stalled. Stopping motor");
		m_talonSRX->StopMotor();
		m_talonSRX->ClearMotionProfileTrajectories();
		m_talonSRX->SetIntegralAccumulator(0, pidIdx, timeoutMs);
		//TODO: change control mode
		//TODO: re-enable
	}
	if (m_delay > 0) {
		m_delay -= 1;
	} else {
		m_talonSRX->Set(ControlMode::MotionMagic, m_setpoint);
		m_delay = 10;
	}
}

void Arm::SetPosition(int setpoint, unsigned delay) {
	m_setpoint = setpoint;
	m_delay = delay;
	m_talonSRX->ConfigPeakOutputForward(+0.40, 0);
	m_talonSRX->ConfigPeakOutputReverse(-0.40, 0);
}

bool Arm::AtSetpoint() {
	return m_talonSRX->GetClosedLoopError(pidIdx) < 50;
}

void Arm::SetHomePosition() {
	DriverStation::ReportWarning("Arm home position reset");
	m_setpoint = 0;
	m_talonSRX->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
	m_talonSRX->Set(ControlMode::MotionMagic, m_setpoint);
}

void Arm::NudgeArm(int distance) {
	m_setpoint = m_setpoint + distance;
	m_talonSRX->Set(ControlMode::MotionMagic, m_setpoint);
}

void Arm::InitSendable(SendableBuilder& builder) {
	Subsystem::InitSendable(builder);
	auto pos = builder.GetEntry("Encoder position").GetHandle();
	builder.SetUpdateTable([=]() {
		auto data = m_talonSRX->GetSensorCollection();
		nt::NetworkTableEntry(pos).SetDouble(data.GetQuadraturePosition());
	});
}

void Arm::ReducePowerForClimb() {
	m_talonSRX->ConfigPeakOutputForward(+0.10, timeoutMs);
	m_talonSRX->ConfigPeakOutputReverse(-0.10, timeoutMs);
}

void Arm::EnableVoltageCompensation(bool doEnable) {
	m_talonSRX->EnableVoltageCompensation(doEnable);
}
