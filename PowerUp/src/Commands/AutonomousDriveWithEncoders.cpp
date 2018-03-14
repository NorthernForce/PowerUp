#include "AutonomousDriveWithEncoders.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive) {
	Requires(Robot::driveTrain.get());

//	initial = (Robot::driveTrain->GetPositionLeft() + Robot::driveTrain->GetPositionRight()) / 2;
	initial = Robot::driveTrain->GetPositionRight();

	distance = metersToDrive;

	if (distance > 0)
		speed = std::abs(speedToDrive);
	if (distance < 0)
		speed = std::abs(speedToDrive) * -1;
	else
		speed = 0;
}

// Called just before this Command runs the first time
void AutonomousDriveWithEncoders::Initialize() {
	Robot::driveTrain->SetBrake();

//	initial = (Robot::driveTrain->GetPositionLeft() + Robot::driveTrain->GetPositionRight()) / 2;
	initial = Robot::driveTrain->GetPositionRight();

	distance = round(distance * Robot::driveTrain->nativeUnitsPerMeterLowGear + initial);

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveWithEncoders::Execute() {
	DriverStation::ReportWarning("distance: " +std::to_string(Robot::driveTrain->GetPositionRight()) +" speed: " +std::to_string(speed));

	Robot::driveTrain->ArcadeDrive(0, speed, false);
//	Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * -0.03, speed, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	return std::abs(Robot::driveTrain->GetPositionRight()) >= std::abs(distance) || speed == 0;
}

// Called once after isFinished returns true
void AutonomousDriveWithEncoders::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);

	// maybe wait to give it time to brake before coasting again
	Wait(50);
	Robot::driveTrain->SetCoast();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveWithEncoders::Interrupted() {

}
