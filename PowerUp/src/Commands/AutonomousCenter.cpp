#include "AutonomousCenter.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

AutonomousCenter::AutonomousCenter()
{
	FieldOrientation::SetStartingRobotCoordinate({ FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
	AddSequential(GenerateAutonomousSequence());
}
