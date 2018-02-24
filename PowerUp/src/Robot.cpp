// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<DriveTrainShifter> Robot::driveTrainShifter;
std::shared_ptr<FieldPositioningSystem> Robot::fieldPositioningSystem;
std::shared_ptr<Gripper> Robot::gripper;
std::shared_ptr<GripperIntake> Robot::gripperIntake;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<Arm> Robot::arm;
Robot* Robot::robot = nullptr;

Robot::Robot()
{
	robot = this;
}

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());
    driveTrainShifter.reset(new DriveTrainShifter());
    fieldPositioningSystem.reset(new FieldPositioningSystem());
    gripper.reset(new Gripper());
    gripperIntake.reset(new GripperIntake());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
    elevator.reset(new Elevator());
    arm.reset(new Arm());
	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	chooser.AddObject("AutonomousLeft", new AutonomousLeft());
	chooser.AddObject("AutonomousCenter", new AutonomousCenter());
	chooser.AddObject("AutonomousRight", new AutonomousRight());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	frc::SmartDashboard::PutData("Auto Modes", &chooser);

//	auto* const lw = LiveWindow::GetInstance();
//	lw->Add(arm);
//	lw->Add(gripper);
//	lw->Add(RobotMap::gripperSolenoid);
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	const auto& driverJoystick = oi->getDriverJoystick();
	const auto& manipulatorJoystick = oi->getManipulatorJoystick();
	double joystick_magic_shift = 0.3;
	double magic_shift_point = 0.2;
	RobotMap::driveTrainRobotDrive->ArcadeDrive(driverJoystick->GetX(), driverJoystick->GetY(), true);
	if ( ( driverJoystick->GetX() > joystick_magic_shift ) && ( driveTrain->GetSpeed() > magic_shift_point ) )
	{
		driveTrainShifter->ShiftHigh();
	}
	else if ( driveTrain->GetSpeed() < ( magic_shift_point * 0.8 ))
	{
		driveTrainShifter->ShiftLow();
	}
}

START_ROBOT_CLASS(Robot);

