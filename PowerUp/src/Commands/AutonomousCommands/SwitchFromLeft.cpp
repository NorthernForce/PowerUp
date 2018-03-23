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

SwitchFromLeft::SwitchFromLeft() {
	AddSequential(new CloseGripper());
	AddSequential(new PositionArm(PositionArm::Position::Switch));
	AddSequential(new AutonomousDriveForward(4000, -0.8));
	AddSequential(new AutonomousTurnWithGyro(-90, 0.35));
	AddSequential(new AutonomousDriveForward(1500, -0.6));
	AddSequential(new AutonomousWait(500));
	AddSequential(new OpenGripper());
	AddSequential(new AutonomousWait(500));
	AddSequential(new CloseGripper());
}
