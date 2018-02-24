/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Commands/Subsystem.h"
#include <WPILib.h>

class UltrasonicSensor: public frc::Subsystem
{
	public:
		UltrasonicSensor(int analogChannel, int serialChannel, int onChannel);
////       analogChannel = 1, serialChannel = 5, onChannel = 1

		double GetRangeInFeet() const;

	private:

		const float kMinVoltage;
		const float kVoltageRange;
		const float kMinDistance;
		const float kDistanceRange;
		mutable AnalogInput m_distanceChannel;

		DigitalOutput m_serialMode;

		DigitalOutput m_sensorOn;
};
