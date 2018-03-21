#include "AutonomousCenter.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

AutonomousCenter::AutonomousCenter() : frc::CommandGroup("Autonomous Center")
{
	FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
	AddSequential(GenerateAutonomousSequence());

}
