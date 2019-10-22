//Not being used currently

#ifndef GRIPPERINTAKE_H
#define GRIPPERINTAKE_H
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class GripperIntake: public frc::Subsystem {
public:
	enum class State {
			Raised,
			Lowered
	};
	GripperIntake();
	void RunIntakeWheels();
	void StopIntakeWheels();
	void SetIntake(State state);
	bool IsDown();
	bool IsRunning();
private:
	bool isRunning;
	const std::shared_ptr<frc::Solenoid> m_gripperIntakeSolenoid;
	const std::shared_ptr<WPI_TalonSRX> m_gripperIntakeTalon;
};

#endif //GRIPPERINTAKE_H
