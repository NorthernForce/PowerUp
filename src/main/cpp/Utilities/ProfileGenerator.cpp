#include "ProfileGenerator.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>

namespace {
    uint32_t ConvertDuration(uint32_t ms) {
        if (ms < m_t5) return m_t5;
	    else if (ms < m_t10) return m_t5;
	    else if (ms < m_t20) return m_t10;
	    else if (ms < m_t30) return m_t20;
	    else if (ms < m_t40) return m_t30;
	    else if (ms < m_t50) return m_t40;
	    else if (ms < m_t100) return m_t50;
	    else return m_t100;
    }

    class ConstantVelocityProfile {
        using TrajectoryDuration = ctre::phoenix::motion::TrajectoryPoint;
    public:
        ConstantVelocityProfile(const ConstantVelocityProfile&) = default;
        ConstantVelocityProfile(const double distance, const double velocity) :
            m_durationMilliSec(GetDurationMs(distance, velocity)),
            m_velocity(velocity),
            m_position(distance - m_durationMilliSec * velocity / 1000),
            m_time(0)
        {
            assert(m_durationMilliSec > 0);
        }

        inline static constexpr double GetDurationMs(const double distance, const double velocity) {
        	return static_cast<unsigned>(RoundProfileDuration(distance / velocity, m_t5) * 1000);
        }

        inline double GetDuration() const {
            return m_durationMilliSec / 1000.0;
        }

        ProfilePoint operator()() {
            assert(m_time < m_durationMilliSec);
            // Ideally we would use TrajectoryDuration::TrajectoryDuration_100ms but for debugging using the same as
            // VelocityTransitionProfile makes life easier
            const auto duration = std::min(ConvertDuration(m_durationMilliSec - m_time), m_t10);
            const auto interval = duration / 1000.0;
            m_position += m_velocity * interval;
            m_time += duration;
            TrajectoryPoint t_TP;
            t_TP.position = m_position;
            t_TP.velocity = m_velocity;
            t_TP.timeDur = m_time;
            return { t_TP };
            // return{ duration, m_position, m_velocity, m_time >= m_durationMilliSec };
        }

    private:
        const unsigned m_durationMilliSec;
        const double m_velocity;
        double m_position;
        unsigned m_time;
    };

    class VelocityTransitionProfile {
    public:
        VelocityTransitionProfile(const VelocityTransitionProfile&) = default;
        VelocityTransitionProfile(const double distance, const double startVelocity, const double finalVelocity) :
            m_durationMilliSec(GetDurationMs(distance, startVelocity, finalVelocity)),
            m_jerk(8 * (finalVelocity - (distance / m_durationMilliSec * 1000.0)) / std::pow(m_durationMilliSec / 1000.0, 2)),
            m_position(0),
            m_velocity((distance / m_durationMilliSec * 1000.0) * 2 - finalVelocity),
            m_acceleration(0),
            m_time(0)
        {
            assert(m_durationMilliSec > 0);
        }

        inline static constexpr double GetDurationMs(const double distance, const double startVelocity, const double finalVelocity) {
        	return static_cast<unsigned>(RoundProfileDuration(distance / (startVelocity + finalVelocity) * 2, m_t20) * 1000);
        }

        inline double GetDuration() const {
            return m_durationMilliSec / 1000.0;
        }

        ProfilePoint operator()() {
            assert(m_time < m_durationMilliSec);
            const auto duration = m_t10;
            const auto interval = duration / 1000.0;
            const auto jerk = m_time < m_durationMilliSec / 2 ? +m_jerk : -m_jerk;
            const auto newAcceleration = m_acceleration + jerk * interval;
            const auto newVelocity = m_velocity + (m_acceleration + newAcceleration) / 2 * interval;
            const auto newPosition = m_position + (m_velocity + newVelocity) / 2 * interval;
            m_acceleration = newAcceleration;
            m_velocity = newVelocity;
            m_position = newPosition;
            m_time += duration;
            TrajectoryPoint t_TP;
            t_TP.position = m_position;
            t_TP.velocity = m_velocity;
            t_TP.timeDur = m_time;
            return { t_TP };
            // return{ duration, m_position, m_velocity, m_time >= m_durationMilliSec };
        }

