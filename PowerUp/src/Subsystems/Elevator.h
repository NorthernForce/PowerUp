#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public frc::Subsystem
{
private:
	const std::shared_ptr<WPI_TalonSRX> talonSRX7;
	const std::shared_ptr<WPI_TalonSRX> talonSRX8;

public:
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetPosition(int);
	bool AtSetpoint();
	void ApplyBrake();
	void ReleaseBrake();
};

#endif
