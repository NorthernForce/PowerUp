#include <Commands/RunIntakeWheels.h>
#include "GenerateAutonomousSequence.h"
#include "AutonomousDrive.h"
#include "AutonomousDriveForward.h"
#include "AutonomousDriveWithEncoders.h"
#include "AutonomousTurnWithGyro.h"
#include "AutonomousWait.h"
#include "OpenGripper.h"
#include "CloseGripper.h"
#include "PositionArm.h"
#include "StartFieldPositioningSystem.h"
#include "Utilities/CommandGroupBuilder.h"
#include "Utilities/RobotNavigation.h"
#include "Utilities/CommandGroupBuilder.h"
#include "DriverStation.h"
#include "ShiftGearbox.h"

namespace {

bool ScoreOnScaleFirst(const FieldOrientation& orientation) {
	return orientation.GetStartingRobotPos() == Position::Center ||
		   orientation.GetStartingRobotPos() == orientation.GetScalePos() ||
		   orientation.GetScalePos() == orientation.GetSwitchPos();
}

frc::CommandGroup* PickupCube(const RobotNavigation& navigator, const RobotNavigation::Position startPos) {
	return BuildSequential( {
		BuildParallel( {
			new AutonomousDrive(navigator.CreatePath(startPos, RobotNavigation::Position::PickupCubeAtSwitch)),
			new PositionArm(PositionArm::Position::Pickup),
			new OpenGripper(),
			new RunIntakeWheels()
		}),
		new CloseGripper()
	});
}

frc::CommandGroup* ScoreCube(const RobotNavigation& navigator, const RobotNavigation::Position startPos, const RobotNavigation::Position finishPos, const PositionArm::Position armPos) {
	return BuildSequential({
		BuildParallel({
			new AutonomousDrive(navigator.CreatePath(startPos, finishPos)),
			BuildSequential({ new CloseGripper(), new PositionArm(armPos) })
		}),
		new OpenGripper()
	});
}
}

frc::CommandGroup* GenerateAutonomousSequence() {
	frc::CommandGroup* const sequence = new frc::CommandGroup;
	// We always start the FPS
	//sequence->AddSequential(new StartFieldPositioningSystem());
	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const FieldOrientation orientation(message);
	const RobotNavigation navigator(orientation);

	sequence->AddSequential(new CloseGripper());
//	sequence->AddSequential(new AutonomousWait(2000));
//	sequence->AddSequential(new PositionArm(PositionArm::Position::Switch));
//	sequence->AddSequential(new AutonomousDriveForward(4000, -0.8));

	// --- ## --- Goes to left scale from left side --- ## ---
//	sequence->AddSequential(new AutonomousDriveWithEncoders(3.5, 0.8));
//	sequence->AddSequential(new AutonomousTurnWithGyro(-20, 0.6));
//	sequence->AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
//	sequence->AddSequential(new AutonomousDriveWithEncoders(3.5, 0.8));


	// --- GET TO SCALE CONT OOOLALA ----

//	sequence->AddSequential(new AutonomousDriveWithEncoders(-0.5, 0.8));

	// --- ## --- !!22 ## 55 %%%%%%%%%%% 55 ## 22!! --- ## ---

//	//right scale from left side ---###----
	sequence->AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	sequence->AddSequential(new AutonomousDriveWithEncoders(5.57, 1));
	sequence->AddSequential(new AutonomousTurnWithGyro(-90, 0.8));
	sequence->AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
	sequence->AddSequential(new AutonomousDriveWithEncoders(5.2, 1));
	sequence->AddSequential(new AutonomousTurnWithGyro(90, 0.8));
	sequence->AddSequential(new AutonomousDriveWithEncoders(1.16, 1));
	sequence->AddSequential(new ShiftGearbox(ShiftGearbox::Gear::Low));




	if ((orientation.GetStartingRobotPos() == Position::Left && orientation.GetStartingRobotPos() == orientation.GetSwitchPos()) || (orientation.GetStartingRobotPos() == Position::Center && Position::Right == orientation.GetSwitchPos())) {
		sequence->AddSequential(new OpenGripper());
	}
	return sequence;

	//useful stuff for laters
	/*if (true || !orientation.IsInitialized()) {
		sequence->AddSequential(new CloseGripper());
		sequence->AddSequential(new AutonomousDrive(RobotNavigation::CreateProfile(2, 0, 0, 0)));
		return sequence;
	}

	if (ScoreOnScaleFirst(orientation)) {
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::StartingPos, RobotNavigation::Position::ScoreOnScale, PositionArm::Position::ScaleRear));
		sequence->AddSequential(PickupCube(navigator, RobotNavigation::Position::ScoreOnScale));
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::PickupCubeAtSwitch, RobotNavigation::Position::ScoreOnSwitch, PositionArm::Position::Switch));
	} else {
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::StartingPos, RobotNavigation::Position::ScoreOnSwitch, PositionArm::Position::Switch));
		sequence->AddSequential(PickupCube(navigator, RobotNavigation::Position::ScoreOnSwitch));
		sequence->AddSequential(ScoreCube(navigator, RobotNavigation::Position::PickupCubeAtSwitch, RobotNavigation::Position::ScoreOnScale, PositionArm::Position::ScaleRear));
	}

	return sequence;*/
}
