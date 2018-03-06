/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/AutonomousTurnWithGyro.h>

AutonomousTurnWithGyro::AutonomousTurnWithGyro(double angleToTurn, double speedToMove) {
	angle = angleToTurn / 180 * 3.1415925639;

	if (angle > 0)
		speed = abs(speed);
	else if (angle < 0)
		speed = abs(speed)*-1;
	else if (angle == 0)
		speed = 0;
}

// Called just before this Command runs the first time
void AutonomousTurnWithGyro::Initialize() {
	Robot::driveTrain->SetBrake();
	RobotMap::ahrs->ResetDisplacement();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousTurnWithGyro::Execute() {
	Robot::driveTrain->ArcadeDrive(speed, 0, false);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousTurnWithGyro::IsFinished() {
	if (speed > 0) {
		if (angle >= RobotMap::ahrs->GetAngle())
			return true;
		else
			return false;
	}
	else if (speed < 0) {
		if (angle <= RobotMap::ahrs->GetAngle())
			return true;
		else
			return false;
	}
	else
		return true;
}

// Called once after isFinished returns true
void AutonomousTurnWithGyro::End() {
	Robot::driveTrain->SetCoast();
	RobotMap::ahrs->ResetDisplacement();
	Robot::driveTrain->ArcadeDrive(0, 0, false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousTurnWithGyro::Interrupted() {

}
