#include "ctre/Phoenix.h"

#include "Arm.h"
#include "../RobotMap.h"

Arm::Arm() :
	frc::Subsystem("Arm")
{
	talonSRX9 = RobotMap::armTalonSRX9;
}

void Arm::InitDefaultCommand()
{
}

void Arm::Periodic()
{
}

void Arm::SetPosition(int setpoint)
{
	ReleaseBrake();
	talonSRX9->Set(ControlMode::Position, setpoint);
}

bool Arm::AtSetpoint()
{
	return talonSRX9->GetClosedLoopError(0) < 12;
}

void Arm::ApplyBrake()
{
	talonSRX9->ConfigPeakOutputForward(+0.2, 10);
	talonSRX9->ConfigPeakOutputReverse(-0.2, 10);
}

void Arm::ReleaseBrake()
{
	talonSRX9->ConfigPeakOutputForward(+0.2, 10);
	talonSRX9->ConfigPeakOutputReverse(-0.2, 10);
}
