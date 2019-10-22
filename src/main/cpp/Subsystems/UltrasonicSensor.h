//Not currently being used
//Add $ifndef, etc.
#pragma once

#include "frc/commands/Subsystem.h"
#include <frc/WPILib.h>

class UltrasonicSensor: public frc::Subsystem {
	public:
		UltrasonicSensor(int analogChannel, int serialChannel, int onChannel);
		//analogChannel = 1, serialChannel = 5, onChannel = 1
		double GetRangeInFeet() const;

	private:
		const float kMinVoltage;
		const float kVoltageRange;
		const float kMinDistance;
		const float kDistanceRange;
		mutable frc::AnalogInput m_distanceChannel;
		frc::DigitalOutput m_serialMode;
		frc::DigitalOutput m_sensorOn;
};
