#include "StartFieldPositioningSystem.h"
#include "Subsystems/FieldPositioningSystem.h"
#include "Utilities/FieldOrientation.h"

StartFieldPositioningSystem::StartFieldPositioningSystem() :
		frc::Command()
{
}

// Called just before this Command runs the first time
void StartFieldPositioningSystem::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StartFieldPositioningSystem::Execute()
{
	const auto& coord = FieldOrientation::GetStartingRobotCoordinate();
	Robot::fieldPositioningSystem->Start(frc::Vector2d(coord.x, coord.y), coord.heading);
}

// Make this return true when this Command no longer needs to run execute()
bool StartFieldPositioningSystem::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void StartFieldPositioningSystem::End()
{
	Robot::fieldPositioningSystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StartFieldPositioningSystem::Interrupted()
{

}
