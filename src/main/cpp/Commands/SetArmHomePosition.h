#ifndef SETARMHOMEPOSITION_H
#define SETARMHOMEPOSITION_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class SetArmHomePosition : public frc::Command {
public:
	SetArmHomePosition() {
		SetRunWhenDisabled(true);
	}

	void Initialize() override {
		Robot::arm->SetHomePosition();
	}

	bool IsFinished() override {
		return true;
	}
};

#endif
