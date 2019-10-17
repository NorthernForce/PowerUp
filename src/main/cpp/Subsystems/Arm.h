#ifndef ARM_H
#define ARM_H
#include "Commands/Subsystem.h"
#include "Utilities/TalonTelemetry.h"
#include "WPILib.h"

class Arm: public frc::Subsystem {
public:
	Arm();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetPosition(int setpoint, unsigned delay);
	bool AtSetpoint();
	void SetHomePosition();
	void NudgeArm(int distance);
	void InitSendable(SendableBuilder& builder) override;
	void ReducePowerForClimb();

private:
	const std::shared_ptr<WPI_TalonSRX> m_talonSRX;
	TalonTelemetry m_telemetry;
	int m_setpoint;
	unsigned m_delay;
	constexpr static int timeoutMs = 10;
	constexpr static int noTimeoutMs = 0;
	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.80;
	constexpr static double sensorUnitsPerRev = 12 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 12 counts per revolution
	constexpr static double maxSensorUnitsPer100ms = sensorUnitsPerRev * maxSpeedRPM * 0.3 / 60 / 10;
	constexpr static double feedForwardGain = 1023 / maxSensorUnitsPer100ms;
	constexpr static double pGainPower = 0.2;
	constexpr static double pGainError = 10;
	constexpr static double pGain = (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.08;
	constexpr static double iLimit = 500;
	constexpr static double dGain = 0;//-1 * pGain / 10;
	constexpr static double timeToMaxSpeed = 2.5;
	constexpr static int slotIdx = 0;
	constexpr static int pidIdx = 0;
};

#endif //ARM_H
