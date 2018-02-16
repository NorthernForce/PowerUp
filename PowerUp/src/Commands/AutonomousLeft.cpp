#include "AutonomousLeft.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

AutonomousLeft::AutonomousLeft()
{
	FieldOrientation::SetStartingRobotCoordinate({ FieldOrientation::StartCoordX, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
	AddSequential(GenerateAutonomousSequence());
}
