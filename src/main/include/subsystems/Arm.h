/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "ctre/Phoenix.h"
#include <frc/commands/Subsystem.h>

class Arm : public frc::Subsystem {
 private:
  std::shared_ptr<WPI_TalonSRX> m_armTalon;
	int m_setPosition;
	unsigned m_delay;
	constexpr static int m_timeoutMs = 10;
	constexpr static int m_noTimeoutMs = 0;
	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.80;
	constexpr static double sensorUnitsPerRev = 12 * 4; 
	constexpr static double maxSensorUnitsPer100ms = sensorUnitsPerRev * maxSpeedRPM * 0.3 / 60 / 10;
	constexpr static double feedForwardGain = 1023 / maxSensorUnitsPer100ms;
	constexpr static double pGainPower = 0.2;
	constexpr static double pGainError = 10;
	constexpr static double pGain = (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.08;
	constexpr static double iLimit = 500;
	constexpr static double dGain = 0;//-1 * pGain / 10;
	constexpr static double timeToMaxSpeed = 2.5;
	constexpr static int m_slotIdx = 0;
	constexpr static int m_PidID = 0;

 public:
  Arm();
	void InitDefaultCommand() override;
	void Periodic() override;
	void SetPosition(int setpoint, unsigned delay);
	bool AtSetpoint();
	void SetHomePosition();
	void NudgeArm(int distance);
	void ReducePowerForClimb();
};
