#include "AutonomousTurnWithGyro.h"

AutonomousTurnWithGyro::AutonomousTurnWithGyro(int degToTurn) {
	Requires(Robot::driveTrain.get());

	angleToTurn = degToTurn;

	error = 0;
	errorOffset = 0;
	output = 0;
}

void AutonomousTurnWithGyro::Initialize() {
	Robot::driveTrain->SetSafetyEnabled(false);

	Robot::driveTrain->SetBrake();

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

double error, output;

void AutonomousTurnWithGyro::Execute() {
	error = (angleToTurn - RobotMap::ahrs->GetAngle()) / 120;
	errorOffset = 0.45 * ((error > 0) ? 1 : -1);

	output = error + errorOffset;

//	printf("output: %f angle: %f error: %f\n", output, RobotMap::ahrs->GetAngle(), error);

	Robot::driveTrain->ArcadeDrive(output, 0, false);
}

bool AutonomousTurnWithGyro::IsFinished() {
	return RobotMap::ahrs->GetAngle() < angleToTurn + 1 && RobotMap::ahrs->GetAngle() > angleToTurn - 1 && std::abs(RobotMap::ahrs->GetRate()) < 2;
}

void AutonomousTurnWithGyro::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);
}

void AutonomousTurnWithGyro::Interrupted() {

}
