#include "AutonomousTurnWithGyro.h"

AutonomousTurnWithGyro::AutonomousTurnWithGyro(int degToTurn) {
	Requires(Robot::driveTrain.get());

	angleToTurn = degToTurn;
}

void AutonomousTurnWithGyro::Initialize() {
	Robot::driveTrain->SetBrake();

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

double k_error, i_error, d_error, k_error_prev, p_out, i_out, d_out, output;

void AutonomousTurnWithGyro::Execute() {
	k_error = angleToTurn - RobotMap::ahrs->GetAngle();
	i_error = i_error + k_error;
	d_error = k_error_prev - k_error;

	p_out = kp * k_error;
	i_out = ki * i_error;
	d_out = kd * d_error;

	output = p_out + i_out + d_out;

	k_error_prev = k_error;

	printf("output: %f angle: %f k_out: %f i_out: %f d_out: %f\n", output, RobotMap::ahrs->GetAngle(), p_out, i_out, d_out);

	Robot::driveTrain->ArcadeDrive(output, 0, false);
}

bool AutonomousTurnWithGyro::IsFinished() {
	return false;
}

void AutonomousTurnWithGyro::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);
}

void AutonomousTurnWithGyro::Interrupted() {

}
