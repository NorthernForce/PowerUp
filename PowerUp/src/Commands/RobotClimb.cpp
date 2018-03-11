#include "Commands/RobotClimb.h"

//Change from RobotClimb to RobotClimb

RobotClimb::RobotClimb() {
	Requires(Robot::elevator.get());
	Requires(Robot::arm.get());
}

void RobotClimb::Initialize() {
	Robot::elevator->EnableVoltageCompensation(false);
	Robot::arm->EnableVoltageCompensation(false);
	Robot::arm->ReducePowerForClimb();
	Robot::elevator->BeginClimb();
}

void RobotClimb::Execute()  {
}

bool RobotClimb::IsFinished() {
	return false;
}

void RobotClimb::End() {
	Robot::elevator->EnableVoltageCompensation(true);
	Robot::arm->EnableVoltageCompensation(true);
	Robot::elevator->EndClimb();
}

void RobotClimb::Interrupted() {
	Robot::elevator->EnableVoltageCompensation(true);
	Robot::arm->EnableVoltageCompensation(true);
	Robot::elevator->EndClimb();
}
