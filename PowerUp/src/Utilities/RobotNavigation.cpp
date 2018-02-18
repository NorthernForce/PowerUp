#include "RobotNavigation.h"
#include "ProfileGenerator.h"

class RobotNavigation::StraightProfile
{
public:
	StraightProfile(const double startVelocity, const double finishVelocity, const double distance) :
			m_generator(CreateGenerator(startVelocity, finishVelocity, distance))
	{

	}

	RobotTrajectoryPoint operator()()
	{
		const auto pt = m_generator();
		return { pt.m_position, pt.m_velocity, pt.m_position, pt.m_velocity, pt.m_duration, pt.m_last};
	}

private:
	static double AccelerationTime(const double velocityChange, const double jerk)
	{
		return 2 * std::sqrt(velocityChange / jerk);
	}

	static double AccelerationDistance(const double startVelocity, const double finishVelocity, const double duration)
	{
		return (startVelocity + finishVelocity) * duration / 2;
	}

	static ProfileGenerator CreateGenerator(const double startVelocity, const double finishVelocity, const double distance)
	{
		const auto jerk = distance > 0 ? maxJerk : -maxJerk;
		const auto targetVelocity = distance > 0 ? maxVelocity : -maxVelocity;
		const auto tAccelerate = AccelerationTime(targetVelocity - startVelocity, jerk);
		const auto tDecelerate = AccelerationTime(targetVelocity - finishVelocity, jerk);
		const auto dAccelerate = AccelerationDistance(startVelocity, targetVelocity, tAccelerate);
		const auto dDecelerate = AccelerationDistance(targetVelocity, finishVelocity, tDecelerate);
		const unsigned tMaintain = (distance - dAccelerate - dDecelerate) / targetVelocity;
		return CombineProfiles({
			CreateVariableVelocityProfile(tAccelerate, startVelocity, targetVelocity),
			CreateConstantVelocityProfile(tMaintain, targetVelocity),
			CreateVariableVelocityProfile(tDecelerate, targetVelocity, finishVelocity)

		});
	}

	static double DistanceToAchieveVelocity(const double currentVelocity, const double desiredVelocity)
	{
		const auto deltaVelocity = desiredVelocity - currentVelocity;
		const auto peakAccelerationTime = std::sqrt(std::abs(deltaVelocity) / RobotNavigation::maxJerk);
		return RobotNavigation::maxJerk * std::pow(peakAccelerationTime, 3) / 8;
	}

	ProfileGenerator m_generator;
};

class RobotNavigation::CurveProfile
{
public:
	CurveProfile(const double startVelocity, const double finishVelocity,
			const double distance, const double angle)
	{

	}

private:
};

RobotNavigation::RobotNavigation(const FieldOrientation& orientation) :
		m_fieldOrientation(orientation)
{
}

RobotNavigation::DriveProfile RobotNavigation::CreateProfile(
		const Position from, const Position to)
{
	return StraightProfile(0, 0, 1);
}

