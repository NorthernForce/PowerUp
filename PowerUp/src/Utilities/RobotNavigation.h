#ifndef ROBOTNAVIGATION_H
#define ROBOTNAVIGATION_H

#include <cstdint>
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "Utilities/FieldOrientation.h"
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

	struct RobotTrajectoryPoint
	{
		double m_leftPosition;
		double m_leftVelocity;
		double m_rightPosition;
		double m_rightVelocity;
		ctre::phoenix::motion::TrajectoryDuration m_duration;
		bool m_last;
	};

	using DriveProfile = std::function<RobotTrajectoryPoint()>;

	RobotNavigation(const FieldOrientation& orientation);
	RobotNavigation(const RobotNavigation&) = default;

	DriveProfile CreateProfile(const Position from, const Position to);
private:
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

	// Max jerk controls how jerky the movements are. A lower number will be smoother but the
	// robot will take more time to accelerate and decelerate. A higher number could cause jerky
	// motion especially when the arm is raised
	constexpr static double timeToMaxSpeed = 1.0;
	constexpr static double maxJerk = maxVelocity / std::pow(timeToMaxSpeed / 2, 2); // Approx. 6.05 meters/sec^3

	// The greatest velocity change that can be obtained at maxJerk without exceeding maxAcceleration
	constexpr static double maxVelocityChange = std::pow(maxAcceleration, 2) / maxJerk;
	static_assert(maxVelocity < maxVelocityChange * 2, "Currently limited to basic triangular shaped acceleration profiles -  isosceles trapezoid profiles not yet supported");

	class StraightProfile;
	class CurveProfile;

	const FieldOrientation m_fieldOrientation;
};

#endif
