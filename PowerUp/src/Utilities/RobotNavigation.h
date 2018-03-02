#ifndef ROBOTNAVIGATION_H
#define ROBOTNAVIGATION_H

#include <cstdint>
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "FieldOrientation.h"
#include "ProfileGenerator.h"
#include "Subsystems/DriveTrain.h"
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

	RobotTrajectory CreatePath(const Position from, const Position to) const;
	static RobotTrajectory CreateProfile(const double distance, const double startVelocity, const double finalVelocity, const double angleDegrees);

private:
	RobotTrajectory CreatePathFromStartToSwitch() const;
	RobotTrajectory CreatePathFromStartToScale() const;


	constexpr static double wheelTrack = 0.64;
	constexpr static double maxVelocity = DriveTrain::maxVelocityLowGear;

	// Max acceleration is a function of the max force available to drive the wheels and the wheel static coefficient of friction
	constexpr static double g = 9.81; // Gravity in meters per second per second
	constexpr static double cof = 1.0; // Colson Performa wheel coefficient of friction
	constexpr static double maxAcceleration = g * cof * 0.5; // Use only 50% of our max available traction

	constexpr static double timeToMaxSpeed = 1.0;

	const FieldOrientation m_fieldOrientation;
};

#endif
