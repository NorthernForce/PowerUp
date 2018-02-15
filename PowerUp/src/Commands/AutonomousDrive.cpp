#include <Commands/AutonomousDrive.h>

AutonomousDrive::AutonomousDrive(const RobotNavigation& navigation,
		const RobotNavigation::Position start,
		const RobotNavigation::Position finish) :
		frc::Command(""), m_navigation(navigation), m_start(start), m_finish(
				finish)
{
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void AutonomousDrive::Initialize()
{
	// ->clearMotionProfileHasUnderrun(0);
	// ->clearMotionProfileTrajectories();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDrive::Execute()
{
	// Extract the next motion profile points
	// push the points to the left and right talons ->pushMotionProfileTrajectory
	// Call talons to process motion profile buffer ->processMotionProfileBuffer
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AutonomousDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDrive::Interrupted()
{

}
