#include "Commands/RobotClimb.h"

//Change from RobotClimb to RobotClimb

RobotClimb::RobotClimb() {
	Requires(Robot::elevator.get());
	Requires(Robot::arm.get());
}

void RobotClimb::Initialize() {
	Robot::elevator->BeginClimb();
	Robot::arm->ReducePowerForClimb();
}

void RobotClimb::Execute()  {
}

bool RobotClimb::IsFinished() {
	return false;
}

void RobotClimb::End() {
	Robot::elevator->EndClimb();
}

void RobotClimb::Interrupted() {
	Robot::elevator->EndClimb();
}
