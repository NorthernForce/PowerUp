/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "../Robot.h"

class AutonomousTurnWithGyro : public frc::Command {
public:
	AutonomousTurnWithGyro(int degToTurn);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	int angleToTurn;

	double kp = 0.025;
	double ki = 0;
	double kd = 0;
};
