#include "FieldPositioningSystem.h"
#include "DriverStation.h"
#include "../RobotMap.h"

#include <fstream>

namespace
{

std::string GetTelemetryFileName()
{
	const auto& ds = DriverStation::GetInstance();
	const auto event = ds.GetEventName();
	const auto match = ds.GetMatchNumber();
	char path[100];
	sprintf(path, "/tmp/Telemetry_%s_Match_%d.csv", event.c_str(), match);
	return path;
}
}

FieldPositioningSystem::FieldPositioningSystem() :
	frc::Subsystem("Field positioning system"),
	ahrs(RobotMap::ahrs),
	running(false),
	itemsToProcess(100)
{
}

FieldPositioningSystem::~FieldPositioningSystem()
{
	Stop();
}

void FieldPositioningSystem::InitDefaultCommand()
{

}

void FieldPositioningSystem::Periodic()
{
	if(!running)
	{
		return;
	}

	const auto update_rate_hz = 50;
	const bool is_moving = true;
	auto& sensor = *ahrs;
	Telemetry value;
	value.xAccel = sensor.GetWorldLinearAccelX();
	value.yAccel = sensor.GetWorldLinearAccelY();
	value.zAccel = sensor.GetWorldLinearAccelZ();
	sensor.UpdateDisplacement(value.xAccel, value.yAccel, update_rate_hz, is_moving);

	value.time = timer.Get();
	value.heading = sensor.GetCompassHeading();
	value.roll = sensor.GetRoll();
	value.pitch = sensor.GetPitch();
	value.yaw = sensor.GetYaw();
	value.xDisplacement = sensor.GetDisplacementX() + offset.x;
	value.yDisplacement = sensor.GetDisplacementY() + offset.y;
	value.zDisplacement = sensor.GetDisplacementZ();
	value.xVelocity = sensor.GetVelocityX();
	value.yVelocity = sensor.GetVelocityY();
	value.zVelocity = sensor.GetVelocityZ();
	value.isMoving = is_moving;

	currentPosition = frc::Vector2d(value.xDisplacement, value.yDisplacement);
	currentHeading = value.heading;
	const std::lock_guard<std::mutex> lck (bufferMutex);
	itemsToProcess.push_back(value);
}

void FieldPositioningSystem::Start(frc::Vector2d position, float heading)
{
	logFile = std::make_unique<std::fstream>(GetTelemetryFileName());
	*logFile << "Time,Heading,xDisplacement,yDisplacement,zDisplacement,Pitch,Roll,Yaw,xVelocity,yVelocity,zVelocity,xAccel,yAccel,zAccel,IsMoving\n";
	running = true;
	offset = position;
	currentPosition = position;
	currentHeading = heading;
	timer.Reset();
	ahrs->ResetDisplacement();
	ahrs->SetAngleAdjustment(heading);
	logWriter = std::thread([this]() { WriteLog(); });

	bool isRealTime;
	const int priority = std::min(GetCurrentThreadPriority(&isRealTime) + 10, 99);
	SetThreadPriority(logWriter, isRealTime, priority);
}

void FieldPositioningSystem::Stop()
{
	running = false;
	if(logWriter.joinable())
	{
		logWriter.join();
	}
	logFile.reset();
}

frc::Vector2d FieldPositioningSystem::GetPosition() const
{
	return currentPosition;
}

float FieldPositioningSystem::GetHeading() const
{
	return currentHeading;
}

void FieldPositioningSystem::WriteLog()
{
	bufferMutex.lock();
	while(running || itemsToProcess.size())
	{
		while(itemsToProcess.size())
		{
			const auto item = itemsToProcess.front();
			bufferMutex.unlock();
			auto& os = *logFile.get();
			os << item.time << item.heading << "," << "," << item.xDisplacement << "," << item.yDisplacement << "," << item.zDisplacement << ","
					<< item.pitch << "," << item.roll << "," << item.yaw << ","
					<< item.xVelocity << "," << item.yVelocity << "," << item.zVelocity << ","
					<< item.xAccel << "," << item.yAccel << "," << item.zAccel << ","
					<< item.isMoving << "\n";

			bufferMutex.lock();
		}
		bufferMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		bufferMutex.lock();
	}
	bufferMutex.unlock();
}

