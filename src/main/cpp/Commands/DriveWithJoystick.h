#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class DriveWithJoystick: public frc::Command {
public:
	DriveWithJoystick();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	int driveDirection;
	int driveStick;
	bool isDriveInverted;
};

#endif
