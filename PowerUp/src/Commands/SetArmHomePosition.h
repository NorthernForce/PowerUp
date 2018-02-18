#ifndef SETARMHOMEPOSITIONA_H
#define SETARMHOMEPOSITIONA_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class SetArmHomePosition : public frc::Command
{
public:
	SetArmHomePosition() {}

	void Initialize() override
	{
		Robot::arm->SetHomePosition();
	}

	bool IsFinished() override { return true; }
};

#endif
