#include "PositionArm.h"

const std::map<PositionArm::Position, int> PositionArm::m_setpoints = {
		{ PositionArm::Position::Retracted, 0 },
		{ PositionArm::Position::Pickup, 500 },
		{ PositionArm::Position::Switch, 1050 },
		{ PositionArm::Position::ScaleFront, 1800 },
		{ PositionArm::Position::ScaleRear, 2100 },
};

PositionArm::PositionArm(Position setpoint): frc::Command()
{
    m_setpoint = setpoint;
	Requires(Robot::arm.get());
}

// Called just before this Command runs the first time
void PositionArm::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void PositionArm::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool PositionArm::IsFinished() {
    return Robot::arm->AtSetpoint();
}

// Called once after isFinished returns true
void PositionArm::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionArm::Interrupted() {

}
