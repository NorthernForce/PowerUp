//add #ifndef, etc.

#pragma once

#include "Commands/Subsystem.h"
#include <WPILib.h>

class Gimbal : public frc::Subsystem {
private:
	frc::Servo* pan;
	frc::Servo* tilt;

public:
	Gimbal(int panChannel, int tiltChannel);

	void SetPan(int i);
	void SetTilt(int i);
	int GetPan();
	int GetTilt();
};

