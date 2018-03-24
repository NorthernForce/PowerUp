#include "ScaleFromRight.h"

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

#include "Commands/AutonomousCommands/SwitchFromRight.h"
#include "Commands/AutonomousCommands/CrossAutoLine.h"

ScaleFromRight::ScaleFromRight() {
	AddSequential(new CloseGripper());
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
	AddSequential(new AutonomousDriveWithEncoders(3, 0.6));
	AddSequential(new AutonomousTurnWithGyro(20, 0.4));
	AddSequential(new AutonomousDriveWithEncoders(3.2, 0.6));
	AddSequential(new AutonomousWait(500));
	AddSequential(new OpenGripper());
	AddSequential(new AutonomousWait(500));
	AddSequential(new AutonomousDriveWithEncoders(-1, 0.6));
	AddSequential(new CloseGripper());
	AddSequential(new PositionArm(PositionArm::Position::Pickup));
	AddSequential(new AutonomousWait(500));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::Low));
}
