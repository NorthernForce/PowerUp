#include <Commands/RobotClimb.h>

ElevatorClimb::ElevatorClimb() {
	Requires(Robot::elevator.get());
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ElevatorClimb::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorClimb::Execute()  {
	Robot::elevator->BeginClimb();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorClimb::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorClimb::End() {
	Robot::elevator->EndClimb();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorClimb::Interrupted() {
	Robot::elevator->EndClimb();
}
