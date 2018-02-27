
#include "Commands/DriveWithJoystick.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"

DriveTrain::DriveTrain() :
		frc::Subsystem("DriveTrain"),
		m_talonSRX1(RobotMap::driveTrainTalonSRX1),
		m_talonSRX2(RobotMap::driveTrainTalonSRX2),
		m_robotDrive(RobotMap::driveTrainRobotDrive),
		m_leftProfile(*m_talonSRX1, pidIdx),
		m_rightProfile(*m_talonSRX2, pidIdx)
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
	DriverStation::ReportError("InitializeMotionProfile start");
	SetSafetyEnabled(false);
	m_leftProfile.Start(left, nativeUnitsPerMeterLowGear);
	m_rightProfile.Start(right, nativeUnitsPerMeterLowGear);
	DriverStation::ReportError("InitializeMotionProfile finish");
}

void DriveTrain::TerminateMotionProfile()
{
	m_leftProfile.Cancel();
	m_rightProfile.Cancel();
}

bool DriveTrain::IsMotionProfileFinished() const
{
	return m_leftProfile.IsFinished() && m_rightProfile.IsFinished();
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
