#include "CrossAutoLine.h"

#include "DriverStation.h"
#include "Utilities/FieldOrientation.h"
#include "Utilities/RobotNavigation.h"
#include "Commands/AutonomousDriveWithEncoders.h"
#include "Commands/AutonomousTurnWithGyro.h"
#include "Commands/AutonomousWait.h"
#include "Commands/PositionArm.h"
#include "Commands/CloseGripper.h"
#include "Commands/ShiftGearbox.h"

CrossAutoLine::CrossAutoLine() {
//	AddSequential(new CloseGripper());
//	AddSequential(new PositionArm(PositionArm::Position::Switch));
//	AddSequential(new AutonomousDriveForward(5500, -0.8));
//	AddSequential(new AutonomousWait(500));
//	AddSequential(new CloseGripper());



	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	AddSequential(new AutonomousWait(500));
	AddSequential(new AutonomousTurnWithGyro(45));
	AddSequential(new AutonomousWait(500));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::Low));
}
