#include "AutonomousTurnWithGyro.h"

AutonomousTurnWithGyro::AutonomousTurnWithGyro(int degToTurn, double speedToDrive) {
	Requires(Robot::driveTrain.get());

	angleToTurn = degToTurn;

	if (degToTurn > 0) {
		highSpeed = std::abs(speedToDrive) * -1;
		lowSpeed = std::abs(lowSpeed) * -1;
	}
	else if (degToTurn < 0) {
		highSpeed = std::abs(speedToDrive);
		lowSpeed = std::abs(lowSpeed);
	}
	else {
		highSpeed = 0;
		lowSpeed = 0;
	}
}

// Called just before this Command runs the first time
void AutonomousTurnWithGyro::Initialize() {
	Robot::driveTrain->SetBrake();

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousTurnWithGyro::Execute() {
	if (std::abs(RobotMap::ahrs->GetAngle()) >= std::abs(angleToTurn) - slowThreshold)
		Robot::driveTrain->ArcadeDrive(highSpeed, 0, false);
	else
		Robot::driveTrain->ArcadeDrive(lowSpeed, 0, false);

//	DriverStation::ReportWarning("angle: " +std::to_string(RobotMap::ahrs->GetAngle()) +" speed: " +std::to_string(speed));
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousTurnWithGyro::IsFinished() {
	return std::abs(RobotMap::ahrs->GetAngle()) >= std::abs(angleToTurn) - stopThreshold || highSpeed == 0;
}

// Called once after isFinished returns true
void AutonomousTurnWithGyro::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);

	// maybe wait to give it time to brake before coasting again
//	Wait(0.05);
	Robot::driveTrain->SetCoast();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousTurnWithGyro::Interrupted() {

}
