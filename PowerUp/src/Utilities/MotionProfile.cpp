#include "MotionProfile.h"
#include "DriverStation.h"

MotionProfile::MotionProfile(TalonSRX& talon, int pidIdx0, int pidIdx1) :
	m_talon(talon),
	m_pidIdx0(pidIdx0),
	m_pidIdx1(pidIdx1),
	m_notifer(&MotionProfile::PeriodicTask, this),
	m_state(State::Disabled),
	m_scale(0)
{
	m_talon.GetMotionProfileStatus(m_status);
	m_talon.ChangeMotionControlFramePeriod(5);
	m_talon.ConfigMotionProfileTrajectoryPeriod(0, timeoutMs);
}

void MotionProfile::Start(const ProfileGenerator& generator, const double scale)
{
	assert(m_state == State::Disabled);
	m_generator = generator;
	m_scale = scale;
	m_state = State::Starting;
	m_talon.Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	m_talon.ClearMotionProfileTrajectories();

	if (m_status.hasUnderrun)
	{
		DriverStation::ReportError("Motion profile underrun");
		m_talon.ClearMotionProfileHasUnderrun(timeoutMs);
	}

	// Prefill a few points
	for (unsigned i = 0; i < minPointsInTalon; ++i)
	{
		PeriodicTask();
	}

	m_talon.GetMotionProfileStatus(m_status);
	// assert(m_status.btmBufferCnt > kMinPointsInTalon); // Unlikely as I think GetMotionProfileStatus returns the last status sent

	m_notifer.StartPeriodic(0.005);
	m_talon.Set(ControlMode::MotionProfile, SetValueMotionProfile::Enable);
}

void MotionProfile::Cancel()
{
	m_notifer.Stop();
	m_talon.Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	m_state = State::Finished;
}

void MotionProfile::PeriodicTask()
{
	// Pull the next point from the profile and send it to the talon
	if ((m_state == State::Starting || m_state == State::Filling)
			&& m_status.topBufferRem > 0)
	{
		const auto pt = m_generator();
		TrajectoryPoint point;
		point.position = pt.m_position * m_scale;
		point.velocity = pt.m_velocity * m_scale;
		point.headingDeg = 0;
		point.profileSlotSelect0 = 0;
		point.profileSlotSelect1 = 0;
		point.isLastPoint = pt.m_last;
		point.zeroPos = m_state == State::Starting;
		point.timeDur = pt.m_duration;
		m_talon.PushMotionProfileTrajectory(point);
		if (point.isLastPoint)
		{
			m_state = State::Running;
		}
	}

	// Keep the talon fed
	m_talon.ProcessMotionProfileBuffer();

	// Check the status of the profile
	m_talon.GetMotionProfileStatus(m_status);
	// auto pos = m_talon.GetActiveTrajectoryPosition();
	// auto vel = m_talon.GetActiveTrajectoryVelocity();
	if (m_status.activePointValid && m_status.isLast)
	{
		m_notifer.Stop();
		m_state = State::Finished;
		m_talon.Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);
	}

	if (m_status.hasUnderrun)
	{
		DriverStation::ReportError("Motion profile underrun");
		m_talon.ClearMotionProfileHasUnderrun(noTimeoutMs);
	}
}
