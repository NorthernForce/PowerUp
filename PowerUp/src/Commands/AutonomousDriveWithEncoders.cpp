#include "AutonomousDriveWithEncoders.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive) {
	Requires(Robot::driveTrain.get());

//	if (Robot::driveTrainShifter->GetGear() == DriveTrainShifter::Gear::High)
//		convUnits = Robot::driveTrain->nativeUnitsPerMeterHighGear;
//	else
//		convUnits = Robot::driveTrain->nativeUnitsPerMeterLowGear;

	distanceToDrive = round(metersToDrive * convUnits);

	error = 0;
	errorOffset = 0;
	output = 0;
}

// Called just before this Command runs the first time
void AutonomousDriveWithEncoders::Initialize() {
	Robot::driveTrain->SetSafetyEnabled(false);

	Robot::driveTrain->SetBrake();

	distanceToDrive = Robot::driveTrain->GetPositionLeft() + distanceToDrive;

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

void AutonomousDriveWithEncoders::Execute() {
	error = (distanceToDrive - Robot::driveTrain->GetPositionLeft()) / convUnits / 5;
	errorOffset = 0.15 * ((error > 0) ? 1 : -1);

	output = (error + errorOffset) * -1;

	Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, output, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	return std::abs((distanceToDrive - Robot::driveTrain->GetPositionLeft()) / convUnits) < 0.01 && std::abs(RobotMap::ahrs->GetWorldLinearAccelX()) < 0.2;
}

// Called once after isFinished returns true
void AutonomousDriveWithEncoders::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveWithEncoders::Interrupted() {

}
