#ifndef SCALEFROMLEFT_H
#define SCALEFROMLEFT_H

#include "Commands/CommandGroup.h"
#include "Utilities/FieldOrientation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/PositionArm.h"

class ScaleFromLeft: public frc::CommandGroup
{
public:
	ScaleFromLeft() : frc::CommandGroup("Scale Autonomous From Left Side")
	{
		FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		//TODO: this sequence only does left side scale from left side, add right side scale
		AddSequential(new AutonomousDriveWithEncoders(3.5, 0.8));
		AddSequential(new AutonomousTurnWithGyro(-20, 0.6));
		AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
		AddSequential(new AutonomousDriveWithEncoders(3.5, 0.8));

	}
};

#endif
