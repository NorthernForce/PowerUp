#include "ctre/Phoenix.h"

#include "Arm.h"
#include "../RobotMap.h"

Arm::Arm() :
	frc::Subsystem("Arm")
{
	talonSRX = RobotMap::armTalonSRX9;
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
	talonSRX->Set(ControlMode::Position, setpoint);
	talonSRX->Config_kF(0, feedForwardGain, 10);
	talonSRX->Config_kP(0, pGain, 10);
	talonSRX->Config_kI(0, iGain, 10);
	talonSRX->Config_kD(0, dGain, 10);
}

bool Arm::AtSetpoint()
{
	return talonSRX->GetClosedLoopError(0) < 12;
}

void Arm::ApplyBrake()
{
	talonSRX->ConfigPeakOutputForward(+0.2, 10);
	talonSRX->ConfigPeakOutputReverse(-0.2, 10);
}

void Arm::ReleaseBrake()
{
	talonSRX->ConfigPeakOutputForward(+0.2, 10);
	talonSRX->ConfigPeakOutputReverse(-0.2, 10);
}
