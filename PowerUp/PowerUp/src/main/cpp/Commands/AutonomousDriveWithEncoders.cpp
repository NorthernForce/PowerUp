#include "AutonomousDriveWithEncoders.h"
#include "SmartDashboard/SmartDashboard.h"

AutonomousDriveWithEncoders::AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive) {
	Requires(Robot::driveTrain.get());

//	if (Robot::driveTrainShifter->GetGear() == DriveTrainShifter::Gear::High)
#ifdef PRACTICE_BOT
		convUnits = Robot::driveTrain->nativeUnitsPerMeterHighGear;
#else
		convUnits = 3700;
#endif
//	else
//		convUnits = Robot::driveTrain->nativeUnitsPerMeterLowGear;

//	convUnits = 6000;

	initialPos = 0;

	failCheckLeftPos = 0;
	failCheckRightPos = 0;

	failCounter = 0;

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

	Robot::driveTrain->ResetPositionLeft();
	Robot::driveTrain->ResetPositionRight();

//	failCheckLeftPos = Robot::driveTrain->GetPositionLeft();
//	failCheckRightPos = Robot::driveTrain->GetPositionRight();

//	int initialLeftPos = Robot::driveTrain->GetPositionLeft()*-1;
//	int initialRightPos = Robot::driveTrain->GetPositionRight()*-1;

//	if (std::abs(initialLeftPos) > std::abs(initialRightPos))
//		initialPos = initialLeftPos;
//	else
//		initialPos = initialRightPos;

//	initialPos = 0;

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveWithEncoders::Execute() {
	int leftPos = Robot::driveTrain->GetPositionLeft()*-1;
	int rightPos = Robot::driveTrain->GetPositionRight()*-1;

	if (failCounter >= 20) {
		if (std::abs(failCheckLeftPos - leftPos) <= 100)
			RobotMap::leftEncoderBroke = true;
		else
			RobotMap::leftEncoderBroke = false;

		if (std::abs(failCheckRightPos - rightPos) <= 100)
			RobotMap::rightEncoderBroke = true;
		else
			RobotMap::rightEncoderBroke = false;

		failCounter = 0;
	}
	if (failCounter == 0) {
		failCheckLeftPos = leftPos;
		failCheckRightPos = rightPos;
	}

	int pos = 0;
	if (std::abs(leftPos) > std::abs(rightPos))
		pos = leftPos;
	else
		pos = rightPos;

	if (std::abs(pos - initialPos) >= (std::abs(distanceToDrive) - slowThreshold))
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, lowSpeed, false);
	else
		Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * turnConstant, highSpeed, false);

	failCounter++;
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveWithEncoders::IsFinished() {
	bool leftResult = std::abs(Robot::driveTrain->GetPositionLeft()*-1 - initialPos) >= std::abs(distanceToDrive) - stopThreshold || highSpeed == 0;
	bool rightResult = std::abs(Robot::driveTrain->GetPositionRight()*-1 - initialPos) >= std::abs(distanceToDrive) - stopThreshold || highSpeed == 0;

	return leftResult || rightResult;
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
