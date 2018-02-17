#include "ProfileGenerator.h"
#include <algorithm>
#include <cassert>
#include <cmath>

namespace
{
    using TrajectoryDuration = ctre::phoenix::motion::TrajectoryDuration;

    ctre::phoenix::motion::TrajectoryDuration ConvertDuration(unsigned ms)
    {
        using namespace ctre::phoenix::motion;
        if (ms < TrajectoryDuration_5ms) return TrajectoryDuration_0ms;
	    else if (ms < TrajectoryDuration_10ms) return TrajectoryDuration_5ms;
	    else if (ms < TrajectoryDuration_20ms) return TrajectoryDuration_10ms;
	    else if (ms < TrajectoryDuration_30ms) return TrajectoryDuration_20ms;
	    else if (ms < TrajectoryDuration_40ms) return TrajectoryDuration_30ms;
	    else if (ms < TrajectoryDuration_50ms) return TrajectoryDuration_40ms;
	    else if (ms < TrajectoryDuration_100ms) return TrajectoryDuration_50ms;
	    else return TrajectoryDuration_100ms;
    }

    constexpr double RoundDuration(const double duration, TrajectoryDuration interval)
    {
        return static_cast<unsigned>((duration * 1000 + interval / 2) / interval) * interval / 1000.0;
    }

    /**
    * Generates a motion profile suitable for feeding to TalonSRX Motion Magic
    *
    */
    class VariableVelocityProfile
    {
        using TrajectoryDuration = ctre::phoenix::motion::TrajectoryDuration;
    public:
        VariableVelocityProfile(const VariableVelocityProfile&) = default;
        VariableVelocityProfile(const double duration, const double startVelocity, const double finalVelocity) :
            m_jerk(4 * (finalVelocity - startVelocity) / std::pow(duration, 2)),
            m_durationMilliSec(static_cast<unsigned>(RoundDuration(duration, TrajectoryDuration::TrajectoryDuration_20ms) * 1000)),
            m_position(0),
            m_velocity(startVelocity),
            m_acceleration(0),
            m_time(0)
        {
            assert(duration > 0);
        }

        ProfilePoint operator()()
        {
            assert(m_time < m_durationMilliSec);

            const auto duration = std::min(ConvertDuration(m_durationMilliSec - m_time), TrajectoryDuration::TrajectoryDuration_10ms);
            const auto interval = duration / 1000.0;
            const auto jerk = m_time < m_durationMilliSec / 2 ? +m_jerk : -m_jerk;
            const auto newAcceleration = m_acceleration + jerk * interval;
            const auto newVelocity = m_velocity + (m_acceleration + newAcceleration) / 2 * interval;
            const auto newPosition = m_position + (m_velocity + newVelocity) / 2 * interval;
            m_acceleration = newAcceleration;
            m_velocity = newVelocity;
            m_position = newPosition;
            m_time += duration;

            return{ duration, m_position, m_velocity, m_time >= m_durationMilliSec };
        }


    private:
        const double m_jerk;
        const unsigned m_durationMilliSec;

        double m_position;
        double m_velocity;
        double m_acceleration;
        unsigned m_time;
    };

    class ConstantVelocityProfile
    {
        using TrajectoryDuration = ctre::phoenix::motion::TrajectoryDuration;
    public:
        ConstantVelocityProfile(const ConstantVelocityProfile&) = default;
        ConstantVelocityProfile(const double duration, const double velocity) :
            m_durationMilliSec(static_cast<unsigned>(RoundDuration(duration, TrajectoryDuration::TrajectoryDuration_5ms) * 1000)),
            m_velocity(velocity),
            m_position(0),
            m_time(0)
        {
            assert(duration >= 0);
        }

        ProfilePoint operator()()
        {
            assert(m_time < m_durationMilliSec);

            const auto duration = std::min(ConvertDuration(m_durationMilliSec - m_time), TrajectoryDuration::TrajectoryDuration_100ms);
            const auto interval = duration / 1000.0;
            m_position += m_velocity * interval;
            m_time += duration;

            return{ duration, m_position, m_velocity, m_time >= m_durationMilliSec };
        }


    private:
        const unsigned m_durationMilliSec;
        const double m_velocity;

        double m_position;
        unsigned m_time;
    };

    class ProfileAggregator
    {
    public:
        ProfileAggregator(std::initializer_list<ProfileGenerator> items) :
            m_items(std::move(items)),
            m_current(m_items.begin()),
            m_positionOffset(0)
        {
        }

        ProfilePoint operator()()
        {
            assert(m_current != m_items.end());
            auto pt = (*m_current)();
            pt.m_position += m_positionOffset;
            if (pt.m_last)
            {
                ++m_current;
                m_positionOffset = pt.m_position;
                if (m_current != m_items.end())
                {
                    pt.m_last = false;
                }
            }
            return pt;
        }

    private:
        using Items = std::vector<ProfileGenerator>;
        Items m_items;
        Items::iterator m_current;
        double m_positionOffset;
    };

}

ProfileGenerator CreateVariableVelocityProfile(const double duration, const double startVelocity, const double finalVelocity)
{
    return VariableVelocityProfile (duration, startVelocity, finalVelocity);
}

ProfileGenerator CreateConstantVelocityProfile(const double duration, const double velocity)
{
    return ConstantVelocityProfile(duration, velocity);
}

ProfileGenerator CombineProfiles(std::initializer_list<ProfileGenerator> items)
{
    return ProfileAggregator(std::move(items));
}

