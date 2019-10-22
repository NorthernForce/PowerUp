//add #ifndef, etc.

#pragma once

#include "frc/commands/Subsystem.h"
#include <frc/WPILib.h>

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

