// #include "AutonomousDriveForward.h"

// AutonomousDriveForward::AutonomousDriveForward(int timeToTravel, double speedToMove) {
// 	Requires(Robot::driveTrain.get());

// 	timer = 0;
// 	// Execute() runs every 20 ms, so we divide by 20
// 	time = timeToTravel/20;
// 	speed = speedToMove;
// }

// void AutonomousDriveForward::Initialize() {
// 	Robot::driveTrain->SetSafetyEnabled(false);

// 	Robot::driveTrain->SetBrake();

// 	RobotMap::ahrs->Reset();
// 	RobotMap::ahrs->ResetDisplacement();
// }

// void AutonomousDriveForward::Execute() {
// 	Robot::driveTrain->ArcadeDrive(RobotMap::ahrs->GetAngle() * -0.03, speed, true);
// 	timer++;
// }

// bool AutonomousDriveForward::IsFinished() {
// 	return (timer >= time);
// }

// void AutonomousDriveForward::End() {
// 	Robot::driveTrain->SetSafetyEnabled(false);
// 	Robot::driveTrain->ArcadeDrive(0, 0, true);

// 	RobotMap::ahrs->Reset();
// 	RobotMap::ahrs->ResetDisplacement();

// }

// void AutonomousDriveForward::Interrupted() {
// 	Robot::driveTrain->ArcadeDrive(0, 0, true);
// }
