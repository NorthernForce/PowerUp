#include "AutonomousCenter.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

AutonomousCenter::AutonomousCenter()
{
	FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
	printf("Auto Center Being Run!");
	AddSequential(GenerateAutonomousSequence());

}
