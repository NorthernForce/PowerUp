#include "FarScaleFromLeft.h"

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

FarScaleFromLeft::FarScaleFromLeft() {
	AddSequential(new CloseGripper());
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	AddSequential(new PositionArm(PositionArm::Position::ScaleFront));
	AddSequential(new AutonomousDriveWithEncoders(6, 0.8));
	AddSequential(new AutonomousWait(200));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::Low));
	AddSequential(new AutonomousWait(200));
	AddSequential(new AutonomousTurnWithGyro(-75, 1));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	AddSequential(new AutonomousDriveWithEncoders(7, 0.8));
	AddSequential(new AutonomousWait(200));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::Low));
	AddSequential(new AutonomousWait(200));
	AddSequential(new AutonomousTurnWithGyro(90, 1));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::High));
	AddSequential(new AutonomousDriveWithEncoders(1.3, 0.8));
	AddSequential(new AutonomousWait(500));
	AddSequential(new OpenGripper());
	AddSequential(new AutonomousWait(500));
	AddSequential(new AutonomousDriveWithEncoders(-1, 0.6));
	AddSequential(new PositionArm(PositionArm::Position::Pickup));
	AddSequential(new CloseGripper());
	AddSequential(new AutonomousWait(500));
	AddSequential(new ShiftGearbox(ShiftGearbox::Gear::Low));
}
