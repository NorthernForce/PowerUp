#include "Gripper.h"
#include "../RobotMap.h"

Gripper::Gripper() :
	frc::Subsystem("Gripper"),
	m_gripperState(State::Closed),
	m_gripperSolenoid(RobotMap::gripperSolenoid)
{
}

void Gripper::SetOpen()
{
	m_gripperSolenoid->Set(true);
	m_gripperState = State::Open;
}

void Gripper::SetClosed()
{
	m_gripperSolenoid->Set(false);
	m_gripperState = State::Open;
}
