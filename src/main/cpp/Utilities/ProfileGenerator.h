#ifndef PROFILEGENERATOR_H
#define PROFILEGENERATOR_H

#include <functional>
#include "ctre/Phoenix.h"

using TrajectoryDuration = ctre::phoenix::motion::TrajectoryPoint;

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

constexpr double RoundProfileDuration(const double duration, double interval) {
    return static_cast<unsigned>((duration * 1000 + interval / 2) / interval) * interval / 1000.0;
}

Profile CreateSimpleProfile(const double distance, const double startVelocity, const double finalVelocity);
Profile CreateComplexProfile(const double distance, const double startVelocity, const double finalVelocity, const double peakVelocity, const double timeToMaxVelocity);
Profile CombineProfiles(std::vector<Profile>&& items, const double startingPosition = 0);

uint32_t m_t5 = 5;
uint32_t m_t10 = 10;
uint32_t m_t20 = 20;
uint32_t m_t30 = 30;
uint32_t m_t40 = 40;
uint32_t m_t50 = 50;
uint32_t m_t100 = 100;


#endif
