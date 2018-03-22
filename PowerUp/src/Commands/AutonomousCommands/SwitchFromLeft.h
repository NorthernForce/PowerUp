#ifndef SWITCHFROMLEFT_H
#define SWITCHFROMLEFT_H

#include "Commands/CommandGroup.h"
#include "Utilities/FieldOrientation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/PositionArm.h"


class SwitchFromLeft: public frc::CommandGroup
{
public:
	SwitchFromLeft() : frc::CommandGroup("Switch Autonomous From Left Side")
	{
		FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		//build sequentials here
		//AddSequential(null);

	}
};

#endif
