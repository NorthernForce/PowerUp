#ifndef MOTIONPROFILE_H
#define MOTIONPROFILE_H

#include "ProfileGenerator.h"
#include "Notifier.h"

class MotionProfile
{
public:
	MotionProfile(TalonSRX& talon, int pidIdx0 = 0, int pidIdx1 = 0);

	void Start(const ProfileGenerator& generator, const double scale);
	void Cancel();

	inline bool IsFinished() const { return m_state == State::Finished; }

private:
	void PeriodicTask();

	static constexpr auto timeoutMs = 10;
	static constexpr auto noTimeoutMs = 0;
	static constexpr auto minPointsInTalon = 5;

	enum class State
	{
		Disabled, Starting, Filling, Running, Finished
	};

	TalonSRX& m_talon;
	const int m_pidIdx0;
	const int m_pidIdx1;
	Notifier m_notifer;
	State m_state;
	MotionProfileStatus m_status;

	ProfileGenerator m_generator;
	double m_scale;
};
#endif // MOTIONPROFILE_H
