// FieldPositioningSystem

#ifndef FIELDPOSITIONINGSYSTEM_H
#define FIELDPOSITIONINGSYSTEM_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "circular_buffer.h"
#include "AHRS.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <ostream>

/**
 *
 *
 */
class FieldPositioningSystem: public frc::Subsystem {
public:
	FieldPositioningSystem();
	~FieldPositioningSystem();

	void InitDefaultCommand() override;
	void Periodic() override;

	void Start(frc::Vector2d position, float heading);
	void Stop();

	frc::Vector2d GetPosition() const;
	float GetHeading() const;

private:
	void WriteLog();
private:
	struct Telemetry
	{
		inline Telemetry(int = 0) {}
		double time;
		float heading, pitch, roll, yaw;
		float xDisplacement, yDisplacement, zDisplacement;
		float xVelocity, yVelocity, zVelocity;
		float xAccel, yAccel, zAccel;
		bool isMoving;
	};


	frc::Vector2d currentPosition;
	float currentHeading;
	frc::Vector2d offset;
	std::shared_ptr<AHRS> ahrs;
	frc::Timer timer;
	std::atomic_bool running;
	std::mutex bufferMutex;
	frc::circular_buffer<Telemetry> itemsToProcess;
	std::unique_ptr<std::ostream> logFile;
	std::thread logWriter;
};

#endif
