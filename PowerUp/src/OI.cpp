// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCenter.h"
#include "Commands/AutonomousLeft.h"
#include "Commands/AutonomousRight.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/RunIntake.h"
#include "Commands/StartFieldPositioningSystem.h"
#include "Commands/PositionArm.h"
#include "Commands/ShiftGearbox.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

#include "Commands/PositionArm.h"
#include "Commands/SetArmHomePosition.h"
#include "Commands/SetElevatorHomePosition.h"
#include "Commands/NudgeElevator.h"
#include "Commands/NudgeArm.h"
#include "Commands/OpenGripper.h"
#include "Commands/CloseGripper.h"
#include "Commands/ElevatorBrake.h"

namespace
{
	void WhenPressed(const std::shared_ptr<frc::Joystick>& joystick, int button, frc::Command* command) {
		auto joystickButton = new JoystickButton(joystick.get(), button);
		joystickButton->WhenPressed(command);
	}

	void WhenReleased(const std::shared_ptr<frc::Joystick>& joystick, int button, frc::Command* command) {
		auto joystickButton = new JoystickButton(joystick.get(), button);
		joystickButton->WhenReleased(command);
	}

	void WhileHeld(const std::shared_ptr<frc::Joystick>& joystick, int button, frc::Command* command) {
		auto joystickButton = new JoystickButton(joystick.get(), button);
		joystickButton->WhileHeld(command);
	}
}

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driverController.reset(new frc::XboxController(0));
	driverJoystick.reset(new frc::Joystick(0));
    manipulatorJoystick.reset(new frc::Joystick(1));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("RunIntake", new RunIntake());
    frc::SmartDashboard::PutData("DriveWithJoystick", new DriveWithJoystick());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    frc::SmartDashboard::PutData("Move arm to start position", new PositionArm(PositionArm::Position::Retracted));
    frc::SmartDashboard::PutData("Move arm to pickup", new PositionArm(PositionArm::Position::Pickup));
    frc::SmartDashboard::PutData("Move arm to switch", new PositionArm(PositionArm::Position::Switch));
    frc::SmartDashboard::PutData("Move arm to scale front", new PositionArm(PositionArm::Position::ScaleFront));
    frc::SmartDashboard::PutData("Move arm to scale rear", new PositionArm(PositionArm::Position::ScaleRear));
    frc::SmartDashboard::PutData("Move arm to climb setup", new PositionArm(PositionArm::Position::ClimbSet));
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
    //frc::SmartDashboard::PutNumber("elevation position from home", 0.0);

    // https://www.chiefdelphi.com/forums/showpost.php?p=1003245&postcount=8 for button assignments

    //Driver Controls
    WhenPressed(driverJoystick, 6, new ShiftGearbox(ShiftGearbox::Gear::Low));
    WhenReleased(driverJoystick, 6, new ShiftGearbox(ShiftGearbox::Gear::High));

    //Manipulator Controls
    WhileHeld(manipulatorJoystick, 1, new OpenGripper());
    WhenReleased(manipulatorJoystick, 1, new CloseGripper());
    WhileHeld(manipulatorJoystick, 2, new NudgeElevator(-3));
    WhileHeld(manipulatorJoystick, 3, new NudgeElevator(+3));
    WhenPressed(manipulatorJoystick, 4, new PositionArm(PositionArm::Position::ClimbSet));
    WhenPressed(manipulatorJoystick, 5, new PositionArm(PositionArm::Position::ClimbExecute));
    WhenPressed(manipulatorJoystick, 6, new PositionArm(PositionArm::Position::Pickup));
    WhenPressed(manipulatorJoystick, 7, new PositionArm(PositionArm::Position::Switch));
    WhenPressed(manipulatorJoystick, 9, new PositionArm(PositionArm::Position::Retracted));
    WhenPressed(manipulatorJoystick, 10, new PositionArm(PositionArm::Position::ScaleRear));
    WhenPressed(manipulatorJoystick, 11, new PositionArm(PositionArm::Position::ScaleFront));
    //This is untested. If it doesn't work try putting it directly in teleop periodic. Values may need to be tuned.
    if (manipulatorJoystick->GetY() > 0) {
    	NudgeArm(+1);
    } else if (manipulatorJoystick->GetY() < 0) {
    	NudgeArm(-1);
    }
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

const std::shared_ptr<frc::Joystick>& OI::getManipulatorJoystick() {
	return manipulatorJoystick;
}

const std::shared_ptr<frc::Joystick>& OI::getDriverJoystick() {
	return driverJoystick;
}

const std::shared_ptr<frc::XboxController>& OI::getDriverController() {
	return driverController;
}
