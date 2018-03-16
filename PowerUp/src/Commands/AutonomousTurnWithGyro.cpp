/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/AutonomousTurnWithGyro.h>

AutonomousTurnWithGyro::AutonomousTurnWithGyro(double angleToTurn, double speedToMove) {
	Requires(Robot::driveTrain.get());

//	angle = angleToTurn / 180 * 3.141592653589;
	angle = angleToTurn;

	if (angle > 0)
		speed = std::abs(speedToMove);
	else if (angle < 0)
		speed = std::abs(speedToMove) * -1;
	else
		speed = 0;
}

// Called just before this Command runs the first time
void AutonomousTurnWithGyro::Initialize() {
	Robot::driveTrain->SetBrake();

	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousTurnWithGyro::Execute() {
	double error = std::abs((angle - RobotMap::ahrs->GetAngle()) / angle);
	DriverStation::ReportWarning("angle: " +std::to_string(RobotMap::ahrs->GetAngle()) +" speed: " +std::to_string(speed*error));
//	speed = error * pgain;
	Robot::driveTrain->ArcadeDrive(speed*error+speed*0.6, 0, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousTurnWithGyro::IsFinished() {
	return (std::abs(angle - RobotMap::ahrs->GetAngle()) < 2) || speed ==0;
}

// Called once after isFinished returns true
void AutonomousTurnWithGyro::End() {
	RobotMap::ahrs->Reset();
	RobotMap::ahrs->ResetDisplacement();

	Robot::driveTrain->ArcadeDrive(0, 0, false);

	// maybe wait to give it time to brake before coasting again
//	Wait(50);
	Robot::driveTrain->SetCoast();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousTurnWithGyro::Interrupted() {

}
