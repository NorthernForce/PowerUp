/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Gimbal.h"
#include "../RobotMap.h"
#include <WPILib.h>

Gimbal::Gimbal(int panChannel, int tiltChannel) : frc::Subsystem("GimbalSubsystem") {
	pan = new frc::Servo(panChannel);
	tilt = new frc::Servo(tiltChannel);
}

void Gimbal::SetPan(int i) {
	pan->SetAngle(i);
}

void Gimbal::SetTilt(int i) {
	tilt->SetAngle(i);
}

int Gimbal::GetPan() {
	return pan->GetAngle();
}

int Gimbal::GetTilt() {
	return tilt->GetAngle();
}
