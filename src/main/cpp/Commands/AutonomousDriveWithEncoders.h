// #pragma once

// #include "frc/commands/Subsystem.h"
// #include "../RobotMap.h"
// #include "../Robot.h"

// class AutonomousDriveWithEncoders : public frc::Command {
// public:
// 	AutonomousDriveWithEncoders(double metersToDrive, double speedToDrive);
// 	void Initialize() override;
// 	void Execute() override;
// 	bool IsFinished() override;
// 	void End() override;
// 	void Interrupted() override;

// private:
// 	int initialPosition;
// 	int distanceToDrive;

// 	double highSpeed;
// 	double lowSpeed = 0.25;

// 	double turnConstant = -0.03;

// 	double convUnits;

// 	int slowThreshold = 0.95;
// 	int stopThreshold = 0.00;
// };
