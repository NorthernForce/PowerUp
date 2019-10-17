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

void DriveWithJoystick::Initialize() {
	DriverStation::ReportError("WithJoystick::Initialize");
	Robot::driveTrain->SetSafetyEnabled(true);
}

void DriveWithJoystick::Execute() {
	const auto& driverController = Robot::oi->getDriverController();
	const auto& driveTrainShifter = Robot::driveTrainShifter;
	double XVal, YVal;
	double joystick_magic_shift = 0.3;
	int magic_shift_point = 100; //denoted by encoder units seen in the last 100ms by default, 1024 units per encoder revolution
	//TODO: fix inverted stuff
	/*if (driverController->GetBumperPressed(frc::XboxController::JoystickHand::kLeftHand)) {
		isDriveInverted = !isDriveInverted;
	}*/

	YVal = (isDriveInverted ? -1 : 1 ) * driverController->GetX(frc::XboxController::JoystickHand::kRightHand);
	XVal = driverController->GetY(frc::XboxController::JoystickHand::kLeftHand);
	auto& driveTrain = Robot::driveTrain;
	driveTrain->ArcadeDrive(YVal, XVal, true);
//	broken autoshifting code
//	if ( ( std::abs(XVal) > joystick_magic_shift ) && ( std::abs(driveTrain->GetSpeed()) > magic_shift_point ) )
//	{
//		if(driveTrainShifter->GetGear() == DriveTrainShifter::Gear::Low)
//		{
//			DriverStation::ReportError("Auto shift from low to high");
//			frc::Scheduler::GetInstance()->AddCommand(new ShiftGearbox(ShiftGearbox::Gear::High));
//		}
//	}
//	else if ( ( std::abs(XVal) < joystick_magic_shift * 0.8 ) || ( std::abs(driveTrain->GetSpeed()) < ( magic_shift_point * 0.8 ) ) )
//	{
//		if(driveTrainShifter->GetGear() == DriveTrainShifter::Gear::High)
//		{
//			DriverStation::ReportError("Auto shift from high to low");
////			if ( std::abs(YVal) < (joystick_magic_shift * 0.8 ) )
////				DriverStation::ReportError("less than joystick hysteresis");
//			frc::Scheduler::GetInstance()->AddCommand(new ShiftGearbox(ShiftGearbox::Gear::Low));
//		}
//	}
}

bool DriveWithJoystick::IsFinished() {
    return false;
}

void DriveWithJoystick::End() {

}

void DriveWithJoystick::Interrupted() {

}
