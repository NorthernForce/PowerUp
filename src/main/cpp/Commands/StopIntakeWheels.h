#ifndef STOPINTAKE_H
#define STOPINTAKE_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class StopIntakeWheels: public frc::TimedCommand {
public:
	StopIntakeWheels() : frc::TimedCommand(duration) {
		Requires(Robot::gripperIntake.get());
	}
	void Initialize() override {
		Robot::gripperIntake->StopIntakeWheels();
	}

private:
	constexpr static double duration { 0.2 };
};

#endif //STOPINTAKE_H
