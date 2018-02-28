
#include "Commands/DriveWithJoystick.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"

DriveTrain::DriveTrain() :
		frc::Subsystem("DriveTrain"),
		m_talonSRX1(RobotMap::driveTrainTalonSRX1),
		m_talonSRX2(RobotMap::driveTrainTalonSRX2),
		m_robotDrive(RobotMap::driveTrainRobotDrive)
{
	ConfigureTalon(*m_talonSRX1);
	ConfigureTalon(*m_talonSRX2);
}

void DriveTrain::InitDefaultCommand()
{
	if (m_driveWithJoystick == nullptr)
	{
		m_driveWithJoystick = new DriveWithJoystick();
	}

	SetDefaultCommand(m_driveWithJoystick);
}

double DriveTrain::GetSpeed()
{
	return (m_talonSRX1->Get() + m_talonSRX2->Get()) / 2.0;
}

int DriveTrain::GetPosition() {
	return m_talonSRX1->GetSensorCollection().GetQuadraturePosition();
}

void DriveTrain::Periodic()
{
	if (IsMotionProfileRunning())
	{
		FeedMotionProfile(false);
	}
}

void DriveTrain::ArcadeDrive(double moveValue, double rotateValue, bool squaredInputsf)
{
	m_robotDrive->ArcadeDrive(moveValue, rotateValue, squaredInputsf);
}

void DriveTrain::SetSafetyEnabled(bool enabled)
{
	m_robotDrive->SetSafetyEnabled(enabled);
}

void DriveTrain::InitializeMotionProfile(const ProfileGenerator& left, const ProfileGenerator& right)
{
	m_leftProfile = left;
	m_rightProfile = right;
	SetSafetyEnabled(false);
	m_talonSRX1->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	m_talonSRX2->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	m_talonSRX1->ClearMotionProfileTrajectories();
	m_talonSRX2->ClearMotionProfileTrajectories();
	FeedMotionProfile(true);
	m_talonSRX1->Set(ControlMode::MotionProfile, SetValueMotionProfile::Enable);
	m_talonSRX2->Set(ControlMode::MotionProfile, SetValueMotionProfile::Enable);
}

void DriveTrain::TerminateMotionProfile()
{
	m_talonSRX1->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	m_talonSRX2->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	m_leftProfile = nullptr;
	m_rightProfile = nullptr;
}

bool DriveTrain::IsMotionProfileRunning() const
{
	auto isEnabled = [](WPI_TalonSRX& talon)
	{
		MotionProfileStatus status;
		talon.GetMotionProfileStatus(status);
		return status.outputEnable == SetValueMotionProfile::Enable;
	};

	return isEnabled(*m_talonSRX1) || isEnabled(*m_talonSRX2);
}

void DriveTrain::FeedMotionProfile(const bool zeroPos)
{
	const auto feedTalon = [zeroPos](WPI_TalonSRX& talon, ProfileGenerator& profile)
			{
				const auto pidIdx0 = pidIdx;
				const auto pidIdx1 = 1;

				MotionProfileStatus status;
				talon.GetMotionProfileStatus(status);
				if(!status.isLast)
				{
					PushProfilePoints(talon, status, profile, nativeUnitsPerMeterLowGear, pidIdx0, pidIdx1, zeroPos);
				}
				talon.ProcessMotionProfileBuffer();
			};

	feedTalon(*m_talonSRX1, m_leftProfile);
	feedTalon(*m_talonSRX2, m_rightProfile);
}

void DriveTrain::ConfigureTalon(WPI_TalonSRX& talon)
{
	talon.ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);
	talon.ClearMotionProfileHasUnderrun(timeoutMs);
	talon.ClearMotionProfileTrajectories();
	talon.ChangeMotionControlFramePeriod(5);
	talon.ConfigMotionProfileTrajectoryPeriod(0, timeoutMs);
	talon.SetNeutralMode(NeutralMode::Coast);
	talon.SelectProfileSlot(slotIdx, pidIdx);
	talon.Config_kF(slotIdx, feedForwardGain, timeoutMs);
//	talon.Config_kP(slotIdx, pGain, timeoutMs);
//	talon.Config_kI(slotIdx, iGain, timeoutMs);
//	talon.ConfigMaxIntegralAccumulator(slotIdx, iLimit, timeoutMs);
//	talon.Config_kD(slotIdx, dGain, timeoutMs);
}
