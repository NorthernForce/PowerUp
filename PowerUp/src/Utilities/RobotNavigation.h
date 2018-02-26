#ifndef ROBOTNAVIGATION_H
#define ROBOTNAVIGATION_H

#include <cstdint>
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "FieldOrientation.h"
#include "ProfileGenerator.h"
#include <functional>
#include <cmath>

class RobotNavigation
{
public:
	enum class Position
	{
		StartingPos,
		ScoreOnScale,
		ScoreOnSwitch,
		PickupCubeAtSwitch,
	};

	struct RobotTrajectory
	{
		Profile m_left;
		Profile m_right;
	};

	RobotNavigation(const FieldOrientation& orientation);
	RobotNavigation(const RobotNavigation&) = default;

	RobotTrajectory CreatePath(const Position from, const Position to);
private:
	RobotTrajectory CreatePathFromStartToSwitch();

	static RobotTrajectory CreateProfile(const double distance, const double startVelocity, const double finalVelocity, const double angleDegrees);

	constexpr static double wheelTrack = 0.64;

	// Max velocity is a function of the CIM, wheel radius and the gear box
	// Free speed 5,330 RPM, low gear 15:1, 4" diameter wheel
	constexpr static double maxRPS = 5330 / 60;
	constexpr static double wheelCircumference = 4 * 0.0254 * M_PI; // Meters
	constexpr static double gearReduction = 15;
	constexpr static double maxEfficency = 0.8;
	constexpr static double maxVelocity = maxRPS / gearReduction * wheelCircumference * maxEfficency; // Approx. 1.512 Meters per second

	// Max acceleration is a function of the max force available to drive the wheels and the wheel static coefficient of friction
	constexpr static double g = 9.81; // Gravity in meters per second per second
	constexpr static double cof = 1.0; // Colson Performa wheel coefficient of friction
	constexpr static double maxAcceleration = g * cof * 0.5; // Use only 50% of our max available traction

	constexpr static double timeToMaxSpeed = 1.0;

	const FieldOrientation m_fieldOrientation;
};

#endif
