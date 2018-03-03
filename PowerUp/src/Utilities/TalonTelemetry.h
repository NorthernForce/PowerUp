#ifndef TALONTELEMETRY_H
#define TALONTELEMETRY_H

#include "ctre/Phoenix.h"
#include "circular_buffer.h"
#include <fstream>
#include <atomic>
#include <mutex>
#include <thread>

class TalonTelemetry {
public:
	TalonTelemetry(std::initializer_list<std::shared_ptr<WPI_TalonSRX>> talons, const int pidIdx, const std::chrono::milliseconds period);
	TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const int pidIdx, const std::chrono::milliseconds period);
	TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const std::chrono::milliseconds period);
	void Start();
	void Stop();

private:
	void RecordTelemetry();
	void WriteTelemetry();
	void OpenLogFile();
	void CloseLogFile();
	struct Telemetry {
		struct TalonInfo {
			double m_output;
			double m_voltage;
			double m_current;
			int m_temperature;
		};
		//TODO: look into this warning
		inline Telemetry(int = 0) {}
		double m_time;
		int m_sensorPosition;
		int m_sensorVelocity;
		int m_closedLoopTarget;
		int m_closedLoopError;
		int m_integralAccumulator;
		std::array<TalonInfo, 4> m_talonDetails;
	};
	const std::vector<std::shared_ptr<WPI_TalonSRX> > m_talons;
	const int m_pidIdx;
	const std::chrono::milliseconds m_period;
	std::unique_ptr<std::ofstream> m_logfile;
	frc::circular_buffer<Telemetry> m_itemsToProcess;
	std::atomic_bool m_running;
	std::mutex m_bufferMutex;
	std::thread m_record;
	std::thread m_write;
};

#endif //TALONTELEMETRY_H
