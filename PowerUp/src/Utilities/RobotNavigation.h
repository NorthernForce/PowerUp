#ifndef ROBOTNAVIGATION_H
#define ROBOTNAVIGATION_H

#include <cstdint>
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "FieldOrientation.h"
#include "ProfileGenerator.h"
#include "Subsystems/DriveTrain.h"
#include <functional>
#include <cmath>

class RobotNavigation {
public:
	enum class Position {
		StartingPos,
		ScoreOnScale,
		ScoreOnSwitch,
		PickupCubeAtSwitch,
	};

	struct RobotTrajectory {
		Profile m_left;
		Profile m_right;
	};
	RobotNavigation(const FieldOrientation& orientation);
	RobotNavigation(const RobotNavigation&) = default;
	RobotTrajectory CreatePath(const Position from, const Position to) const;
	static RobotTrajectory CreateProfile(const double distance, const double startVelocity, const double finalVelocity, const double angleDegrees);

private:
	static double CalculateDuration(const double distance, const double startVelocity, const double finalVelocity);

	RobotTrajectory CreatePathFromStartToSwitch() const;
	RobotTrajectory CreatePathFromStartToScale() const;
	constexpr static double wheelTrack = 0.64;
	constexpr static double maxSpeed = DriveTrain::maxVelocityLowGear * 0.8;
	constexpr static double timeToMaxSpeed = 1.0;
	const FieldOrientation m_fieldOrientation;
};

#endif
