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
		m_leftTelemetry(m_talonSRX1, pidIdx, std::chrono::milliseconds(10)),
		m_rightTelemetry(m_talonSRX2, pidIdx, std::chrono::milliseconds(10))
{
	ConfigureTalon(*m_talonSRX1);
	ConfigureTalon(*m_talonSRX2);
	RobotMap::driveTrainTalonSRX1->ConfigVoltageCompSaturation(11, timeoutMs);
	RobotMap::driveTrainTalonSRX2->ConfigVoltageCompSaturation(11, timeoutMs);
	RobotMap::driveTrainTalonSRX3->ConfigVoltageCompSaturation(11, timeoutMs);
	RobotMap::driveTrainTalonSRX4->ConfigVoltageCompSaturation(11, timeoutMs);
	RobotMap::driveTrainTalonSRX5->ConfigVoltageCompSaturation(11, timeoutMs);
	RobotMap::driveTrainTalonSRX6->ConfigVoltageCompSaturation(11, timeoutMs);
	EnableVoltageCompensation(false);
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
	Robot::driveTrainShifter->Shift(DriveTrainShifter::Gear::Low);
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
	const double pValue = 1;
	const double iValue = 0.02;
	const double iLimit = 0.1E6;
	talon.ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);
	talon.ClearMotionProfileHasUnderrun(timeoutMs);
	talon.ClearMotionProfileTrajectories();
	talon.ChangeMotionControlFramePeriod(5);
	talon.ConfigMotionProfileTrajectoryPeriod(0, timeoutMs);
	talon.SetNeutralMode(NeutralMode::Coast);
	talon.SelectProfileSlot(slotIdx, pidIdx);
	talon.Config_kF(slotIdx, feedForwardGain, timeoutMs);
	talon.Config_kP(slotIdx, pValue, timeoutMs);
	talon.Config_kI(slotIdx, iValue, timeoutMs);
	talon.ConfigMaxIntegralAccumulator(slotIdx, iLimit, timeoutMs);
	talon.SetSelectedSensorPosition(0, pidIdx, timeoutMs);
}

void DriveTrain::SetOutput(double speed) {
	m_talonSRX1->ConfigPeakOutputForward(speed, timeoutMs);
	m_talonSRX1->ConfigPeakOutputReverse(speed, timeoutMs);
	m_talonSRX2->ConfigPeakOutputForward(speed, timeoutMs);
	m_talonSRX2->ConfigPeakOutputReverse(speed, timeoutMs);
}

void DriveTrain::EnableVoltageCompensation(bool enabled)
{
	RobotMap::driveTrainTalonSRX1->EnableVoltageCompensation(enabled);
	RobotMap::driveTrainTalonSRX2->EnableVoltageCompensation(enabled);
	RobotMap::driveTrainTalonSRX3->EnableVoltageCompensation(enabled);
	RobotMap::driveTrainTalonSRX4->EnableVoltageCompensation(enabled);
	RobotMap::driveTrainTalonSRX5->EnableVoltageCompensation(enabled);
	RobotMap::driveTrainTalonSRX6->EnableVoltageCompensation(enabled);
}

int DriveTrain::GetPositionLeft() {
	return m_talonSRX1->GetSensorCollection().GetQuadraturePosition();
}

int DriveTrain::GetPositionRight() {
	return m_talonSRX2->GetSensorCollection().GetQuadraturePosition();
}

void DriveTrain::SetBrake() {
	m_talonSRX1->SetNeutralMode(NeutralMode::Brake);
	m_talonSRX2->SetNeutralMode(NeutralMode::Brake);
}

void DriveTrain::SetCoast() {
	m_talonSRX1->SetNeutralMode(NeutralMode::Coast);
	m_talonSRX2->SetNeutralMode(NeutralMode::Coast);
}
