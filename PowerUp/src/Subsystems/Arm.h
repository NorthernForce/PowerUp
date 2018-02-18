#ifndef ARM_H
#define ARM_H
#include "Commands/Subsystem.h"
#include "Utilities/TalonTelemetry.h"
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
	void SetHomePosition();

private:
	const std::shared_ptr<WPI_TalonSRX> m_talonSRX;
	TalonTelemetry m_telemetry;
	int m_setpoint;

	constexpr static int timeoutMs = 10;
	constexpr static int noTimeoutMs = 0;
	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.80;
	constexpr static double sensorUnitsPerRev = 12 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 12 counts per revolution
	constexpr static double maxSensorUnitsPer100ms = sensorUnitsPerRev * maxSpeedRPM / 60 / 10;
	constexpr static double feedForwardGain = 1023 / maxSensorUnitsPer100ms;
	constexpr static double pGainPower = 0.1;
	constexpr static double pGainError = 1200; // Made up
	constexpr static double pGain = (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.001;
	constexpr static double dGain = pGain / 10;
	constexpr static double timeToMaxSpeed = 3.0;
	constexpr static int slotIdx = 0;
	constexpr static int pidIdx = 0;
};

#endif
