#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Commands/Subsystem.h"
#include "Utilities/TalonTelemetry.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public frc::Subsystem
{
public:
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetPosition(int);
	bool AtSetpoint();
	void ApplyBrake();
	void ReleaseBrake();
	void SetHomePosition();
	void Nudge(int distance);

private:
	const std::shared_ptr<WPI_TalonSRX> m_masterTalon;
	const std::shared_ptr<WPI_TalonSRX> m_slaveTalon;
	TalonTelemetry m_telemetryMaster;
	TalonTelemetry m_telemetrySlave;
	int m_setpoint;

	constexpr static int timeoutMs = 10;
	constexpr static int noTimeoutMs = 0;
	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.80;
	constexpr static double sensorUnitsPerRev = 12 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 12 counts per revolution
	constexpr static double maxSensorUnitsPer100ms = sensorUnitsPerRev * maxSpeedRPM / 60 / 10;
	constexpr static double feedForwardGain = 1023 / maxSensorUnitsPer100ms;
	constexpr static double pGainPower = 0.1;
	constexpr static double pGainError = 2;
	constexpr static double dGainError = 100;
	constexpr static double pGain = (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.10;
	constexpr static double dGain = 0;//-1 * pGain / dGainError;
	constexpr static double timeToMaxSpeed = 0.5;
	constexpr static int slotIdx = 0;
	constexpr static int pidIdx = 0;
};

#endif
