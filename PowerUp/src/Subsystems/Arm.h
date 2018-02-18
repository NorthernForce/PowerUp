#ifndef ARM_H
#define ARM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Arm: public frc::Subsystem
{
private:
	std::shared_ptr<WPI_TalonSRX> talonSRX;

	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.75;
	constexpr static double maxSpeedRevPer100ms = maxSpeedRPM / 60 / 10;
	constexpr static double encoderPulsesPerRev = 12;
	constexpr static double encoderPulsesPer100ms = maxSpeedRevPer100ms * encoderPulsesPerRev;
	constexpr static double feedForwardGain = 1023 / encoderPulsesPer100ms;
	constexpr static double pGainPower = 0.1;
	constexpr static double pGainError = 1200; // Made up
	constexpr static double pGain = (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.001;
	constexpr static double dGain = pGain / 10;

public:
	Arm();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetPosition(int);
	bool AtSetpoint();
	void ApplyBrake();
	void ReleaseBrake();
};

#endif
