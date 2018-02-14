#pragma once

#include <WPILib.h>
//#include "../Commands/RangeReadout.h"
#include "Commands/Subsystem.h"


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



