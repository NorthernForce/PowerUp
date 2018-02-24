/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutonomousTurnToTarget.h"
#include "../VisionThread.h"

AutonomousTurnToTarget::AutonomousTurnToTarget(bool turnToLights, bool blueLights) {
	vtLookForLights = turnToLights;
	vtLookForBlue = blueLights;
}

// Called just before this Command runs the first time
void AutonomousTurnToTarget::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousTurnToTarget::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousTurnToTarget::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutonomousTurnToTarget::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousTurnToTarget::Interrupted() {

}
