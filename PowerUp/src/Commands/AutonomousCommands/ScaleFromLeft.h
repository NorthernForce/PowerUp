#ifndef SCALEFROMLEFT_H
#define SCALEFROMLEFT_H

#include "Commands/CommandGroup.h"
#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"
#include "Utilities/RobotNavigation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/PositionArm.h"

class ScaleFromLeft: public frc::CommandGroup
{
public:
	ScaleFromLeft() : frc::CommandGroup("Scale Autonomous From Left Side")
	{
		const auto& ds = DriverStation::GetInstance();
		const auto& message = ds.GetGameSpecificMessage();
		const FieldOrientation orientation(message);
		const RobotNavigation navigator(orientation);

		//FieldOrientation::SetStartingRobotCoordinate(Position::Center, { FieldOrientation::FieldWidth / 2, FieldOrientation::StartCoordY, FieldOrientation::StartCoordHeading });
		//if robot starts on left side and scale is on left side..
		AddSequential(new AutonomousDriveWithEncoders(3.5, 0.8));
		if(orientation.GetStartingRobotPos() == Position::Left && orientation.GetStartRobotPos() == orientation.GetScalePos()) {
			AddSequential(new AutonomousTurnWithGyro(-20, 0.6));
			AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
			AddSequential(new AutonomousDriveWithEncoders(3.5, 0.8));
		} else if(orientation.GetStartingRobotPos() == Position::Left && orientation.GetStartingPos() != orientation.GetScalePos()) { //if robot starts on left side and scale is on right side..
			//TODO: autonomous code for right-side-scale from left side
		}
			AddSequential(new AutonomousWait(500));
			AddSequential(new OpenGripper());
			AddSequential(new AutonomousWait(500));

	}
};

#endif
