#ifndef MOTIONPROFILE_H
#define MOTIONPROFILE_H

#include "ProfileGenerator.h"
#include "Notifier.h"
// #include "build/tmp/expandedArchives/cscore-cpp-2019.4.1-sources.zip_35f77497d636edf40e6457730c589f42/Notifier.h"
// Use for cs::Notifier

class MotionProfile {
public:
	MotionProfile(TalonSRX& talon, int pidIdx0 = 0, int pidIdx1 = 0);
	void Start(const ProfileGenerator& generator, const double scale);
	void Cancel();
	inline bool IsFinished() const { return m_state == State::Finished; }
	
	void PeriodicTask();
	static constexpr auto timeoutMs = 10;
	static constexpr auto noTimeoutMs = 0;
	static constexpr auto minPointsInTalon = 10;
	enum class State {
		Disabled, Starting, Filling, Running, Finished
	};
	TalonSRX& m_talon;
	const int m_pidIdx0;
	const int m_pidIdx1;

	using Notifier = frc::Notifier;
    Notifier m_notifier;
	State m_state;
	MotionProfileStatus m_status;
	ProfileGenerator m_generator;
	double m_scale;
};
#endif // NOTIFIER_H