#include "AutonomousDriveWithEncoders.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive) {
	Requires(Robot::driveTrain.get());

//	initial = (Robot::driveTrain->GetPositionLeft() + Robot::driveTrain->GetPositionRight()) / 2;
	initialPosition = Robot::driveTrain->GetPositionRight();
//	distanceToDrive = round(metersToDrive * Robot::driveTrain->nativeUnitsPerMeterHighGear);
	distanceToDrive = round(metersToDrive * Robot::driveTrain->nativeUnitsPerMeterLowGear);

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

//	initial = (Robot::driveTrain->GetPositionLeft() + Robot::driveTrain->GetPositionRight()) / 2;
	initialPosition = Robot::driveTrain->GetPositionRight();

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveWithEncoders::Execute() {
	if (std::abs(Robot::driveTrain->GetPositionRight() - initialPosition) >= std::abs(distanceToDrive) - slowThreshold)
//		Robot::driveTrain->ArcadeDrive(0, lowSpeed, false);
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, lowSpeed, false);
	else
//		Robot::driveTrain->ArcadeDrive(0, highSpeed, false);
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, highSpeed, false);

//	printf("distance from target: %f currentPos: %f initialPos: %f speed: %f\n", distanceToDrive - std::abs((Robot::driveTrain->GetPositionRight() / unitConv - initialPosition)), Robot::driveTrain->GetPositionLeft() / unitConv, initialPosition, speed);
//	Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * -0.03, speed, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	return std::abs(Robot::driveTrain->GetPositionRight() - initialPosition) >= std::abs(distanceToDrive) - stopThreshold || highSpeed == 0;
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
