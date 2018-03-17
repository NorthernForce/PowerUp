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
	int initialPosition;
	int distanceToDrive;

	double highSpeed;
	double lowSpeed = 0.25;

	double turnConstant = -0.03;

	int slowThreshold = round(0.6 * Robot::driveTrain->nativeUnitsPerMeterLowGear);
	int stopThreshold = round(0.02 * Robot::driveTrain->nativeUnitsPerMeterLowGear);
//	int slowThreshold = round(0.6 * Robot::driveTrain->nativeUnitsPerMeterHighGear);
//	int stopThreshold = round(0.02 * Robot::driveTrain->nativeUnitsPerMeterHighGear);
};
