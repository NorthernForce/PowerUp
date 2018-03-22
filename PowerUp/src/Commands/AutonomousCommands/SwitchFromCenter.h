#ifndef SWITCHFROMCENTER_H
#define SWITCHFROMCENTER_H

#include "Commands/CommandGroup.h"
#include "Utilities/FieldOrientation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/PositionArm.h"


class SwitchFromCenter: public frc::CommandGroup
{
public:
	SwitchFromCenter() : frc::CommandGroup("Switch Autonomous From Center")
	{
		FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		//build sequentials here
		//AddSequential(null);

	}
};

#endif
