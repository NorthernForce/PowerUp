/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "Robot.h"
#include <frc/WPILib.h>
#include <frc/buttons/JoystickButton.h>

#include "commands/NudgeElevator.h"
#include "commands/ShiftGear.h"
#include "commands/PositionArm.h"
#include "commands/OpenGripper.h"
#include "commands/CloseGripper.h"
#include "commands/NudgeArm.h"
#include "commands/ElevatorBrake.h"
#include "commands/RobotClimb.h"
#include "commands/SetArmHomePosition.h"
#include "commands/SetElevatorHomePosition.h"
#include "commands/SetGripperIntake.h"
#include "commands/StartIntakeWheels.h"
#include "commands/StopIntakeWheels.h"
#include "commands/MoveElevator.h"
#include "triggers/ComboControl.h"
#include "triggers/RawAxis.h"
#include "triggers/RawButton.h"
#include "RobotMap.h"

namespace {
	void WhenPressed(frc::Trigger* trigger, frc::Command* command) {
		trigger->WhenActive(command);
	}

	void WhenReleased(frc::Trigger* trigger, frc::Command* command) {
		trigger->WhenInactive(command);
	}

	void WhileHeld(frc::Trigger* trigger, frc::Command* command) {
		trigger->WhileActive(command);
	}
}

OI::OI() {
  /* Initialize Controllers */
   m_driverController.reset(new frc::XboxController(RobotMap::Controls::k_driverController_id));
   m_manipulatorJoystick.reset(new frc::Joystick(RobotMap::Controls::k_manipulatorJoystick_id));

  /* SmartDashboard Controls */
	/* Driver Controls */
	 frc::SmartDashboard::PutNumber("Driver: Speed", 1);
	//  frc::SmartDashboard::PutData("Gearbox: Shift High", new ShiftGear(ShiftGear::Gear::High));
	//  frc::SmartDashboard::PutData("Gearbox: Shift Low", new ShiftGear(ShiftGear::Gear::Low));

	/* Arm Controls */
	 frc::SmartDashboard::PutData("Arm: Start position", new PositionArm(PositionArm::Position::Retracted));
	 frc::SmartDashboard::PutData("Arm: Pickup", new PositionArm(PositionArm::Position::Pickup));
	 frc::SmartDashboard::PutData("Arm: Switch", new PositionArm(PositionArm::Position::Switch));
	 frc::SmartDashboard::PutData("Arm: Scale Front", new PositionArm(PositionArm::Position::ScaleFront));
	 frc::SmartDashboard::PutData("Arm: Scale Rear", new PositionArm(PositionArm::Position::ScaleRear));
	 frc::SmartDashboard::PutData("Arm: Climb Setup", new PositionArm(PositionArm::Position::ClimbSet));
	 frc::SmartDashboard::PutData("Arm: Nudge Up", new NudgeArm(+1));
	 frc::SmartDashboard::PutData("Arm: Nudge Down", new NudgeArm(-1));
	 frc::SmartDashboard::PutData("**Reset arm home position**", new SetArmHomePosition());

	/* Elevator Controls */
	 frc::SmartDashboard::PutData("Elevator: Nudge Up", new NudgeElevator(+3));
	 frc::SmartDashboard::PutData("Elevator: Nudge Down", new NudgeElevator(-3));
	 frc::SmartDashboard::PutData("Elevator: Brake", new ElevatorBrake(ElevatorBrake::State::BrakeOn));
	 frc::SmartDashboard::PutData("Elevator: Brake Release", new ElevatorBrake(ElevatorBrake::State::BrakeOff));
	 frc::SmartDashboard::PutData("**Reset elevator home position**", new SetElevatorHomePosition());
	 frc::SmartDashboard::PutData("Elevator: Climb", new RobotClimb());
	
	/* Gripper Controls */
	 frc::SmartDashboard::PutData("Gripper: Open", new OpenGripper());
	 frc::SmartDashboard::PutData("Gripper: Close", new CloseGripper());
	 frc::SmartDashboard::PutData("Intake: Run Wheels", new StartIntakeWheels());
	 frc::SmartDashboard::PutData("Intake: Stop Wheels", new StopIntakeWheels());
	 frc::SmartDashboard::PutData("Intake: Raise", new SetGripperIntake(GripperIntake::State::Raised));
	 frc::SmartDashboard::PutData("Intake: Lower", new SetGripperIntake(GripperIntake::State::Lowered));
	

  /* Driver Controller */
	// WhenPressed(new RawButton<OI::Xbox>(m_driverController, Xbox::lt_Bumper), new ShiftGear(ShiftGear::Gear::High));
	// WhenPressed(new RawButton<OI::Xbox>(m_driverController, Xbox::lt_Bumper), new ShiftGear(ShiftGear::Gear::Low));

  /* Manipulator Joystick */
	WhileHeld(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::trigger), new OpenGripper());
	WhenReleased(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::trigger), new CloseGripper());
	WhileHeld(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button2), new NudgeElevator(-3));
	WhileHeld(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button3), new NudgeElevator(+3));
	WhileHeld(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button4), new PositionArm(PositionArm::Position::ClimbSet));
	WhileHeld(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button5), new RobotClimb());
	WhenPressed(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button6), new PositionArm(PositionArm::Position::Pickup));
	WhenPressed(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button7), new PositionArm(PositionArm::Position::Switch));
	WhenPressed(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button8), new PositionArm(PositionArm::Position::Retracted));
	WhileHeld(new ComboControl(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button9), 
	                           new RawAxis<OI::JoystickAxis>(m_manipulatorJoystick, JoystickAxis::Wheel)), new NudgeArm(true));
	WhenPressed(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button10), new PositionArm(PositionArm::Position::ScaleRear));
	WhenPressed(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button11), new PositionArm(PositionArm::Position::ScaleFront));
	// WhileHeld(new RawButton<OI::Joystick>(m_manipulatorJoystick, Joystick::button11), new MoveElevator());
}

std::pair<double, double> OI::GetDriveControls() {
    double speed = m_driverController->GetY(frc::XboxController::JoystickHand::kLeftHand) * -1;
    double rotation = m_driverController->GetX(frc::XboxController::JoystickHand::kRightHand);
    double driveMultiplier = frc::SmartDashboard::GetNumber("Driver: Speed", 1);

    if (driveMultiplier < 0) 
        driveMultiplier = 0;
    else if (driveMultiplier > 1)
        driveMultiplier = 1;

    return std::make_pair(speed * driveMultiplier, rotation * driveMultiplier);
}