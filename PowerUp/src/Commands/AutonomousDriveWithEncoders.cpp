#include "AutonomousDriveWithEncoders.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive) {
	Requires(Robot::driveTrain.get());

//	if (Robot::driveTrainShifter->GetGear() == DriveTrainShifter::Gear::High)
		convUnits = Robot::driveTrain->nativeUnitsPerMeterHighGear;
//	else
//		convUnits = Robot::driveTrain->nativeUnitsPerMeterLowGear;

//	convUnits = 6000;

	initialPosition = Robot::driveTrain->GetPositionRight()*-1;
	distanceToDrive = round(metersToDrive * convUnits);

	slowThreshold = std::abs(metersToDrive) * 0.5;
	if (slowThreshold > 1)
		slowThreshold = 1;

	slowThreshold = round(slowThreshold * convUnits);
	stopThreshold = round(stopThreshold * convUnits);

	if (metersToDrive > 0) {
		highSpeed = std::abs(speedToDrive) * -1;
		lowSpeed = std::abs(lowSpeed) * -1;
	}
	else if (metersToDrive < 0) {
		highSpeed = std::abs(speedToDrive);
		lowSpeed = std::abs(lowSpeed);
	}
	else {
		highSpeed = 0;
		lowSpeed = 0;
	}
}

// Called just before this Command runs the first time
void AutonomousDriveWithEncoders::Initialize() {
	Robot::driveTrain->SetBrake();

	initialPosition = Robot::driveTrain->GetPositionRight()*-1;

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveWithEncoders::Execute() {
	if (std::abs(Robot::driveTrain->GetPositionRight()*-1 - initialPosition) >= std::abs(distanceToDrive) - slowThreshold)
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, lowSpeed, false);
	else
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, highSpeed, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	return std::abs(Robot::driveTrain->GetPositionRight()*-1 - initialPosition) >= std::abs(distanceToDrive) - stopThreshold || highSpeed == 0;
}

// Called once after isFinished returns true
void AutonomousDriveWithEncoders::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);

	// maybe wait to give it time to brake before coasting again
//	Wait(0.05);
//	Robot::driveTrain->SetCoast();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveWithEncoders::Interrupted() {

}
