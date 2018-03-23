#include "CrossAutoLine.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"
#include "Utilities/RobotNavigation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/AutonomousWait.h"
#include "Commands/PositionArm.h"
#include "Commands/CloseGripper.h"

CrossAutoLine::CrossAutoLine() {
	AddSequential(new CloseGripper());
	AddSequential(new PositionArm(PositionArm::Position::Switch));
	AddSequential(new AutonomousDriveForward(3500, -0.8));
	AddSequential(new AutonomousWait(500));
	AddSequential(new CloseGripper());
}
