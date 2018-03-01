#include "DriveWithJoystick.h"
#include "ShiftGearbox.h"
#include "Robot.h"
#include "OI.h"

DriveWithJoystick::DriveWithJoystick(): frc::Command() {
	driveDirection = 1;
	driveStick = 0;
	isDriveInverted = false;
    Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize()
{
	DriverStation::ReportError("WithJoystick::Initialize");
	Robot::driveTrain->SetSafetyEnabled(true);
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute()
{
	const auto& driverController = Robot::oi->getDriverController();
	const auto& driveTrainShifter = Robot::driveTrainShifter;
	double XVal, YVal;
	double joystick_magic_shift = 0.3;
	int magic_shift_point = 100; //denoted by encoder units seen in the last 100ms by default, 1024 units per encoder revolution
	if (driverController->GetBumperPressed(frc::XboxController::JoystickHand::kRightHand))
	{
		isDriveInverted = !isDriveInverted;
	}

	YVal = ( isDriveInverted ? 1 : 1 ) * driverController->GetX(frc::XboxController::JoystickHand::kRightHand);
	XVal = driverController->GetY(frc::XboxController::JoystickHand::kLeftHand);
	auto& driveTrain = Robot::driveTrain;
	driveTrain->ArcadeDrive(YVal, XVal, true);

	if ( ( std::abs(XVal) > joystick_magic_shift ) && ( std::abs(driveTrain->GetSpeed()) > magic_shift_point ) )
	{
		if(driveTrainShifter->GetGear() == DriveTrainShifter::Gear::Low)
		{
			DriverStation::ReportError("Auto shift from low to high");
			frc::Scheduler::GetInstance()->AddCommand(new ShiftGearbox(ShiftGearbox::Gear::High));
		}
	}
	else if ( ( std::abs(XVal) < joystick_magic_shift * 0.8 ) || ( std::abs(driveTrain->GetSpeed()) < ( magic_shift_point * 0.8 ) ) )
	{
		if(driveTrainShifter->GetGear() == DriveTrainShifter::Gear::High)
		{
			DriverStation::ReportError("Auto shift from high to low");
//			if ( std::abs(YVal) < (joystick_magic_shift * 0.8 ) )
//				DriverStation::ReportError("less than joystick hysteresis");
			frc::Scheduler::GetInstance()->AddCommand(new ShiftGearbox(ShiftGearbox::Gear::Low));
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {

}
