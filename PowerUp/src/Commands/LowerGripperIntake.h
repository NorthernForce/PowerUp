#ifndef LOWERGRIPPERINTAKE_H
#define LOWERGRIPPERINTAKE_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class LowerGripperIntake: public frc::TimedCommand {
public:
	LowerGripperIntake() : frc::TimedCommand(duration) {
		Requires(Robot::gripperIntake.get());
	}
	void Initialize() override {
		Robot::gripperIntake->LowerIntake();
	}

private:
	constexpr static double duration { 1.0 };
};

#endif //LOWERGRIPPERINTAKE_H
