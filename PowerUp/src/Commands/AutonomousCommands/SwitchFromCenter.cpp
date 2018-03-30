#include "SwitchFromCenter.h"

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

SwitchFromCenter::SwitchFromCenter() {
	const auto& ds = DriverStation::GetInstance();
	const auto& message = ds.GetGameSpecificMessage();
	const FieldOrientation orientation(message);

	AddSequential(new CloseGripper());
	AddSequential(new PositionArm(PositionArm::Position::Switch));
	AddSequential(new AutonomousDriveForward(800, -0.8));
	if (orientation.GetSwitchPos() == Position::Right) {
		AddSequential(new AutonomousTurnWithGyro(-45));
		AddSequential(new AutonomousDriveForward(2000, -0.8));
		AddSequential(new AutonomousTurnWithGyro(45));
	}
	else {
		AddSequential(new AutonomousTurnWithGyro(45));
		AddSequential(new AutonomousDriveForward(2000, -0.8));
		AddSequential(new AutonomousTurnWithGyro(-45));
	}
	AddSequential(new AutonomousDriveForward(1500, -0.6));
	AddSequential(new AutonomousWait(500));
	if (message != "")
		AddSequential(new OpenGripper());
	AddSequential(new AutonomousWait(500));
	AddSequential(new CloseGripper());
}
