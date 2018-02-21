#include "PositionArm.h"

struct PositionArm::PositionSetpoints
{
	int m_armSetpoint;
	int m_elevatorSetpoint;
	unsigned m_armDelay;
};

const std::map<PositionArm::Position, PositionArm::PositionSetpoints> PositionArm::m_setpoints = {
		{ PositionArm::Position::Retracted, { 0,    0,     75 } },
		{ PositionArm::Position::Pickup,    { 420,  -2300, 0 } },
		{ PositionArm::Position::Switch,    { 500,  +400,  0 } },
		{ PositionArm::Position::ScaleFront,{ 1600, +1500, 0 } },
		{ PositionArm::Position::ScaleRear, { 2600, +1500, 0 } },
		//{ PositionArm::Position::Climb, { , , } },
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
		m_arm->SetPosition(setpoints->second.m_armSetpoint, setpoints->second.m_armDelay);
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

	return false && armDone && elevatorDone;
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
	m_arm->ApplyBrake();
	m_elevator->ApplyBrake();
}
