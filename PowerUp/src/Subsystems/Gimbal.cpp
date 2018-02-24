/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Gimbal.h"

Gimbal::Gimbal(int panChannel, int tiltChannel) : frc::Subsystem("GimbalSubsystem") {
	pan = new frc::PWM(panChannel);
	tilt = new frc::PWM(tiltChannel);
}

void Gimbal::SetPan(int i) {
	pan->SetRaw(i);
}

void Gimbal::SetTilt(int i) {
	tilt->SetRaw(i);
}

int Gimbal::GetPan() {
	return pan->GetRaw();
}

int Gimbal::GetTilt() {
	return tilt->GetRaw();
}
