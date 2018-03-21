#include "PositionArm.h"

struct PositionArm::PositionSetpoints {
	int m_armSetpoint;
	int m_elevatorSetpoint;
	unsigned m_armDelay;
};

bool hasClimbed = false;

#ifdef PRACTICE_BOT
const std::map<PositionArm::Position, PositionArm::PositionSetpoints> PositionArm::m_setpoints = {
		{ PositionArm::Position::Retracted, { 0,    0,     75 } },
		{ PositionArm::Position::Pickup,    { 420,  -2500, 0 } },
		{ PositionArm::Position::Switch,    { 500,  +700,  0 } },
		{ PositionArm::Position::ScaleFront,{ 1600, +1700, 0 } },
		{ PositionArm::Position::ScaleRear, { 2600, +1500, 0 } },
        { PositionArm::Position::ClimbSet,  { 2500, +2700, 0 } },
};
#else
const std::map<PositionArm::Position, PositionArm::PositionSetpoints> PositionArm::m_setpoints = {
		{ PositionArm::Position::Retracted, { 0,    0,     75 } },
		{ PositionArm::Position::Pickup,    { 420,  -3600, 0 } },
		{ PositionArm::Position::Switch,    { 500,  +700,  0 } },
		{ PositionArm::Position::ScaleFront,{ 1600, +1500, 0 } },
		{ PositionArm::Position::ScaleRear, { 2600, +1500, 0 } },
        { PositionArm::Position::ClimbSet,  { 2500, +2700, 0 } },
};
#endif //PRACTICE_BOT

PositionArm::PositionArm(Position pos) :
	m_elevator(Robot::elevator.get()),
	m_arm(Robot::arm.get())
{
	m_position = pos;
	Requires(m_arm.get());
	Requires(m_elevator.get());
}

void PositionArm::Initialize() {
	const auto setpoints = m_setpoints.find(m_position);
	if (setpoints != m_setpoints.end()) {
		m_arm->SetPosition(setpoints->second.m_armSetpoint, setpoints->second.m_armDelay);
		m_elevator->SetPosition(setpoints->second.m_elevatorSetpoint);
	}
}

void PositionArm::Execute() {
}

bool PositionArm::IsFinished()
{
	const bool armDone = m_arm->AtSetpoint();
	const bool elevatorDone = m_elevator->AtSetpoint();
	return (armDone && elevatorDone);
}

void PositionArm::End() {
}

void PositionArm::Interrupted() {
 }
