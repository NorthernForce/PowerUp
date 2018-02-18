#include "GenerateAutonomousSequence.h"
#include "AutonomousDrive.h"
#include "OpenGripper.h"
#include "CloseGripper.h"
#include "RunIntake.h"
#include "PositionArm.h"
#include "StartFieldPositioningSystem.h"

#include "Utilities/CommandGroupBuilder.h"
#include "Utilities/RobotNavigation.h"
#include "Utilities/CommandGroupBuilder.h"
#include "DriverStation.h"

namespace
{

bool ScoreOnScaleFirst(const FieldOrientation& orientation)
{
	return orientation.GetStartingRobotPos() == Position::Center ||
			orientation.GetStartingRobotPos() == orientation.GetScalePos() ||
			orientation.GetScalePos() == orientation.GetSwitchPos();
}

/**
 * Generates the following sequence
 * 	Drives to the cube while
 * 	  positioning the arm to the pickup position while
 * 	  opening the griper while
 * 	  starting the in-take wheels
 * 	and then
 * 	  closes the gripper
 */
frc::CommandGroup* PickupCube(const RobotNavigation& navigator, const RobotNavigation::Position startPos)
{
	return BuildSequential({
		BuildParallel({
			new AutonomousDrive(navigator, startPos, RobotNavigation::Position::PickupCubeAtSwitch),
			new PositionArm(PositionArm::Position::Pickup),
			new OpenGripper(),
			new RunIntake()
		}),
		new CloseGripper()
	});
}

/**
 * Generates the following sequence
 * 	Drives to the finish position while
 * 	  closing the gripper and then positioning the arm to the score position
 * 	and then
 * 	  opens the gripper
 */
frc::CommandGroup* ScoreCube(const RobotNavigation& navigator, const RobotNavigation::Position startPos, const RobotNavigation::Position finishPos, const PositionArm::Position armPos)
{
	return BuildSequential({
		BuildParallel({
			new AutonomousDrive(navigator, startPos, finishPos),
			BuildSequential({ new CloseGripper(), new PositionArm(armPos) })
		}),
		new OpenGripper()
	});
}

}

frc::CommandGroup* GenerateAutonomousSequence()
{
	frc::CommandGroup* const sequence = new frc::CommandGroup;

	// We always start the FPS
	sequence->AddSequential(new StartFieldPositioningSystem());

	const FieldOrientation orientation;
	if (!orientation.IsInitialized())
	{
		DriverStation::ReportError("Field orientation is not known - autonomous sequence cannot be generated");
		sequence->AddSequential(new CloseGripper());
		return sequence;
	}

	const RobotNavigation navigator(orientation);
	if (ScoreOnScaleFirst(orientation))
	{
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::StartingPos, RobotNavigation::Position::ScoreOnScale, PositionArm::Position::ScaleRear));
		sequence->AddSequential(PickupCube(navigator, RobotNavigation::Position::ScoreOnScale));
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::PickupCubeAtSwitch, RobotNavigation::Position::ScoreOnSwitch, PositionArm::Position::Switch));
	}
	else
	{
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::StartingPos, RobotNavigation::Position::ScoreOnSwitch, PositionArm::Position::Switch));
		sequence->AddSequential(PickupCube(navigator, RobotNavigation::Position::ScoreOnSwitch));
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::PickupCubeAtSwitch, RobotNavigation::Position::ScoreOnScale, PositionArm::Position::ScaleRear));
	}

	return sequence;
}
