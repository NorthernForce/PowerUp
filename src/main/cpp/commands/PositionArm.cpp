/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionArm.h"

struct PositionArm::PositionSetpoints {
	int m_armSetpoint;
	int m_elevatorSetpoint;
	unsigned m_armDelay;
};

bool hasClimbed = false;

const std::map<PositionArm::Position, PositionArm::PositionSetpoints> PositionArm::m_setpoints = {
		{ PositionArm::Position::Retracted, { 0,    0,     75 } },
		{ PositionArm::Position::Pickup,    { 475,  -3900, 0 } },
		{ PositionArm::Position::Switch,    { 500,  +1210,  0 } },
		{ PositionArm::Position::ScaleFront,{ 1600, +2660, 0 } },
		{ PositionArm::Position::ScaleRear, { 2600, +2660, 0 } },
        { PositionArm::Position::ClimbSet,  { 2525, +3000, 0 } },
};

PositionArm::PositionArm(Position pos) : Command("PositionArm")
{
  m_position = pos;
	Requires(m_arm.get());
	Requires(m_elevator.get());
}

// Called just before this Command runs the first time
void PositionArm::Initialize()
{
  const auto setpoints = m_setpoints.find(m_position);
	if (setpoints != m_setpoints.end()) {
		m_arm->SetPosition(setpoints->second.m_armSetpoint, setpoints->second.m_armDelay);
		m_elevator->SetCurrentPosition(setpoints->second.m_elevatorSetpoint);
	}
}

// Called repeatedly when this Command is scheduled to run
void PositionArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool PositionArm::IsFinished()
{
  const bool armDone = m_arm->AtSetpoint();
	const bool elevatorDone = m_elevator->AtSetPosition();
	return (armDone && elevatorDone);
}

// Called once after isFinished returns true
void PositionArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionArm::Interrupted() {}
