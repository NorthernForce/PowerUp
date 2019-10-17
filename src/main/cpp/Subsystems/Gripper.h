#ifndef GRIPPER_H
#define GRIPPER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Gripper: public frc::Subsystem {

public:
	Gripper();
	void SetOpen();
	void SetClosed();
	bool IsClosed() const {
		return m_gripperState == State::Closed;
	}

private:
	enum class State {
		Open,
		Closed
	};
	State m_gripperState;
	const std::shared_ptr<frc::Solenoid> m_gripperSolenoid;
};

#endif //GRIPPER_H
