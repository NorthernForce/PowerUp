#ifndef ARM_H
#define ARM_H
#include "Commands/Subsystem.h"
#include "Utilities/ProfileGenerator.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Arm: public frc::Subsystem
{
public:
	Arm();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetPosition(int);
	bool AtSetpoint();
	void ApplyBrake();
	void ReleaseBrake();

private:
	std::shared_ptr<WPI_TalonSRX> talonSRX;

	constexpr static int timeoutMs = 10;
	constexpr static int noTimeoutMs = 0;
	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.80;
	constexpr static double maxSpeedRevPer100ms = maxSpeedRPM / 60 / 10;
	constexpr static double encoderPulsesPerRev = 12;
	constexpr static double encoderPulsesPer100ms = maxSpeedRevPer100ms * encoderPulsesPerRev;
	constexpr static double feedForwardGain = 1023 / encoderPulsesPer100ms;
	constexpr static double pGainPower = 0.1;
	constexpr static double pGainError = 1200; // Made up
	constexpr static double pGain = (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.001;
	constexpr static double dGain = pGain / 10;
	constexpr static double timeToMaxSpeed = 4.0;
	constexpr static double maxJerk = encoderPulsesPer100ms * 10 / std::pow(timeToMaxSpeed / 2, 2); // Encoder pulses / s^3

	ProfileGenerator m_currentProfile;
	bool PushPoints(WPI_TalonSRX& talon, ProfileGenerator& generator, const double scale, const uint32_t profileSlotSelect0, const uint32_t profileSlotSelect1, const bool zeroPos);
};

#endif
