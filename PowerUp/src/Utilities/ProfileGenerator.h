#ifndef PROFILEGENERATOR_H
#define PROFILEGENERATOR_H

#include <functional>
#include "ctre/Phoenix.h"


struct ProfilePoint
{
    TrajectoryDuration m_duration;
    double m_position;
    double m_velocity;
    bool m_last;
};

using ProfileGenerator = std::function<ProfilePoint()>;

struct Profile
{
	ProfileGenerator m_generator;
	double m_distance;
	double m_duration;

    ProfilePoint operator()() { return m_generator(); }
};

Profile CreateSimpleProfile(const double distance, const double startVelocity, const double finalVelocity);
Profile CreateComplexProfile(const double distance, const double startVelocity, const double finalVelocity, const double peakVelocity, const double timeToMaxVelocity);
Profile CombineProfiles(std::vector<Profile>&& items, const double startingPosition = 0);

bool PushProfilePoints(WPI_TalonSRX& talon, const MotionProfileStatus& status, ProfileGenerator& generator, const double scale, const uint32_t profileSlotSelect0, const uint32_t profileSlotSelect1, const bool zeroPos);

#endif
