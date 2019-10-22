#ifndef SETGRIPPERINTAKE_H
#define SETGRIPPERINTAKE_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"
#include "Subsystems/GripperIntake.h"

class SetGripperIntake: public frc::TimedCommand {
public:
	SetGripperIntake(GripperIntake::State intakeState) : frc::TimedCommand(duration) {
		Requires(Robot::gripperIntake.get());
		m_intakeState = intakeState;
	}
	void Initialize() override {
		Robot::gripperIntake->SetIntake(m_intakeState);
	}

private:
	GripperIntake::State m_intakeState;
	constexpr static double duration { 1.0 };

};

#endif //SEtGRIPPERINTAKE_H
