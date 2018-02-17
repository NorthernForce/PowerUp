#ifndef PROFILEGENERATOR_H
#define PROFILEGENERATOR_H

#include <cstdint>
#include <utility>
#include <vector>
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

ProfileGenerator CreateVariableVelocityProfile(const double duration, const double startVelocity, const double finalVelocity);
ProfileGenerator CreateConstantVelocityProfile(const double duration, const double velocity);
ProfileGenerator CreateConstantJerkProfile(const double distance, const double jerk);
ProfileGenerator CombineProfiles(std::initializer_list<ProfileGenerator> items, const double startingPosition = 0);

bool PushProfilePoints(WPI_TalonSRX& talon, ProfileGenerator& generator, const double scale, const uint32_t profileSlotSelect0, const uint32_t profileSlotSelect1, const bool zeroPos);

#endif
