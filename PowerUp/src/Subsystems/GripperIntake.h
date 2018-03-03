//Not being used currently

#ifndef GRIPPERINTAKE_H
#define GRIPPERINTAKE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class GripperIntake: public frc::Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> talonSRX11;
public:
	GripperIntake();
	void InitDefaultCommand() override;
	void Periodic() override;
	void Enable();
	void Disable();
};

#endif //GRIPPERINTAKE_H
