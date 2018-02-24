/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Gimbal : public frc::Subsystem {
private:
	frc::PWM* pan;
	frc::PWM* tilt;

public:
	Gimbal(int panChannel, int tiltChannel);

	void SetPan(int i);
	void SetTilt(int i);
	int GetPan();
	int GetTilt();
};

