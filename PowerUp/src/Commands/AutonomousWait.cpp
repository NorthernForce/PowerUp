#include "AutonomousWait.h"
#include "WPILib.h"

AutonomousWait::AutonomousWait(int timeToWaitMs) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	duration = timeToWaitMs;
	counter = 0;
}

// Called just before this Command runs the first time
void AutonomousWait::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void AutonomousWait::Execute() {
	counter++;
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousWait::IsFinished() {
//	DriverStation::ReportWarning(std::to_string(counter) + " counts remaining");
	return (counter*20 >= duration);
}

// Called once after isFinished returns true
void AutonomousWait::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousWait::Interrupted() {

}
