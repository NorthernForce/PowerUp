#ifndef RUNINTAKE_H
#define RUNINTAKE_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class RunIntakeWheels: public frc::TimedCommand {
public:
	RunIntakeWheels() : frc::TimedCommand(duration) {
		Requires(Robot::gripperIntake.get());
	}
	void Initialize() override {
		Robot::gripperIntake->RunIntakeWheels();
	}

private:
	constexpr static double duration { 0.2 };
};

#endif //RUNINTAKE_H
