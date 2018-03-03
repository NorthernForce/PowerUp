#include "AutonomousDriveForward.h"

AutonomousDriveForward::AutonomousDriveForward(int timeToTravel, double speedToMove) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	timer = 0;
	// Execute() runs every 20 ms, so ... :{D
	time = timeToTravel/20;
	speed = speedToMove;
}

// Called just before this Command runs the first time
void AutonomousDriveForward::Initialize() {
	Robot::driveTrain->SetSafetyEnabled(false);
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveForward::Execute() {
	printf("speed: %f timer: %i time: %i\n", speed, timer, time);
	Robot::driveTrain->SetSafetyEnabled(false);
	Robot::driveTrain->ArcadeDrive(0, speed, true);
	timer++;
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveForward::IsFinished() {
	return (timer >= time);
}

// Called once after isFinished returns true
void AutonomousDriveForward::End() {
	Robot::driveTrain->SetSafetyEnabled(false);
	Robot::driveTrain->ArcadeDrive(0, 0, true);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveForward::Interrupted() {
	Robot::driveTrain->ArcadeDrive(0, 0, true);
}
