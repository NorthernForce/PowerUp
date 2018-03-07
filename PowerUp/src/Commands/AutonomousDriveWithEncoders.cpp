#include "AutonomousDriveWithEncoders.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive) {
	Requires(Robot::driveTrain.get());

//	initial = (Robot::driveTrain->GetPositionLeft() + Robot::driveTrain->GetPositionRight()) / 2;
	initial = Robot::driveTrain->GetPositionRight();
	distance = metersToDrive;
	speed = speedToDrive;
}

// Called just before this Command runs the first time
void AutonomousDriveWithEncoders::Initialize() {
	Robot::driveTrain->SetBrake();
//	initial = (Robot::driveTrain->GetPositionLeft() + Robot::driveTrain->GetPositionRight()) / 2;
	initial = Robot::driveTrain->GetPositionRight();
	distance = round(distance * Robot::driveTrain->nativeUnitsPerMeterLowGear + initial);

	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveWithEncoders::Execute() {
//	Robot::driveTrain->ArcadeDrive(0, speed, false);
	Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * -0.03, speed, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	if (speed > 0)
		return (Robot::driveTrain->GetPositionRight() >= distance);
	else if (speed < 0)
		return (Robot::driveTrain->GetPositionRight() <= distance);
	else
		return true;
}

// Called once after isFinished returns true
void AutonomousDriveWithEncoders::End() {
	Robot::driveTrain->SetCoast();
	Robot::driveTrain->ArcadeDrive(0, 0, true);
	RobotMap::ahrs->ResetDisplacement();
//	Wait(2);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveWithEncoders::Interrupted() {

}
