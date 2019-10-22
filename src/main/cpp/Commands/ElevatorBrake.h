#ifndef ELEVATORBREAK_H
#define ELEVATORBREAK_H

#include "frc/commands/Subsystem.h"
#include "../Robot.h"

class ElevatorBreak : public frc::Command
{
public:
	enum class State {
		BrakeOn,
		BrakeOff
	};

	ElevatorBreak(State state) : m_state(state) {
		Requires(Robot::elevator.get());
	}

	void Execute() override {
		if(m_state == State::BrakeOn)
			Robot::elevator->ApplyBrake();
		else
			Robot::elevator->ReleaseBrake();
	}

	bool IsFinished() override {
		return true;
	}

private:
	const State m_state;
};

#endif
