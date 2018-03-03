#include "Commands/RobotClimb.h"

//Change from ElevatorClimb to RobotClimb

ElevatorClimb::ElevatorClimb() {
	Requires(Robot::elevator.get());
	Requires(Robot::arm.get());
}

void ElevatorClimb::Initialize() {
	Robot::elevator->BeginClimb();
	Robot::arm->ReducePowerForClimb();
}

void ElevatorClimb::Execute()  {
}

bool ElevatorClimb::IsFinished() {
	return false;
}

void ElevatorClimb::End() {
	Robot::elevator->EndClimb();
}

void ElevatorClimb::Interrupted() {
	Robot::elevator->EndClimb();
}
