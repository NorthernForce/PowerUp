#ifndef AUTONOMOUSLEFT_H
#define AUTONOMOUSLEFT_H

#include "Commands/CommandGroup.h"
#include "AutonomousLeft.h"
#include "GenerateAutonomousSequence.h"
#include "Utilities/FieldOrientation.h"

class AutonomousLeft: public frc::CommandGroup
{
public:
	AutonomousLeft() : frc::CommandGroup("Autonomous Left")
	{
		FieldOrientation::SetStartingRobotCoordinate(Position::Left, { FieldOrientation::StartCoordX, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		AddSequential(GenerateAutonomousSequence());
	}

};

#endif
