#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "../Robot.h"

class AutonomousDriveWithEncoders : public frc::Command {
public:
	AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	int initial;
	int distance;
	double speed;
};

