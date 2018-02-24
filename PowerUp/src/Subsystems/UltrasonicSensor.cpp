/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "UltrasonicSensor.h"
#include "../RobotMap.h"
#include <WPILib.h>

UltrasonicSensor::UltrasonicSensor(int analogChannel,  int serialChannel, int onChannel) :
	frc::Subsystem("UltrasonicSensor"),
	kMinVoltage(0.5),
	kVoltageRange(5.0 - kMinVoltage),
	kMinDistance(3.0),
	kDistanceRange(60 - kMinDistance),
	m_distanceChannel(analogChannel),
	m_serialMode(serialChannel),
	m_sensorOn(onChannel)
{
	m_serialMode.Set(1);
	m_sensorOn.Set(1);
}

double UltrasonicSensor::GetRangeInFeet() const
{
	return m_distanceChannel.GetVoltage() / (0.0098*12);
}
