#include "AutonomousDriveWithEncoders.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive) {
	Requires(Robot::driveTrain.get());

	if (Robot::driveTrainShifter->GetGear() == DriveTrainShifter::Gear::High)
		convUnits = Robot::driveTrain->nativeUnitsPerMeterHighGear;
	else
		convUnits = Robot::driveTrain->nativeUnitsPerMeterLowGear;

	slowThreshold = round(slowThreshold * convUnits);
	stopThreshold = round(stopThreshold * convUnits);

	initialPosition = GetPosition();
	distanceToDrive = round(metersToDrive * convUnits);

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

	initialPosition = GetPosition();

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveWithEncoders::Execute() {
	if (std::abs(Robot::driveTrain->GetPosition() - initialPosition) >= std::abs(distanceToDrive) - slowThreshold)
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, lowSpeed, false);
	else
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, highSpeed, false);

//	printf("distance from target: %f currentPos: %f initialPos: %f \n", distanceToDrive - std::abs((Robot::driveTrain->GetPosition() / convUnits - initialPosition)), Robot::driveTrain->GetPosition() / convUnits, initialPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	return std::abs(GetPosition() - initialPosition) >= std::abs(distanceToDrive) - stopThreshold || highSpeed == 0;
}

// Called once after isFinished returns true
void AutonomousDriveWithEncoders::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);

	// maybe wait to give it time to brake before coasting again
//	Wait(0.05);
	Robot::driveTrain->SetCoast();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveWithEncoders::Interrupted() {

}

int AutonomousDriveWithEncoders::GetPosition() {
	if (getRightEncoder)
		return Robot::driveTrain->GetPositionRight();
	else
		return Robot::driveTrain->GetPositionLeft();
}
