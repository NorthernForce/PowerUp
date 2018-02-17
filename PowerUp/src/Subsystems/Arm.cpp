#include "ctre/Phoenix.h"

#include "Arm.h"
#include "../RobotMap.h"

Arm::Arm() :
	frc::Subsystem("Arm")
{
	talonSRX = RobotMap::armTalonSRX9;
	talonSRX->ConfigMotionProfileTrajectoryPeriod(0, timeoutMs);
	talonSRX->Config_kF(0, feedForwardGain, timeoutMs);
	talonSRX->Config_kP(0, pGain, timeoutMs);
	talonSRX->Config_kI(0, iGain, timeoutMs);
	talonSRX->Config_kD(0, dGain, timeoutMs);
	talonSRX->Set(ControlMode::Position, 1);
	talonSRX->ConfigSelectedFeedbackSensor(QuadEncoder, 0, timeoutMs);
	talonSRX->SetSelectedSensorPosition(0, 0, timeoutMs);

	const auto feedTalon = [this]()
	{
		talonSRX->ProcessMotionProfileBuffer();
	    std::this_thread::sleep_for(std::chrono::milliseconds(5));
	};
	std::thread t(feedTalon);
	t.detach();
}

void Arm::InitDefaultCommand()
{
	ApplyBrake();
}

void Arm::Periodic()
{
	PushProfilePoints(*talonSRX, m_currentProfile, 1, 0, 0, false);
}

void Arm::SetPosition(int setpoint)
{
	ApplyBrake();
	const auto distance = talonSRX->GetSelectedSensorPosition(0) - setpoint;
	m_currentProfile = CreateConstantJerkProfile(distance, maxJerk);

	talonSRX->ClearMotionProfileHasUnderrun(noTimeoutMs);
	talonSRX->ClearMotionProfileTrajectories();
	Periodic();
	ReleaseBrake();
	talonSRX->ProcessMotionProfileBuffer();
	talonSRX->Set(ControlMode::MotionProfile, 1);
}

bool Arm::AtSetpoint()
{
	return talonSRX->GetClosedLoopError(0) < 12;
}

void Arm::ApplyBrake()
{
//	auto setpoint = talonSRX->GetSensorCollection().GetQuadraturePosition();
	auto setpoint = talonSRX->GetSelectedSensorPosition(0);
	talonSRX->Set(ControlMode::Position, setpoint);

	talonSRX->ConfigPeakOutputForward(+0.2, noTimeoutMs);
	talonSRX->ConfigPeakOutputReverse(-0.2, noTimeoutMs);
}

void Arm::ReleaseBrake()
{
	talonSRX->ConfigPeakOutputForward(+0.2, noTimeoutMs);
	talonSRX->ConfigPeakOutputReverse(-0.2, noTimeoutMs);
}
