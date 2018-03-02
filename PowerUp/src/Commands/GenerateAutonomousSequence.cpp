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
			new AutonomousDrive(navigator.CreatePath(startPos, RobotNavigation::Position::PickupCubeAtSwitch)),
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
			new AutonomousDrive(navigator.CreatePath(startPos, finishPos)),
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
//	sequence->AddSequential(new StartFieldPositioningSystem());

	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();

	const FieldOrientation orientation(message);
	const RobotNavigation navigator(orientation);

	if ((orientation.GetStartingRobotPos() == Position::Left && orientation.GetStartingRobotPos() == orientation.GetSwitchPos()) || (orientation.GetStartingRobotPos() == Position::Center && Position::Right == orientation.GetSwitchPos())) {
		sequence->AddSequential(new CloseGripper());
		sequence->AddSequential(new PositionArm(PositionArm::Position::Switch));
		sequence->AddParallel(new AutonomousDrive(RobotNavigation::CreateProfile(.25, 0, 0, 0)));
		sequence->AddSequential(new OpenGripper());
		return sequence;
	}

	if (true || !orientation.IsInitialized())
	{
		sequence->AddSequential(new CloseGripper());
		sequence->AddSequential(new AutonomousDrive(RobotNavigation::CreateProfile(2, 0, 0, 0)));
		return sequence;
	}

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
