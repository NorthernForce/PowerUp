#include "Gimbal.h"
#include "../RobotMap.h"
#include <frc/WPILib.h>

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
