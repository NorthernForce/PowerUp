#include <RobotMap.h>
#include "ctre/Phoenix.h"

#include "Elevator.h"

Elevator::Elevator() :
	frc::Subsystem("Elevator"),
	talonSRX7(RobotMap::elevatorTalonSRX7),
	talonSRX8(RobotMap::elevatorTalonSRX8)
{
	talonSRX8->Follow(*talonSRX7);
}

void Elevator::InitDefaultCommand()
{
}

void Elevator::Periodic()
{
}

void Elevator::SetPosition(int setpoint)
{
	ReleaseBrake();
	talonSRX7->Set(ControlMode::Position, setpoint);
}

bool Elevator::AtSetpoint()
{
	return talonSRX7->GetClosedLoopError(0) < 12;
}

void Elevator::ApplyBrake()
{
}

void Elevator::ReleaseBrake()
{
}
