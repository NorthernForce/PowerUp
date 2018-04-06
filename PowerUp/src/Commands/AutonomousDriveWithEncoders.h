#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "../Robot.h"

class AutonomousDriveWithEncoders : public frc::Command {
public:
	AutonomousDriveWithEncoders(double metersToDrive);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	int distanceToDrive;

#ifdef PRACTICE_BOT
	double convUnits = 3600;
#else
	double convUnits = 7000;
#endif

	double turnConstant = -0.03;

	double error, errorOffset, output;
};