    private:
        const unsigned m_durationMilliSec;
        const double m_jerk;
        double m_position;
        double m_velocity;
        double m_acceleration;
        unsigned m_time;
    };

    class ProfileAggregator {
    public:
        ProfileAggregator(ProfileAggregator&& other) = default;
        ProfileAggregator(const ProfileAggregator& other) : m_items(other.m_items), m_current(m_items.begin()), m_positionOffset(other.m_positionOffset) {
        }
        ProfileAggregator(std::vector<Profile>&& items, const double startingPosition) :
            m_items(std::move(items)),
            m_current(m_items.begin()),
            m_positionOffset(startingPosition)
        {
            auto isEmpty = [](const Profile& profile) {
            	return profile.m_distance == 0;
            };
            m_items.erase(std::remove_if(m_items.begin(), m_items.end(), isEmpty), m_items.end());
        }

        double GetDuration() const {
            double duration = 0;
            for (const auto& profile : m_items) {
                duration += profile.m_duration;
            }
            return duration;
        }

        double GetDistance() const {
            double distance = 0;
            for (const auto& profile : m_items) {
                distance += profile.m_distance;
            }
            return distance;
        }

        ProfilePoint operator()() {
            assert(m_current != m_items.end());
            auto pt = (*m_current)();
            pt.m_position += m_positionOffset;
            if (pt.m_last) {
                ++m_current;
                m_positionOffset = pt.m_position;
                if (m_current != m_items.end()) {
                    pt.m_last = false;
                }
            }
            return pt;
        }

    private:
        using Items = std::vector<Profile>;
        Items m_items;
        Items::iterator m_current;
        double m_positionOffset;
    };

}

Profile CreateSimpleProfile(const double distance, const double startVelocity, const double finalVelocity) {
    if (distance == 0) {
        return {};
    }
    else if(startVelocity == finalVelocity) {
        ConstantVelocityProfile generator(distance, startVelocity);
        const auto duration = generator.GetDuration();
        return{ std::move(generator), distance, duration };
    } else {
        VelocityTransitionProfile generator(distance, startVelocity, finalVelocity);
        const auto duration = generator.GetDuration();
        return{ std::move(generator), distance, duration };
    }
}

/**
 * Creates a motion profile definition consisting of up to three parts
 *  1. A transition from the start velocity to the target velocity
 *  2. Constant velocity travel at the target velocity
 *  3. A transition from the target velocity to the final velocity
 *
 * Note, if the distance is too short for the target velocity to be achieved then
 * the profile will contain only parts 1 and 3
 */
Profile CreateComplexProfile(const double distance, const double startVelocity, const double finalVelocity, double targetVelocity, const double timeToMaxVelocity) {
	targetVelocity = std::abs(targetVelocity) * (distance > 0 ? 1 : -1);
    auto d1 = (1 - startVelocity / targetVelocity) * timeToMaxVelocity * (targetVelocity + startVelocity) / 2;
    auto d3 = (1 - finalVelocity / targetVelocity) * timeToMaxVelocity * (targetVelocity + finalVelocity) / 2;
    auto d2 = distance - d1 - d3;
    if (d2 / targetVelocity < TrajectoryDuration_5ms / 1000) {
        if (distance >= 0) {
            targetVelocity = (distance / timeToMaxVelocity + sqrt(2 * (finalVelocity * finalVelocity + startVelocity * startVelocity) + distance * distance)) / 2;
        } else {
            targetVelocity = (distance / timeToMaxVelocity - sqrt(2 * (finalVelocity * finalVelocity + startVelocity * startVelocity) + distance * distance)) / 2;
        }
        d1 = (1 - startVelocity / targetVelocity) * timeToMaxVelocity * (targetVelocity + startVelocity) / 2;
        d2 = 0;
        d3 = distance - d1;
    }

    return CombineProfiles({
        CreateSimpleProfile(d1, startVelocity, targetVelocity),
        CreateSimpleProfile(d2, targetVelocity, targetVelocity),
        CreateSimpleProfile(d3, targetVelocity, finalVelocity)
    });
 }

Profile CombineProfiles(std::vector<Profile>&& items, const double startingPosition) {
    ProfileAggregator aggregator(std::move(items), startingPosition);
    const auto distance = aggregator.GetDistance();
    const auto duration = aggregator.GetDuration();
    return {
    	std::move(aggregator), distance, duration
    };
}
