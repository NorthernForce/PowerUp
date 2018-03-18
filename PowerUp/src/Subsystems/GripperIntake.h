//Not being used currently

#ifndef GRIPPERINTAKE_H
#define GRIPPERINTAKE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class GripperIntake: public frc::Subsystem {
public:
	GripperIntake();
	void RunIntakeWheels();
	void StopIntakeWheels();
	void RaiseIntake();
	void LowerIntake();
	bool IsDown();
	bool IsRunning();
private:
	bool isRunning;
	const std::shared_ptr<WPI_TalonSRX> m_gripperIntakeTalon;
	const std::shared_ptr<frc::Solenoid> m_gripperIntakeSolenoid;

};

#endif //GRIPPERINTAKE_H
