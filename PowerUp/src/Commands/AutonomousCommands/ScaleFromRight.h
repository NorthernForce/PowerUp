#ifndef SCALEFROMRIGHT_H
#define SCALEFROMRIGHT_H

#include "Commands/CommandGroup.h"
#include "Utilities/FieldOrientation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/PositionArm.h"


class ScaleFromRight: public frc::CommandGroup
{
public:
	ScaleFromRight() : frc::CommandGroup("Scale Autonomous From Right Side")
	{
		FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		//build sequentials here
		//AddSequential(null);

	}
};

#endif
