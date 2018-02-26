#include "AutonomousLeft.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

AutonomousLeft::AutonomousLeft()
{
	FieldOrientation::SetStartingRobotCoordinate(Position::Left, { FieldOrientation::StartCoordX, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
	AddSequential(GenerateAutonomousSequence());
}
