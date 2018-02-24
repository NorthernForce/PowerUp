#ifndef DRIVETRAINSHIFTER_H
#define DRIVETRAINSHIFTER_H
#include "Commands/Subsystem.h"
#include "Utilities/TalonTelemetry.h"
#include "WPILib.h"

class DriveTrainShifter: public frc::Subsystem
{
public:
	DriveTrainShifter();
	void ShiftHigh();
	void ShiftLow();
	bool IsShiftDone() const;
	void FinishShift();

private:
	std::shared_ptr<frc::DoubleSolenoid> shifter;
	TalonTelemetry m_left;
	TalonTelemetry m_right;
	mutable int m_count;
};

#endif
