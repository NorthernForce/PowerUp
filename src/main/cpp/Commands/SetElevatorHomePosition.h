#ifndef SETELEVATORHOMEPOSITION_H
#define SETELEVATORHOMEPOSITION_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class SetElevatorHomePosition : public frc::Command {
public:
	SetElevatorHomePosition() {
		SetRunWhenDisabled(true);
	}

	void Initialize() override {
		Robot::elevator->SetHomePosition();
	}

	bool IsFinished() override {
		return true;
	}
};

#endif //SETELEVATORHOMEPOSITION_H
