
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
		m_rightProfile(*m_talonSRX2, pidIdx),
		m_leftTelemetry(m_talonSRX1, pidIdx, std::chrono::milliseconds(20)),
		m_rightTelemetry(m_talonSRX2, pidIdx, std::chrono::milliseconds(20))
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

//returns units per 100ms, by default units are in 1/1024 of a rotation
//https://github.com/CrossTheRoadElec/Phoenix-Documentation/blob/master/Migration%20Guide.md
double DriveTrain::GetSpeed()
{
	double left = m_talonSRX1->GetSensorCollection().GetQuadratureVelocity();
	double right = m_talonSRX2->GetSensorCollection().GetQuadratureVelocity();
	return ( std::abs(left) + std::abs(right) ) / 2;
}

int DriveTrain::GetPosition() {
	printf("srx1: %i srx2: %i\n", m_talonSRX1->GetSensorCollection().GetQuadraturePosition(), m_talonSRX2->GetSensorCollection().GetQuadraturePosition());
	return m_talonSRX1->GetSensorCollection().GetQuadraturePosition();
}

void DriveTrain::SetSpeed(double speed) {
	m_talonSRX1->Set(speed);
	m_talonSRX2->Set(speed);
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
	m_leftTelemetry.Start();
	m_rightTelemetry.Start();
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
	m_leftTelemetry.Stop();
	m_rightTelemetry.Stop();
}

bool DriveTrain::IsMotionProfileFinished() const
{
	return m_leftProfile.IsFinished() && m_rightProfile.IsFinished();
}

void DriveTrain::ConfigureTalon(WPI_TalonSRX& talon)
{
	double pValue = 0.2;
	if(talon.GetInverted())
	{
		pValue = -pValue;
	}
	talon.ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);
	talon.ClearMotionProfileHasUnderrun(timeoutMs);
	talon.ClearMotionProfileTrajectories();
	talon.ChangeMotionControlFramePeriod(5);
	talon.ConfigMotionProfileTrajectoryPeriod(0, timeoutMs);
	talon.SetNeutralMode(NeutralMode::Coast);
	talon.SelectProfileSlot(slotIdx, pidIdx);
	talon.Config_kF(slotIdx, feedForwardGain, timeoutMs);
	talon.Config_kP(slotIdx, pValue, timeoutMs);
}
