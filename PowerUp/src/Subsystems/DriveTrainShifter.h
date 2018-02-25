#ifndef DRIVETRAINSHIFTER_H
#define DRIVETRAINSHIFTER_H
#include "Commands/Subsystem.h"
#include "Utilities/TalonTelemetry.h"
#include "WPILib.h"

class DriveTrainShifter: public frc::Subsystem
{
public:
	enum class Gear
	{
		Low,
		High
	};

	DriveTrainShifter();
	void Periodic() override;

	void Shift(Gear gear);
	Gear GetGear();
	bool IsShiftDone() const;
	void FinishShift();

private:
	void BeginShift(const DoubleSolenoid::Value value);

	std::shared_ptr<frc::DoubleSolenoid> shifter;
	Gear m_currentGear;
	TalonTelemetry m_left;
	TalonTelemetry m_right;
	mutable int m_shiftCountdown;
};

#endif
