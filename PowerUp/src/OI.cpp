#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCenter.h"
#include "Commands/AutonomousLeft.h"
#include "Commands/AutonomousRight.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/RunIntake.h"
#include "Commands/StartFieldPositioningSystem.h"
#include "Commands/PositionArm.h"
#include "Commands/ShiftGearbox.h"
#include "Commands/RobotClimb.h"
#include "Commands/PositionArm.h"
#include "Commands/SetArmHomePosition.h"
#include "Commands/SetElevatorHomePosition.h"
#include "Commands/NudgeElevator.h"
#include "Commands/NudgeArm.h"
#include "Commands/OpenGripper.h"
#include "Commands/CloseGripper.h"
#include "Commands/ElevatorBrake.h"

namespace {
	void WhenPressed(const std::shared_ptr<frc::GenericHID>& joystick, int button, frc::Command* command) {
		auto joystickButton = new JoystickButton(joystick.get(), button);
		joystickButton->WhenPressed(command);
	}

	void WhenReleased(const std::shared_ptr<frc::GenericHID>& joystick, int button, frc::Command* command) {
		auto joystickButton = new JoystickButton(joystick.get(), button);
		joystickButton->WhenReleased(command);
	}

	void WhileHeld(const std::shared_ptr<frc::GenericHID>& joystick, int button, frc::Command* command) {
		auto joystickButton = new JoystickButton(joystick.get(), button);
		joystickButton->WhileHeld(command);
	}
}

OI::OI() {
	driverController.reset(new frc::XboxController(0));
    manipulatorJoystick.reset(new frc::Joystick(1));
    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("RunIntake", new RunIntake());
    frc::SmartDashboard::PutData("DriveWithJoystick", new DriveWithJoystick());
    //Call this pos home instead of retracted
    frc::SmartDashboard::PutData("Move arm to start position", new PositionArm(PositionArm::Position::Retracted));
    frc::SmartDashboard::PutData("Move arm to pickup", new PositionArm(PositionArm::Position::Pickup));
    frc::SmartDashboard::PutData("Move arm to switch", new PositionArm(PositionArm::Position::Switch));
    frc::SmartDashboard::PutData("Move arm to scale front", new PositionArm(PositionArm::Position::ScaleFront));
    frc::SmartDashboard::PutData("Move arm to scale rear", new PositionArm(PositionArm::Position::ScaleRear));
    frc::SmartDashboard::PutData("Move arm to climb setup", new PositionArm(PositionArm::Position::ClimbSet));
    //TODO: fix description -> should not be PositionArm - > RobotClimb
    frc::SmartDashboard::PutData("Climb using arm and elevator", new PositionArm(PositionArm::Position::ClimbExecute));
    frc::SmartDashboard::PutData("Nudge elevator up", new NudgeElevator(+3));
    frc::SmartDashboard::PutData("Nudge elevator down", new NudgeElevator(-3));
    //These arm values may need to be tuned
    frc::SmartDashboard::PutData("Nudge arm up", new NudgeArm(+1));
    frc::SmartDashboard::PutData("Nudge arm down", new NudgeArm(-1));
    frc::SmartDashboard::PutData("Shift High", new ShiftGearbox(ShiftGearbox::Gear::High));
    frc::SmartDashboard::PutData("Shift Low", new ShiftGearbox(ShiftGearbox::Gear::Low));
	frc::SmartDashboard::PutData("Open gripper", new OpenGripper());
	frc::SmartDashboard::PutData("Close gripper", new CloseGripper());
	frc::SmartDashboard::PutData("Break elevator", new ElevatorBreak(ElevatorBreak::State::BrakeOn));
	frc::SmartDashboard::PutData("Release elevator", new ElevatorBreak(ElevatorBreak::State::BrakeOff));
	frc::SmartDashboard::PutData("**Reset arm home position**", new SetArmHomePosition());
    frc::SmartDashboard::PutData("**Reset elevator home position**", new SetElevatorHomePosition());

    //TODO: switch to using enums for joystick buttons

    //Driver controls
    WhenPressed(driverController, 6, new ShiftGearbox(ShiftGearbox::Gear::High));
    WhenReleased(driverController, 6, new ShiftGearbox(ShiftGearbox::Gear::Low));
    //Manipulator controls
    WhileHeld(manipulatorJoystick, 1, new OpenGripper());
    WhenReleased(manipulatorJoystick, 1, new CloseGripper());
    WhileHeld(manipulatorJoystick, 2, new NudgeElevator(-3));
    WhileHeld(manipulatorJoystick, 3, new NudgeElevator(+3));
    WhenPressed(manipulatorJoystick, 4, new PositionArm(PositionArm::Position::ClimbSet));
    WhileHeld(manipulatorJoystick, 5, new ElevatorClimb());
    WhenPressed(manipulatorJoystick, 6, new PositionArm(PositionArm::Position::Pickup));
    WhenPressed(manipulatorJoystick, 7, new PositionArm(PositionArm::Position::Switch));
    WhenPressed(manipulatorJoystick, 9, new PositionArm(PositionArm::Position::Retracted));
    WhenPressed(manipulatorJoystick, 10, new PositionArm(PositionArm::Position::ScaleRear));
    WhenPressed(manipulatorJoystick, 11, new PositionArm(PositionArm::Position::ScaleFront));
    //TODO: fix this
    /*if (manipulatorJoystick->GetY() > 0) {
    	NudgeArm(+1);
    } else if (manipulatorJoystick->GetY() < 0) {
    	NudgeArm(-1);
    }*/
}

const std::shared_ptr<frc::Joystick>& OI::getManipulatorJoystick() {
	return manipulatorJoystick;
}

const std::shared_ptr<frc::XboxController>& OI::getDriverController() {
	return driverController;
}
