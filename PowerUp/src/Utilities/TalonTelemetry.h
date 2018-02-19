#ifndef TALONTELEMETRY_H
#define TALONTELEMETRY_H

#include "ctre/Phoenix.h"
#include <fstream>

/**
 *
 *
 * @author ExampleAuthor
 */
class TalonTelemetry
{
public:
	TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const int pidIdx, const unsigned frequency);
	TalonTelemetry(std::shared_ptr<WPI_TalonSRX> talon, const unsigned frequency);
	void Start();
	void Periodic();
	void Stop();

private:
	const std::shared_ptr<WPI_TalonSRX> m_talon;
	const int m_pidIdx;
	const unsigned m_frequency;
	unsigned m_count;
	std::ofstream m_os;
};

#endif
