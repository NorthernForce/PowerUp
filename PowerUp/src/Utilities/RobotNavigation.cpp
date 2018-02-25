#include "RobotNavigation.h"

namespace
{
RobotNavigation::RobotTrajectory Combine()
{

}
}

RobotNavigation::RobotNavigation(const FieldOrientation& orientation) :
		m_fieldOrientation(orientation)
{
}

RobotNavigation::RobotTrajectory RobotNavigation::CreateProfile(const Position from, const Position to)
{
	return CreateProfile(2, 0, 0, 0);
}

RobotNavigation::RobotTrajectory RobotNavigation::CreateProfile(const double distance, const double startVelocity, const double finalVelocity, const double angleDegrees)
{
	if(angleDegrees == 0)
	{
		const auto profile = CreateComplexProfile(distance, startVelocity, finalVelocity, maxVelocity, timeToMaxSpeed);
		return RobotTrajectory { profile, profile };
	}

    const auto outsideDistance = distance + std::abs(angleDegrees) / 360 * M_PI * wheelTrack;
    const auto outsideProfile = CreateComplexProfile(outsideDistance, startVelocity, finalVelocity, maxVelocity, timeToMaxSpeed);

    // There is probably a better way to calculate the target velocity for the inside wheels than this
    const auto insideDistance = distance - std::abs(angleDegrees) / 360 * M_PI * wheelTrack;
    auto vMax = maxVelocity;
    auto vMin = 0.0;
    while(true)
    {
        const auto insideProfile = CreateComplexProfile(insideDistance, startVelocity, finalVelocity, (vMax + vMin) / 2, timeToMaxSpeed);
        if(std::abs(insideProfile.m_duration - outsideProfile.m_duration) < 0.01)
        {
            if(angleDegrees > 0)
                return { outsideProfile, insideProfile };
            else
                return{ insideProfile, outsideProfile };
        }
        if(insideProfile.m_duration > outsideProfile.m_duration)
        {
            vMin = (vMax + vMin) / 2;
        }
        else
        {
            vMax = (vMax + vMin) / 2;
        }
    }
}
