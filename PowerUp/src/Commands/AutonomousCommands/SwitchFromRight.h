#ifndef SWITCHFROMRIGHT_H
#define SWITCHFROMRIGHT_H

#include "Commands/CommandGroup.h"
#include "Utilities/FieldOrientation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/PositionArm.h"


class SwitchFromRight: public frc::CommandGroup
{
public:
	SwitchFromRight() : frc::CommandGroup("Switch Autonomous From Right Side")
	{
		FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		//build sequentials here
		//AddSequential(null);

	}
};

#endif
