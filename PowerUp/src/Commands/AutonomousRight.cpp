#include "AutonomousRight.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

AutonomousRight::AutonomousRight()
{
	FieldOrientation::SetStartingRobotCoordinate(Position::Right, { FieldOrientation::FieldWidth - FieldOrientation::StartCoordX, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
	AddSequential(GenerateAutonomousSequence());
}
