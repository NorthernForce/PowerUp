#include "TalonTelemetry.h"
#include <Timer.h>
#include <ctime>

namespace
{
std::string GetCurrentTime()
{
	constexpr int bufferSize = 32;
	char buffer[bufferSize];
	const auto t = std::time(nullptr);
	std::strftime(buffer, bufferSize, "%F %T", std::localtime(&t));
	return buffer;
}
}

TalonTelemetry::TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const int pidIdx, const unsigned frequency) :
	m_talon(std::move(talon)),
	m_pidIdx(pidIdx),
	m_frequency(frequency),
	m_count(0)
{
}

void TalonTelemetry::Start()
{
	char path[100];
	const auto& name = m_talon->GetName();
	const auto& time = GetCurrentTime();
	sprintf(path, "/tmp/%s %s Telemetry.csv", name.c_str(), time.c_str());
	m_os.open(path);
	m_os
			<< "Time Sec,Output %,Position,Velocity,Target,Error,Derivative,Voltage (V),Current (A),Temperature (C)\n";
	Periodic();
}

void TalonTelemetry::Periodic()
{
	if((++m_count % m_frequency) == 0)
	{
		m_os << Timer::GetFPGATimestamp() << "," <<
		m_talon->GetMotorOutputPercent() * 100 << "," <<
		m_talon->GetSelectedSensorPosition(m_pidIdx) << "," <<
		m_talon->GetSelectedSensorVelocity(m_pidIdx) << "," <<
		m_talon->GetClosedLoopTarget(m_pidIdx) << "," <<
		m_talon->GetClosedLoopError(m_pidIdx) << "," <<
		m_talon->GetErrorDerivative(m_pidIdx) << "," <<
		m_talon->GetMotorOutputVoltage() << "," <<
		m_talon->GetOutputCurrent() << "," <<
		m_talon->GetTemperature() << "\n";
	}
}

void TalonTelemetry::Stop()
{
m_os.close();
}
