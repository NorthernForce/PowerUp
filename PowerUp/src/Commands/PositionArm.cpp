#include "PositionArm.h"

struct PositionArm::PositionSetpoints
{
	int m_armSetpoint;
	int m_elevatorSetpoint;
};

const std::map<PositionArm::Position, PositionArm::PositionSetpoints> PositionArm::m_setpoints = {
		{ PositionArm::Position::Retracted, { 0, 2000 } },
		{ PositionArm::Position::Pickup, { 500, 0 } },
		{ PositionArm::Position::Switch, { 1050, 2000 } },
		{ PositionArm::Position::ScaleFront, { 1800, 4000 } },
		{ PositionArm::Position::ScaleRear, { 2100, 4000 } },
};

PositionArm::PositionArm(Position pos) :
	m_elevator(Robot::elevator.get()),
	m_arm(Robot::arm.get())
{
	m_position = pos;
	Requires(m_arm.get());
	Requires(m_elevator.get());
}

// Called just before this Command runs the first time
void PositionArm::Initialize()
{
	const auto setpoints = m_setpoints.find(m_position);
	if (setpoints != m_setpoints.end())
	{
		m_arm->SetPosition(setpoints->second.m_armSetpoint);
		m_elevator->SetPosition(setpoints->second.m_elevatorSetpoint);
	}
}

// Called repeatedly when this Command is scheduled to run
void PositionArm::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool PositionArm::IsFinished()
{
	const bool armDone = m_arm->AtSetpoint();
	if (armDone)
	{
		m_arm->ApplyBrake();
	}

	const bool elevatorDone = m_elevator->AtSetpoint();
	if (elevatorDone)
	{
		m_elevator->ApplyBrake();
	}

	return armDone && elevatorDone;
}

// Called once after isFinished returns true
void PositionArm::End()
{
	m_arm->ApplyBrake();
	m_elevator->ApplyBrake();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionArm::Interrupted()
{
}
