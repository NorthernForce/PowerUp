#include "DriveWithJoystick.h"
#include "Robot.h"
#include "OI.h"

DriveWithJoystick::DriveWithJoystick(): frc::Command() {
	driveDirection = 1;
	driveStick = 0;
	isDriveInverted = false;
	isComboStep1Complete = false;
	isComboStep2Complete = false;
	isComboStep3Complete = false;
	isComboStep4Complete = false;
    Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize()
{
	DriverStation::ReportError("DriveWithJoystick init called");
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute()
{
	const auto& driverController = Robot::oi->getDriverController();
	const auto& manipulatorJoystick = Robot::oi->getManipulatorJoystick();
	static double XVal, YVal;
	double joystick_magic_shift = 0.3;
	double magic_shift_point = 0.2;
	//RobotMap::driveTrainRobotDrive->ArcadeDrive(driverJoystick->GetX(), driverJoystick->GetY(), true);
	if (driverController->GetBumperPressed(frc::XboxController::JoystickHand::kRightHand)) {
		isDriveInverted = !isDriveInverted;
	}
	XVal = ( isDriveInverted ? -1 : 1 ) * driverController->GetX(frc::XboxController::JoystickHand::kRightHand);
	YVal = driverController->GetY(frc::XboxController::JoystickHand::kLeftHand);
	RobotMap::driveTrainRobotDrive->ArcadeDrive(YVal, XVal, true);

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

/*if (driverController->GetPOV() == 180) {
	isComboStep1Complete = true;
}
if (isComboStep1Complete) {
	if (driverController->GetPOV() == 0) {
		isComboStep2Complete = true;
	}
}
if (isComboStep2Complete) {
	if (driverController->GetPOV() == 270) {
		isComboStep3Complete = true;
	}
}
if (isComboStep3Complete) {
	if (driverController->GetPOV() == 90) {
		isComboStep4Complete = true;
	}
}*
if (isComboStep4Complete) {
	if (driveStick == 0) {
		driveStick = 1;
	} else if (driveStick == 1) {
		driveStick = 0;
	}
	isComboStep1Complete = false;
	isComboStep2Complete = false;
	isComboStep3Complete = false;
	isComboStep4Complete = false;
} else {
	if (driveStick == 1) {
		driveStick = 0;
	} else if (driveStick == 0) {
		driveStick = 1;
	}
}
if (driveStick == 0) {*/
	/*if ((driverController->GetY(frc::XboxController::JoystickHand::kRightHand) > joystick_magic_shift) && (driveTrain->GetSpeed() > magic_shift_point)) {
		driveTrainShifter->ShiftHigh();
	} else if (driveTrain->GetSpeed() < ( magic_shift_point * 0.8 )) {
		driveTrainShifter->ShiftLow();
	}
} else if (driveStick == 1) {
	RobotMap::driveTrainRobotDrive->ArcadeDrive(driverController->GetX(frc::XboxController::JoystickHand::kLeftHand), driveDirection * driverController->GetY(frc::XboxController::JoystickHand::kRightHand), true);
	if ((driverController->GetY(frc::XboxController::JoystickHand::kRightHand) > joystick_magic_shift) && (driveTrain->GetSpeed() > magic_shift_point)) {
		driveTrainShifter->ShiftHigh();
	} else if (driveTrain->GetSpeed() < ( magic_shift_point * 0.8 )) {
		driveTrainShifter->ShiftLow();
	}
}*/
