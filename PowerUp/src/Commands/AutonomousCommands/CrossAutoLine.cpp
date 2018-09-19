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
//	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	AddSequential(new AutonomousDriveWithEncoders(13, 1));
}
