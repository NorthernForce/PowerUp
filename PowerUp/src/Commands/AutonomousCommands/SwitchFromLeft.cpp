#include "SwitchFromLeft.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"
#include "Utilities/RobotNavigation.h"
#include "Commands/AutonomousDriveForward.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/AutonomousWait.h"
#include "Commands/PositionArm.h"
#include "Commands/CloseGripper.h"
#include "Commands/OpenGripper.h"
#include "Commands/ShiftGearbox.h"

SwitchFromLeft::SwitchFromLeft() {}

void SwitchFromLeft::Initialize() {
	for (int time = 0; time <= 500; time++) {
		if (DriverStation::GetInstance().GetGameSpecificMessage() == "")
			break;
		Wait(0.01);
	}

	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const FieldOrientation orientation(message);

	AddSequential(new CloseGripper());
	AddSequential(new PositionArm(PositionArm::Position::Switch));
	AddSequential(new AutonomousDriveForward(4000, -0.8));
	if (orientation.GetSwitchPos() == Position::Left) {
		AddSequential(new AutonomousTurnWithGyro(-90, 0.35));
		AddSequential(new AutonomousDriveForward(800, -0.6));
		AddSequential(new AutonomousWait(500));
		AddSequential(new OpenGripper());
	}
	AddSequential(new AutonomousWait(500));
	AddSequential(new CloseGripper());
}
