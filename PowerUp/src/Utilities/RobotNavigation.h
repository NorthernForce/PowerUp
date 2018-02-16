#ifndef ROBOTNAVIGATION_H
#define ROBOTNAVIGATION_H

#include <cstdint>
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "Utilities/FieldOrientation.h"
#include <functional>

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
		ctre::phoenix::motion::TrajectoryPoint m_left;
		ctre::phoenix::motion::TrajectoryPoint m_right;
	};

	using DriveProfile = std::function<RobotTrajectoryPoint()>;

	RobotNavigation(const FieldOrientation& orientation);
	RobotNavigation(const RobotNavigation&) = default;

	DriveProfile CreateProfile(const Position from, const Position to);
private:
	const FieldOrientation m_fieldOrientation;
};

#endif
