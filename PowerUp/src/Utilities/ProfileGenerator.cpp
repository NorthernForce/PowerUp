#include "ProfileGenerator.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>

namespace
{
    TrajectoryDuration ConvertDuration(unsigned ms)
    {
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
            m_durationMilliSec(static_cast<unsigned>(RoundDuration(duration, TrajectoryDuration::TrajectoryDuration_20ms) * 1000)),
            m_jerk(4 * (finalVelocity - startVelocity) / std::pow(m_durationMilliSec / 1000.0, 2)),
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
        const unsigned m_durationMilliSec;
        const double m_jerk;

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
        ProfileAggregator(std::initializer_list<ProfileGenerator> items, const double startingPosition) :
            m_items(std::move(items)),
            m_current(m_items.begin()),
            m_positionOffset(startingPosition)
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

ProfileGenerator CreateConstantJerkProfile(const double distance, const double jerk)
{
    const auto duration = RoundDuration(std::pow(16 * distance / jerk, 1 / 3.0), TrajectoryDuration_20ms);
    const auto adjustedJerk = 16 * distance / std::pow(duration, 3);
    const auto targetVelocity = adjustedJerk * std::pow(duration, 2) / 4;

    return CombineProfiles({
        VariableVelocityProfile(duration, 0, targetVelocity),
        VariableVelocityProfile(duration, targetVelocity, 0)
    });
}

ProfileGenerator CombineProfiles(std::initializer_list<ProfileGenerator> items, const double startingPosition)
{
    return ProfileAggregator(std::move(items), startingPosition);
}

bool PushProfilePoints(WPI_TalonSRX& talon, ProfileGenerator& generator, const double scale, const uint32_t profileSlotSelect0, const uint32_t profileSlotSelect1, const bool zeroPos)
{
	if(!generator)
	{
		return true;
	}

	unsigned time = 0;
	ctre::phoenix::motion::TrajectoryPoint trajPt = {};
	trajPt.zeroPos = zeroPos;
	trajPt.profileSlotSelect0 = profileSlotSelect0;
	trajPt.profileSlotSelect1 = profileSlotSelect1;

	while(!trajPt.isLastPoint && time < 100)
	{
		const auto pt = generator();
		trajPt.position = pt.m_position * scale;
		trajPt.velocity = pt.m_velocity * scale;
		trajPt.timeDur = pt.m_duration;
		trajPt.isLastPoint = pt.m_last;
		trajPt.zeroPos = false;
		talon.PushMotionProfileTrajectory(trajPt);
		time = time + pt.m_duration;
	}

	if(trajPt.isLastPoint)
	{
		generator = nullptr;
	}
	return trajPt.isLastPoint;
}
