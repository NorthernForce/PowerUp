// #include "StartFieldPositioningSystem.h"
// #include "Subsystems/FieldPositioningSystem.h"
// #include "Utilities/FieldOrientation.h"

// StartFieldPositioningSystem::StartFieldPositioningSystem() :
// 	frc::Command() {
// }
// void StartFieldPositioningSystem::Initialize() {

// }

// void StartFieldPositioningSystem::Execute() {
// 	const auto& coord = FieldOrientation::GetStartingRobotCoordinate();
// 	Robot::fieldPositioningSystem->Start(frc::Vector2d(coord.x, coord.y), coord.heading);
// }

// bool StartFieldPositioningSystem::IsFinished() {
// 	return false;
// }

// void StartFieldPositioningSystem::End() {
// 	Robot::fieldPositioningSystem->Stop();
// }

// void StartFieldPositioningSystem::Interrupted() {
// }
