#ifndef PROFILEGENERATOR_H
#define PROFILEGENERATOR_H

#include <functional>
#include "ctre/Phoenix.h"

struct ProfilePoint {
    TrajectoryDuration m_duration;
    double m_position;
    double m_velocity;
    bool m_last;
};

using ProfileGenerator = std::function<ProfilePoint()>;

struct Profile {
	ProfileGenerator m_generator;
	double m_distance;
	double m_duration;

    inline ProfilePoint operator()() {
    	return m_generator();
    }
};

constexpr double RoundProfileDuration(const double duration, TrajectoryDuration interval);

Profile CreateSimpleProfile(const double distance, const double startVelocity, const double finalVelocity);
Profile CreateComplexProfile(const double distance, const double startVelocity, const double finalVelocity, const double peakVelocity, const double timeToMaxVelocity);
Profile CombineProfiles(std::vector<Profile>&& items, const double startingPosition = 0);

#endif
