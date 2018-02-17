#ifndef PROFILEGENERATOR_H
#define PROFILEGENERATOR_H

#include <cstdint>
#include <utility>
#include <vector>
#include <functional>
#include "ctre/phoenix/Motion/TrajectoryPoint.h"

struct ProfilePoint
{
    ctre::phoenix::motion::TrajectoryDuration m_duration;
    double m_position;
    double m_velocity;
    bool m_last;
};

using ProfileGenerator = std::function<ProfilePoint()>;

ProfileGenerator CreateVariableVelocityProfile(const double duration, const double startVelocity, const double finalVelocity);
ProfileGenerator CreateConstantVelocityProfile(const double duration, const double velocity);
ProfileGenerator CombineProfiles(std::initializer_list<ProfileGenerator> items);

#endif
