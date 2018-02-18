#include "CloseGripper.h"

CloseGripper::CloseGripper() : frc::TimedCommand(timeToClose) {
	Requires(Robot::gripper.get());
}

// Called just before this Command runs the first time
void CloseGripper::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CloseGripper::Execute() {
}

// Called once after command times out
void CloseGripper::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CloseGripper::Interrupted() {

}
