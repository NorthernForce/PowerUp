// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef GRIPPER_H
#define GRIPPER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
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

#endif
