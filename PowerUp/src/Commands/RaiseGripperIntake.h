#ifndef RAISEGRIPPERINTAKE_H
#define RAISEGRIPPERINTAKE_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class RaiseGripperIntake: public frc::TimedCommand {
public:
	RaiseGripperIntake() : frc::TimedCommand(duration) {
		Requires(Robot::gripperIntake.get());
	}
	void Initialize() override {
		Robot::gripperIntake->RaiseIntake();
	}

private:
	constexpr static double duration { 1.0 };
};

#endif //RAISEGRIPPERINTAKE_H
