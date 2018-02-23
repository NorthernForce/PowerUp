#include "TalonTelemetry.h"
#include "Robot.h"
#include <Timer.h>
#include <ctime>
#include <thread>

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

TalonTelemetry::TalonTelemetry(std::initializer_list<std::shared_ptr<WPI_TalonSRX>> talons, const int pidIdx, const std::chrono::milliseconds period) :
	m_talons(talons),
	m_pidIdx(pidIdx),
	m_period(period),
	m_itemsToProcess(100)
{
}


TalonTelemetry::TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const int pidIdx, const std::chrono::milliseconds period) :
	m_talons({ std::move(talon) }),
	m_pidIdx(pidIdx),
	m_period(period),
	m_itemsToProcess(100)
{
}

TalonTelemetry::TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const std::chrono::milliseconds period) :
	m_talons({ std::move(talon) }),
	m_pidIdx(-1),
	m_period(period),
	m_itemsToProcess(100)
{
}

void TalonTelemetry::Start()
{
	m_running = true;
	std::thread([this](){ this->RecordTelemetry(); }).detach();
	std::thread([this](){ this->WriteTelemetry(); }).detach();
}

void TalonTelemetry::RecordTelemetry()
{
	Telemetry telemetry;
	while(true)
	{
		std::this_thread::sleep_for(m_period);
		if(!Robot::robot->IsDisabled())
		{
			telemetry.m_time = Timer::GetFPGATimestamp();
			if(m_pidIdx != -1)
			{
				auto const talon = m_talons.front().get();
				auto sensorCollection = talon->GetSensorCollection();
				telemetry.m_sensorPosition = sensorCollection.GetQuadraturePosition();
				telemetry.m_sensorVelocity = sensorCollection.GetQuadratureVelocity();
				telemetry.m_closedLoopTarget = talon->GetClosedLoopTarget(m_pidIdx);
				telemetry.m_closedLoopError = talon->GetClosedLoopError(m_pidIdx);
				telemetry.m_errorDerivative = talon->GetErrorDerivative(m_pidIdx);

				for( size_t i = 0; i < m_talons.size(); ++i)
				{
					auto const talon = m_talons[i].get();
					telemetry.m_talonDetails[i].m_output = talon->GetMotorOutputVoltage();
					telemetry.m_talonDetails[i].m_voltage = talon->GetMotorOutputVoltage();
					telemetry.m_talonDetails[i].m_current = talon->GetOutputCurrent();
					telemetry.m_talonDetails[i].m_temperature = talon->GetTemperature();
				}
			}
		}
		const std::lock_guard<std::mutex> lck (m_bufferMutex);
		m_itemsToProcess.push_back(telemetry);
	}
}

void TalonTelemetry::WriteTelemetry()
{
	bool isRealTime;
	const int priority = std::min(GetCurrentThreadPriority(&isRealTime) + 10, 99);
	SetCurrentThreadPriority(isRealTime, priority);

	m_bufferMutex.lock();
	while(m_running || m_itemsToProcess.size())
	{
		if(Robot::robot->IsDisabled())
		{
			m_bufferMutex.unlock();
			if(m_logfile)
			{
				CloseLogFile();
			}
		}
		else if(!m_logfile)
		{
			m_bufferMutex.unlock();
			OpenLogFile();
		}
		else
		{
			while(m_itemsToProcess.size())
			{
				const auto item = m_itemsToProcess.pop_front();
				m_bufferMutex.unlock();
				(*m_logfile) << item.m_time << "," << item.m_sensorPosition << "," << item.m_sensorVelocity << "," <<
						item.m_closedLoopTarget << "," << item.m_closedLoopError << "," << item.m_errorDerivative;

				for(size_t i = 0; i < m_talons.size(); ++i)
				{
					(*m_logfile) << "," << item.m_talonDetails[i].m_output << "," << item.m_talonDetails[i].m_voltage << "," << item.m_talonDetails[i].m_current << "," << item.m_talonDetails[i].m_temperature;
				}

				(*m_logfile) << "\n";
				m_bufferMutex.lock();
			}
			m_bufferMutex.unlock();
		}
		std::this_thread::sleep_for(m_period);
		m_bufferMutex.lock();
	}
	m_bufferMutex.unlock();
}

void TalonTelemetry::OpenLogFile()
{
	char path[100];
	const auto& name = m_talons.front()->GetName();
	const auto& time = GetCurrentTime();
	sprintf(path, "/tmp/%s %s Telemetry.csv", name.c_str(), time.c_str());
	m_logfile = std::make_unique<std::ofstream>(path);
	(*m_logfile) << "Time Sec";
	if(m_pidIdx != -1)
	{
		(*m_logfile) << ",Position,Velocity,Target,Error,Derivative";
		auto const talon = m_talons.front().get();
		talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_3_Quadrature, m_period.count(), 0);
		talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, m_period.count(), 0);
	}

	for(const auto& talon : m_talons)
	{
		const auto name = talon->GetName();
		(*m_logfile) << "," << name << " Output %," << name << " Voltage (V)," << name << " Current (A)," << name << " Temperature (C)";
	}

	(*m_logfile) << "\n";
}

void TalonTelemetry::CloseLogFile()
{
	m_logfile->close();
	m_logfile.reset();
}


void TalonTelemetry::Stop()
{
	m_running = false;
}
