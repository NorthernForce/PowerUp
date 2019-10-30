#include "TalonTelemetry.h"
#include "Robot.h"
#include "LogFileName.h"
#include <frc/Timer.h>
#include <thread>
#include <hal/Threads.h>

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

void TalonTelemetry::Start() {
	if(m_record.joinable()) {
		m_record.join();
	}
	if(m_write.joinable()) {
		m_write.join();
	}
	m_running = true;
	m_record = std::thread([this](){ this->RecordTelemetry(); });
	m_write = std::thread([this](){ this->WriteTelemetry(); });
}

void TalonTelemetry::RecordTelemetry() {
	Telemetry telemetry;
	while(m_running) {
		std::this_thread::sleep_for(m_period);
		if(!Robot::robot->IsDisabled()) {
			telemetry.m_time = Timer::GetFPGATimestamp();
			auto const talon = m_talons.front().get();
			auto sensorCollection = talon->GetSensorCollection();
			telemetry.m_sensorPosition = sensorCollection.GetQuadraturePosition();
			telemetry.m_sensorVelocity = sensorCollection.GetQuadratureVelocity();
			if(m_pidIdx != -1 && (talon->GetControlMode() != ControlMode::PercentOutput)) {
				telemetry.m_closedLoopTarget = talon->GetClosedLoopTarget(m_pidIdx);
				telemetry.m_closedLoopError = talon->GetClosedLoopError(m_pidIdx);
				telemetry.m_integralAccumulator = talon->GetIntegralAccumulator(m_pidIdx);
			}

			for(size_t i = 0; i < m_talons.size(); ++i) {
				auto const talon = m_talons[i].get();
				telemetry.m_talonDetails[i].m_output = talon->GetMotorOutputVoltage();
				telemetry.m_talonDetails[i].m_voltage = talon->GetMotorOutputVoltage();
				telemetry.m_talonDetails[i].m_current = talon->GetOutputCurrent();
				telemetry.m_talonDetails[i].m_temperature = talon->GetTemperature();
			}
			const std::lock_guard<std::mutex> lck (m_bufferMutex);
			m_itemsToProcess.push_back(telemetry);
		}
	}
}

void TalonTelemetry::WriteTelemetry() {
	HAL_Bool isRealTime = false;
	HAL_Bool* isRealTime_ptr = &isRealTime;
	int32_t* status = 0; 
	const int priority = std::min(HAL_GetCurrentThreadPriority(isRealTime_ptr, status) + 10, 99);
	HAL_SetCurrentThreadPriority(false, priority, status);
	m_bufferMutex.lock();
	while(m_running || m_itemsToProcess.size()) {
		if(!m_logfile && m_itemsToProcess.size()) {
			m_bufferMutex.unlock();
			OpenLogFile();
			m_bufferMutex.lock();
		}
		while(m_itemsToProcess.size()) {
			const auto item = m_itemsToProcess.pop_front();
			m_bufferMutex.unlock();
			(*m_logfile) << item.m_time << "," << item.m_sensorPosition << "," << item.m_sensorVelocity;
			if (m_pidIdx != -1) {
				(*m_logfile) << "," << item.m_closedLoopTarget << "," << item.m_closedLoopError << "," << item.m_integralAccumulator;
			}
			for (size_t i = 0; i < m_talons.size(); ++i) {
				(*m_logfile) << "," << item.m_talonDetails[i].m_output << "," << item.m_talonDetails[i].m_voltage << "," << item.m_talonDetails[i].m_current << "," << item.m_talonDetails[i].m_temperature;
			}
			(*m_logfile) << "\n";
			m_bufferMutex.lock();
		}
		m_bufferMutex.unlock();
		if(Robot::robot->IsDisabled() && m_logfile) {
			CloseLogFile();
		}
		std::this_thread::sleep_for(m_period);
		m_bufferMutex.lock();
	}
	m_bufferMutex.unlock();
	if (m_logfile) {
		CloseLogFile();
	}
}

void TalonTelemetry::OpenLogFile()
{
	const auto& name = m_talons.front()->GetName();
	const auto path = GetLogFileName(name.c_str(), "Telemetry");
	m_logfile = std::make_unique<std::ofstream>(path);
	(*m_logfile) << "Time Sec,Position,Velocity";
	auto const talon = m_talons.front().get();
	talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_3_Quadrature, m_period.count(), 0);
	talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_2_Feedback0, m_period.count(), 0);
	talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, m_period.count(), 0);
	if(m_pidIdx != -1) {
		(*m_logfile) << ",Target,Error,Integral Accumulator";
		talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, m_period.count(), 0);
	}
	for (const auto& talon : m_talons) {
		const auto name = talon->GetName();
		(*m_logfile) << "," << name << " Output %," << name << " Voltage (V)," << name << " Current (A)," << name << " Temperature (C)";
	}
	(*m_logfile) << "\n";
}

void TalonTelemetry::CloseLogFile() {
	m_logfile->close();
	m_logfile.reset();
}

void TalonTelemetry::Stop() {
	m_running = false;
}
